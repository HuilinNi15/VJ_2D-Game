#ifndef _INTERFACE_INCLUDE
#define _INTERFACE_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"
#include "Text.h"

#include "TileMap.h"
#include "Texture.h"
#include "Sprite.h"
#include "Player.h"
#include "Object.h"
#include "Enemy.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 5

#define CAMERA_WIDTH 256
#define CAMERA_HEIGHT 192

#define DEAD_ZONE_SIZE 4.0f


enum MenuOptionsAnims
{
    PRACTICE, PRACTICE_ARROW,
    NORMAL, NORMAL_ARROW,
    INSTRUCTIONS, INSTRUCTIONS_ARROW,
    CREDITS, CREDITS_ARROW
};

enum LifeBarAnims
{
    ZERO_STAR, ONE_STAR, TWO_STARS, THREE_STARS
};

class Scene {
public:
    Scene();
    ~Scene(); 
    virtual void update(int deltaTime);
    virtual void render();

    Text text;

    std::string getCurrentTime() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << int(Time - currentTime / 1000.f);  // Pads with '0' to a width of 2
        return oss.str();
    }

protected:
    void initShaders();

    ShaderProgram texProgram, simpleProgram;
    float currentTime;
    float Time = 400.f;
    glm::mat4 projection;
};



class GameScene : public Scene {
public:
    GameScene(string level);
    ~GameScene();

    virtual void update(int deltaTime) override;
    virtual void render() override;

private:
    void updateCam(int deltaTime);

    float cameraX = 0.0f;
    float cameraSpeed = 10.0f;

    struct mapData {
        TileMap* map;
        TileMap* decorations;
        std::vector<Enemy> enemies;
        std::vector<Object> objects;
    };
    Player* player;
    mapData map; 

    Texture lifeBarTexture;
    Sprite* lifeBarSprite;

    glm::ivec2 size;
};



class MainScreen : public Scene {
public:
    MainScreen();
    ~MainScreen();

    void update(int deltaTime) override;
    void render() override;

protected:
    Texture backgroundTexture;
    Sprite* backgroundSprite;
    Player* mickeySprite;
    glm::vec2 mickeyPosition;

    Texture textTexture;
    Sprite* textSprite;
}; 



class MenuScreen : public Scene {
public:
    MenuScreen();
    ~MenuScreen();

    void update(int deltaTime) override;
    void render() override;

    void updateSelection(int selection);
    int getSelectedOption();

protected:
    int selectedOption; 

    const int optionCount = 4;
    std::vector<std::string> options;
    glm::ivec2 size, boxPosition, boxSize;
    
    Texture backgroundTexture;
    Texture optionsTexture;

    Sprite* backgroundSprite;
    Sprite* practiceSprite;
    Sprite* normalSprite; 
    Sprite* instructionsSprite;
    Sprite* creditsSprite;

    ShaderProgram* shaderprogram;
};



class InstructionsScreen : public Scene {
public:
    InstructionsScreen();
    ~InstructionsScreen();

    void update(int deltaTime) override;
    void render() override;

protected:
    Texture backgroundTexture;
    Texture instructionsTexture;

    Sprite* backgroundSprite;
    Sprite* instructionsSprite;
};



class CreditsScreen : public Scene {
public:
    CreditsScreen();
    ~CreditsScreen(); 

    void update(int deltaTime) override;
    void render() override;

protected:
    Texture backgroundTexture;
    Texture creditsTexture;

    Sprite* backgroundSprite;
    Sprite* creditsSprite;
};


#endif // _INTERFACE_INCLUDE
