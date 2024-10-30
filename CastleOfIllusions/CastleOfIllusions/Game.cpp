#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.h"
#include "Interface.h"


Game::Game() 
{

}

Game::~Game()
{
	delete currentScreen;
	delete mainScreen;
	delete menuScreen;
	delete gameScreen;
	delete instructionsScreen;
	delete creditsScreen;

	engine->drop();
}

void Game::init()
{
	bPlay = true;
	glClearColor(0.0f, 0.67f, 1.0f, 1.0f);

	engine = createIrrKlangDevice();
	if (!engine) {
		std::cerr << "Unable to create engine" << std::endl;
	}
	engine->play2D("media/IntroTheme.ogg", true); // true = set audio into a loop

	mainScreen = new MainScreen();
	menuScreen = new MenuScreen();
	instructionsScreen = new InstructionsScreen();
	creditsScreen = new CreditsScreen();

	currentScreen = mainScreen;  
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
	if (key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	if (key == GLFW_KEY_SPACE)  // Space key switches screens
	{
		if (currentScreen == mainScreen)
			currentScreen = menuScreen;
		else if (currentScreen == menuScreen)
		{
			int selectedOption = static_cast<MenuScreen*>(currentScreen)->getSelectedOption();

			if (selectedOption == 0)
			{
				gameScreen = new GameScene(true);
				glClearColor(0.0f, 0.67f, 1.0f, 1.0f);
				currentScreen = gameScreen;
				engine->stopAllSounds();
				engine->play2D("media/EnchantedForest.ogg", true);
			}
			else if (selectedOption == 1)
			{
				gameScreen = new GameScene(false);
				glClearColor(0.627f, 0.314f, 1.0f, 1.0f);
				currentScreen = gameScreen;
				engine->stopAllSounds();
				engine->play2D("media/DessertFactory.ogg", true);
			}
			else if (selectedOption == 2)
			{
				currentScreen = instructionsScreen;
			}
			else if (selectedOption == 3)
			{
				currentScreen = creditsScreen;
			}
		}
		else if (currentScreen == creditsScreen || currentScreen == instructionsScreen)
			currentScreen = menuScreen;
	}

	if (key == GLFW_KEY_UP)
	{
		if (currentScreen == menuScreen)
		{
			static_cast<MenuScreen*>(currentScreen)->updateSelection(-1);
			engine->play2D("media/menuOptionSelection.ogg", false);
		}
	}
	else if (key == GLFW_KEY_DOWN)
	{
		if (currentScreen == menuScreen)
		{
			static_cast<MenuScreen*>(currentScreen)->updateSelection(1);
			engine->play2D("media/menuOptionSelection.ogg", false);
		}
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