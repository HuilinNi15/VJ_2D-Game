#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Interface.h"

#include <iostream>
#include <irrKlang.h>
using namespace irrklang;


#define SCREEN_WIDTH 256 * 5
#define SCREEN_HEIGHT 192 * 5


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}

	Game();
	~Game();
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;

	ISoundEngine* engine = createIrrKlangDevice();

private:
	bool bPlay = true; // Continue to play game?
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
							    // we can have access at any time
	Scene* mainScreen, * menuScreen, * gameScreen, * currentScreen, * instructionsScreen, * creditsScreen;
};


#endif // _GAME_INCLUDE


