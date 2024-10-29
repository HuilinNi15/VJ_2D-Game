#ifndef _INTERFACE_INCLUDE
#define _INTERFACE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Texture.h"
#include "Sprite.h"
#include "Player.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 5

#define CAMERA_WIDTH 256
#define CAMERA_HEIGHT 192

#define DEAD_ZONE_SIZE 4.0f


class Scene {
public:
    Scene();
    ~Scene(); 
    virtual void update(int deltaTime);
    virtual void render();

protected:
    void initShaders();

    ShaderProgram texProgram;
    float currentTime;
    glm::mat4 projection;
};



class GameScene : public Scene {
public:
    GameScene();
    ~GameScene();

    virtual void update(int deltaTime) override;
    virtual void render() override;

private:
    void updateCam(int deltaTime);

    float cameraX = 0.0f;
    float cameraSpeed = 10.0f;

    TileMap* map;
    TileMap* decorations; 
    Player* player;
};



class MenuScreen : public Scene {
public:
    MenuScreen();
    ~MenuScreen();

    void update(int deltaTime) override;
    void render() override;

private:
    int selectedOption; 
};



class MainScreen : public Scene {
public:
    MainScreen();
    ~MainScreen();

    void update(int deltaTime) override;
    void render() override;

private:
    Texture backgroundTexture; 
    Sprite* backgroundSprite; 
    Player* mickeySprite;
    glm::vec2 mickeyPosition;
};



class CreditsScreen : public Scene {
public:
    CreditsScreen();
    ~CreditsScreen(); 

    void update(int deltaTime) override;
    void render() override;

private:
    // Additional attributes for credits
};



class InstructionsScreen : public Scene {
public:
    InstructionsScreen();
    ~InstructionsScreen();

    void update(int deltaTime) override;
    void render() override;

private:
    // Additional attributes for instructions
};


#endif // _INTERFACE_INCLUDE
