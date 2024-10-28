#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	// Forest practice map
	//map = TileMap::createTileMap("levels/forest_practice_map.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	// Chocolate map
	map = TileMap::createTileMap("levels/chocolate_map.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::updateCam(int deltaTime)
{
	float deltaTimeSec = (float)deltaTime / 1000.0f;
	glm::ivec2 posPlayer = player->getPosition();

	glm::ivec2 mapPixelSize = map->getMapPixelSize();
	int mapWidth = mapPixelSize.x;
	int mapHeight = mapPixelSize.y;

	float deadZoneWidth = CAMERA_WIDTH / DEAD_ZONE_SIZE;

	// Define the dead zone boundaries
	float deadZoneLeft = cameraX-16 + (CAMERA_WIDTH - deadZoneWidth) / 2.0f;
	float deadZoneRight = cameraX-16 + (CAMERA_WIDTH + deadZoneWidth) / 2.0f;

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
		cameraX = mapWidth - CAMERA_WIDTH;

	projection = glm::ortho(cameraX, cameraX + float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	updateCam(deltaTime);
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
	map->render();
	player->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{	
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}