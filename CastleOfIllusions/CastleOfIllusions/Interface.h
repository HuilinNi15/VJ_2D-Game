#ifndef _INTERFACE_INCLUDE
#define _INTERFACE_INCLUDE

#include "Scene.h"
#include "Texture.h"
#include "Sprite.h"
#include "Player.h"

class Interface : public Scene {
public:
    virtual void init() override;
    virtual void update(int deltaTime) override;
    virtual void render() override;

protected:
    Texture backgroundTexture;
    std::string title;
};

class MainScreen : public Interface {
public:
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    Texture backgroundTexture;
    //Sprite* titleSprite; // To hold the title sprite
    Player* mickeySprite; // To hold the Mickey sprite
    //glm::vec2 titlePosition; // Position for the title
    glm::vec2 mickeyPosition; // Position for Mickey
};

class MenuScreen : public Interface {
public:
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    int selectedOption; // Track selected level
};

class CreditsScreen : public Interface {
public:
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    // Additional attributes for credits
};

class InstructionsScreen : public Interface {
public:
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    // Additional attributes for instructions
};

#endif // _INTERFACE_INCLUDE
