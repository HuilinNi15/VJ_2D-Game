#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Interface.h"
#include "Player.h"


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



GameScene::GameScene(string level)
{
	map.map = TileMap::createTileMap(level, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map.decorations = TileMap::createTileMap(level, glm::vec2(SCREEN_X, SCREEN_Y), texProgram, true);
	
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map.map->getTileSize(), INIT_PLAYER_Y_TILES * map.map->getTileSize()));
	player->setTileMap(map.map);

	// Load the Life Bar texture
	lifeBarTexture.loadFromFile("images/screens/LifeBar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	lifeBarTexture.setMinFilter(GL_NEAREST);
	lifeBarTexture.setMagFilter(GL_NEAREST);

	float x = 1.0;
	float y = 0.25;

	size = glm::ivec2(256, 32);

	// Create the background sprite
	lifeBarSprite = Sprite::createSprite(size, glm::vec2(x, y), &lifeBarTexture, &texProgram);
	lifeBarSprite->setNumberAnimations(4);

	lifeBarSprite->setAnimationSpeed(ZERO_STAR, 1);
	lifeBarSprite->addKeyframe(ZERO_STAR, glm::vec2(x * 0.f, y * 0.f));

	lifeBarSprite->setAnimationSpeed(ONE_STAR, 1);
	lifeBarSprite->addKeyframe(ONE_STAR, glm::vec2(x * 0.f, y * 1.f));

	lifeBarSprite->setAnimationSpeed(TWO_STARS, 1);
	lifeBarSprite->addKeyframe(TWO_STARS, glm::vec2(x * 0.f, y * 2.f));

	lifeBarSprite->setAnimationSpeed(THREE_STARS, 1);
	lifeBarSprite->addKeyframe(THREE_STARS, glm::vec2(x * 0.f, y * 3.f));


	lifeBarSprite->changeAnimation(THREE_STARS);
	lifeBarSprite->setPosition(glm::vec2(0.f, 160.f)); // Position the background at (0, 160)


	// Select which font you want to use
	if (!text.init("fonts/zx_spectrum-7_bold.ttf"))
		cout << "Could not load font!!!" << endl;
}

GameScene::~GameScene()
{
	delete map.map;
	delete map.decorations;
	delete player;

	delete lifeBarSprite;
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

	lifeBarSprite->changeAnimation(player->getLives());
}

void GameScene::render()
{
	Scene::render();
	map.decorations->render();
	map.map->render();
	player->render();

	lifeBarSprite->render();

	text.render(player->getTries(), glm::vec2(600, 900), 32, glm::vec4(1, 1, 1, 1));
	text.render(player->getScore(), glm::vec2(765, 900), 32, glm::vec4(1, 1, 1, 1));
	text.render(getCurrentTime(), glm::vec2(1060, 900), 32, glm::vec4(1, 1, 1, 1));
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
	mickeySprite->init(glm::ivec2(112, 128), texProgram); // Mickey sprite position
	mickeySprite->changeAnimation(WAVING_HAND); // Waving animation
	mickeySprite->setStatic();

	// Load the text texture
	textTexture.loadFromFile("images/screens/press_spacebar_MainScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	textTexture.setMinFilter(GL_NEAREST);
	textTexture.setMagFilter(GL_NEAREST);

	// Create the text sprite
	textSprite = Sprite::createSprite(glm::ivec2(52, 28), glm::vec2(1.0f, 1.0f), &textTexture, &texProgram);
	textSprite->setNumberAnimations(1);
	textSprite->setAnimationSpeed(0, 1);
	textSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	textSprite->changeAnimation(0);
	textSprite->setPosition(glm::vec2(176.f, 120.f)); // Position the background at (0, 0)
}

MainScreen::~MainScreen()
{
    delete backgroundSprite;
    delete mickeySprite;
	delete textSprite;
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
	textSprite->render();
}



MenuScreen::MenuScreen()
{
	selectedOption = 0;

	// Load the background texture
	backgroundTexture.loadFromFile("images/screens/black_screen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	// Create the background sprite
	backgroundSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &backgroundTexture, &texProgram);
	backgroundSprite->setNumberAnimations(1);
	backgroundSprite->setAnimationSpeed(0, 1);
	backgroundSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	backgroundSprite->changeAnimation(0);
	backgroundSprite->setPosition(glm::vec2(0, 0)); // Position the background at (0, 0)

	
	optionsTexture.loadFromFile("images/screens/options_MenuScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	optionsTexture.setMinFilter(GL_NEAREST);
	optionsTexture.setMagFilter(GL_NEAREST);

	float x = 1.0;
	float y = 0.125;

	size = glm::ivec2(128, 8);

	practiceSprite = Sprite::createSprite(size, glm::vec2(x, y), &optionsTexture, &texProgram);
	practiceSprite->setNumberAnimations(2);

	practiceSprite->setAnimationSpeed(0, 1);
	practiceSprite->addKeyframe(0, glm::vec2(x * 0.f, y * 0.f));

	practiceSprite->setAnimationSpeed(1, 1);
	practiceSprite->addKeyframe(1, glm::vec2(x * 0.f, y * 1.f));

	// Create the normal level sprite
	normalSprite = Sprite::createSprite(size, glm::vec2(x, y), &optionsTexture, &texProgram);
	normalSprite->setNumberAnimations(2);

	normalSprite->setAnimationSpeed(0, 1);
	normalSprite->addKeyframe(0, glm::vec2(x * 0.f, y * 2.f));

	normalSprite->setAnimationSpeed(1, 1);
	normalSprite->addKeyframe(1, glm::vec2(x * 0.f, y * 3.f));

	// Create the instructions screen sprite
	instructionsSprite = Sprite::createSprite(size, glm::vec2(x, y), &optionsTexture, &texProgram);
	instructionsSprite->setNumberAnimations(2);
 
	instructionsSprite->setAnimationSpeed(0, 1);
	instructionsSprite->addKeyframe(0, glm::vec2(x * 0.f, y * 4.f));

	instructionsSprite->setAnimationSpeed(1, 1);
	instructionsSprite->addKeyframe(1, glm::vec2(x * 0.f, y * 5.f));

	// Create the credits screen sprite
	creditsSprite = Sprite::createSprite(size, glm::vec2(x, y), &optionsTexture, &texProgram);
	creditsSprite->setNumberAnimations(2);

	creditsSprite->setAnimationSpeed(0, 1);
	creditsSprite->addKeyframe(0, glm::vec2(x * 0.f, y * 6.f));

	creditsSprite->setAnimationSpeed(1, 1);
	creditsSprite->addKeyframe(1, glm::vec2(x * 0.f, y * 7.f));

	// Set position
	practiceSprite->changeAnimation(1);
	practiceSprite->setPosition(glm::vec2(66.f, 72.5f));

	normalSprite->changeAnimation(0);
	normalSprite->setPosition(glm::vec2(66.f, 85.5f));

	instructionsSprite->changeAnimation(0);
	instructionsSprite->setPosition(glm::vec2(66.f, 98.5f));

	creditsSprite->changeAnimation(0);
	creditsSprite->setPosition(glm::vec2(66.f, 111.5f));
}

MenuScreen::~MenuScreen()
{
	delete backgroundSprite;
	delete practiceSprite;
	delete normalSprite;
	delete instructionsSprite;
	delete creditsSprite;
}

void MenuScreen::updateSelection(int selection)
{
	selectedOption += selection;

	if (selectedOption < 0)
		selectedOption = 0;
	else if (selectedOption > 3)
		selectedOption = 3;
}

int MenuScreen::getSelectedOption()
{
	return selectedOption;
}

void MenuScreen::update(int deltaTime) 
{
	Scene::update(deltaTime);

	practiceSprite->changeAnimation(0);
	normalSprite->changeAnimation(0);
	instructionsSprite->changeAnimation(0);
	creditsSprite->changeAnimation(0);

	if (selectedOption == 0)
		practiceSprite->changeAnimation(1);
	else if (selectedOption == 1)
		normalSprite->changeAnimation(1);
	else if (selectedOption == 2)
		instructionsSprite->changeAnimation(1);
	else if (selectedOption == 3)
		creditsSprite->changeAnimation(1);
}

void MenuScreen::render() 
{
	Scene::render();
	backgroundSprite->render();
	practiceSprite->render();
	normalSprite->render();
	instructionsSprite->render();
	creditsSprite->render();
}


InstructionsScreen::InstructionsScreen() 
{
	// Load the background texture
	backgroundTexture.loadFromFile("images/screens/black_screen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	// Create the background sprite
	backgroundSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &backgroundTexture, &texProgram);
	backgroundSprite->setNumberAnimations(1);
	backgroundSprite->setAnimationSpeed(0, 1);
	backgroundSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	backgroundSprite->changeAnimation(0);
	backgroundSprite->setPosition(glm::vec2(0, 0)); // Position the background at (0, 0)


	// Load the Instructions texture
	instructionsTexture.loadFromFile("images/screens/InstructionsScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructionsTexture.setMinFilter(GL_NEAREST);
	instructionsTexture.setMagFilter(GL_NEAREST);

	// Create the Instructions sprite
	instructionsSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &instructionsTexture, &texProgram);
	instructionsSprite->setNumberAnimations(1);
	instructionsSprite->setAnimationSpeed(0, 1);
	instructionsSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	instructionsSprite->changeAnimation(0);
	instructionsSprite->setPosition(glm::vec2(0, 0)); // Position the background at (0, 0)
}

InstructionsScreen::~InstructionsScreen()
{
	delete backgroundSprite;
	delete instructionsSprite;
}

void InstructionsScreen::update(int deltaTime) 
{
	Scene::update(deltaTime);
}

void InstructionsScreen::render() 
{
	Scene::render();
	backgroundSprite->render();
	instructionsSprite->render();
}


CreditsScreen::CreditsScreen()
{
	// Load the background texture
	backgroundTexture.loadFromFile("images/screens/black_screen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	// Create the background sprite
	backgroundSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &backgroundTexture, &texProgram);
	backgroundSprite->setNumberAnimations(1);
	backgroundSprite->setAnimationSpeed(0, 1);
	backgroundSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	backgroundSprite->changeAnimation(0);
	backgroundSprite->setPosition(glm::vec2(0, 0)); // Position the background at (0, 0)


	// Load the Instructions texture
	creditsTexture.loadFromFile("images/screens/CreditsScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	creditsTexture.setMinFilter(GL_NEAREST);
	creditsTexture.setMagFilter(GL_NEAREST);

	// Create the Instructions sprite
	creditsSprite = Sprite::createSprite(glm::ivec2(256, 192), glm::vec2(1.0f, 1.0f), &creditsTexture, &texProgram);
	creditsSprite->setNumberAnimations(1);
	creditsSprite->setAnimationSpeed(0, 1);
	creditsSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	creditsSprite->changeAnimation(0);
	creditsSprite->setPosition(glm::vec2(0, 0)); // Position the background at (0, 0)
}

CreditsScreen::~CreditsScreen()
{
	delete backgroundSprite;
	delete creditsSprite;
}

void CreditsScreen::update(int deltaTime) 
{
	Scene::update(deltaTime);
}

void CreditsScreen::render() 
{
	backgroundSprite->render();
	creditsSprite->render();
}