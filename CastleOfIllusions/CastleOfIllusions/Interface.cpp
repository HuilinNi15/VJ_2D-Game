#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Interface.h"


Scene::Scene()
{
	initShaders();
	projection = glm::ortho(0.f, float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
	currentTime = 0.0f;
}

Scene::~Scene()
{

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
}



GameScene::GameScene()
{
	// Forest practice map
	//map = TileMap::createTileMap("levels/forest_practice_map.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	// Chocolate map
	
	string level = "levels/forest_map_prueba.txt"; 
	map.map = TileMap::createTileMap(level, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map.decorations = TileMap::createTileMap(level, glm::vec2(SCREEN_X, SCREEN_Y), texProgram, true);
	
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map.map->getTileSize(), INIT_PLAYER_Y_TILES * map.map->getTileSize()));
	player->setTileMap(map.map);
}

GameScene::~GameScene()
{
	delete map.map;
	delete map.decorations;
	delete player;
}

void GameScene::updateCam(int deltaTime)
{
	float deltaTimeSec = (float)deltaTime / 1000.0f;
	glm::ivec2 posPlayer = player->getPosition();

	glm::ivec2 mapPixelSize = map.map->getMapPixelSize();
	int mapWidth = mapPixelSize.x;
	int mapHeight = mapPixelSize.y;

	float deadZoneWidth = CAMERA_WIDTH / DEAD_ZONE_SIZE;

	// Define the dead zone boundaries
	float deadZoneLeft = cameraX - 16 + (CAMERA_WIDTH - deadZoneWidth) / 2.0f;
	float deadZoneRight = cameraX - 16 + (CAMERA_WIDTH + deadZoneWidth) / 2.0f;

	// Check if the player is outside the dead zone (horizontally)
	if (posPlayer.x < deadZoneLeft)
	{
		cameraX -= (deadZoneLeft - posPlayer.x);  // Move camera left
	}
	else if (posPlayer.x > deadZoneRight)
	{
		cameraX += (posPlayer.x - deadZoneRight);  // Move camera right
	}

	// Clamp the camera to not go out of the map boundaries
	if (cameraX < 0)
		cameraX = 0;
	else if (cameraX + CAMERA_WIDTH > mapWidth)
		cameraX = (float)mapWidth - CAMERA_WIDTH;

	projection = glm::ortho(cameraX, cameraX + float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
}

void GameScene::update(int deltaTime)
{
	Scene::update(deltaTime);
	player->update(deltaTime);
	updateCam(deltaTime);
}

void GameScene::render()
{
	Scene::render();
	map.decorations->render();
	map.map->render();
	player->render();
}



MainScreen::MainScreen()
{
	// Load the background texture
	backgroundTexture.loadFromFile("images/screens/MainScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	// Create the background sprite
	backgroundSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &backgroundTexture, &texProgram);
	backgroundSprite->setNumberAnimations(1);
	backgroundSprite->setAnimationSpeed(0, 1);
	backgroundSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	backgroundSprite->changeAnimation(0);
	backgroundSprite->setPosition(glm::vec2(0, 0)); // Position the background at (0, 0)

	// Create the Mickey sprite and set its position and animation
	mickeySprite = new Player();
	mickeySprite->init(glm::ivec2(112, 128), texProgram); // Initial position of Mickey
	mickeySprite->changeAnimation(WAVING_HAND); // Waving animation
	mickeySprite->setStatic();
}

MainScreen::~MainScreen()
{
    delete backgroundSprite;
    delete mickeySprite;
}

void MainScreen::update(int deltaTime) 
{
	Scene::update(deltaTime);
    mickeySprite->update(deltaTime);
}

void MainScreen::render() 
{
	Scene::render();
    backgroundSprite->render();
	mickeySprite->render();
}



MenuScreen::MenuScreen() 
{
    selectedOption = 0; // Default selection
    // Load textures and initialize the menu
}

MenuScreen::~MenuScreen()
{

}

void MenuScreen::update(int deltaTime) 
{
    // Handle input for selecting levels
}

void MenuScreen::render() 
{
    // Draw menu options
}

// Implement CreditsScreen and InstructionsScreen similarly...



CreditsScreen::CreditsScreen() 
{
    // Load textures and initialize the menu
}

CreditsScreen::~CreditsScreen()
{

}

void CreditsScreen::update(int deltaTime) {
    // Handle input for selecting levels
}

void CreditsScreen::render() {
    // Draw menu options
}



InstructionsScreen::InstructionsScreen() 
{
    // Load textures and initialize the menu
}

InstructionsScreen::~InstructionsScreen()
{

}

void InstructionsScreen::update(int deltaTime) {
    // Handle input for selecting levels
}

void InstructionsScreen::render() {
    // Draw menu options
}