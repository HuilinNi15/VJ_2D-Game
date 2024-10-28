#include "Interface.h"

void Interface::init() {
    // Initialize common attributes, if any
}

void Interface::update(int deltaTime) {
    // Update common logic, if any
}

void MainScreen::init() {
    // Load the background texture
    backgroundTexture.loadFromFile("images/screens/MainScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
    backgroundTexture.setMinFilter(GL_NEAREST);
    backgroundTexture.setMagFilter(GL_NEAREST);

    // Crear el sprite de fondo
    backgroundSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &backgroundTexture, &texProgram);
    backgroundSprite->setPosition(glm::vec2(0, 0)); // Posicionar el fondo en (0,0)

    // Crear el sprite de Mickey y establecer su posición y animación de saludo
    mickeySprite = new Player();
    mickeySprite->init(glm::ivec2(50, 50), texProgram);  // Posición inicial de Mickey
    mickeySprite->setStatic();
    mickeySprite->changeAnimation(WAVING_HAND); // Animación de saludo
}

void MainScreen::update(int deltaTime) {
    mickeySprite->update(deltaTime);
}

void MainScreen::render() {
    glm::mat4 modelview;

    texProgram.use();
    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    modelview = glm::mat4(1.0f);
    texProgram.setUniformMatrix4f("modelview", modelview);
    texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

    backgroundSprite->render(); // Renderizar el fondo
    mickeySprite->render();           // Renderizar a Mickey
}

void MenuScreen::init() {
    selectedOption = 0; // Default selection
    // Load textures and initialize the menu
}

void MenuScreen::update(int deltaTime) {
    // Handle input for selecting levels
}

void MenuScreen::render() {
    // Draw menu options
}

// Implement CreditsScreen and InstructionsScreen similarly...
