#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Interface.h"


Game::Game() 
{

}

Game::~Game()
{
	delete mainScreen;
	delete menuScreen;
	delete gameScreen;
}

void Game::init()
{
	bPlay = true;
	glClearColor(0.0f, 0.67f, 1.0f, 1.0f);
	mainScreen = new MainScreen();
	menuScreen = new MenuScreen();
	gameScreen = new GameScene(); 
	currentScreen = mainScreen;  // Aquí puedes usar el puntero de tipo Interface
}

bool Game::update(int deltaTime)
{
	currentScreen->update(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScreen->render();
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	if (key == GLFW_KEY_SPACE)  // Space key switches screens
	{
		if (currentScreen == mainScreen)
			currentScreen = gameScreen;
		else
			currentScreen = mainScreen;
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}