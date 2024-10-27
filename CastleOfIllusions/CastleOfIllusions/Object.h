#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"


const float GRAVITY = 500.0f; // Determined gravity for our world


#pragma once
class Object
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition() const { return pos; };

private:
	virtual void handleMove(float direction);
	void handleJump();
	void handleCrouch();
	void handleInputs(int deltaTime);
	virtual void changeAnimations(int deltaTime);

	glm::ivec2 tileMapDispl;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	glm::vec2 pos, vel, avgVel;
	glm::ivec2 hitBox = glm::ivec2(18, 30);
	glm::ivec2 hitBoxOffset = glm::ivec2(7, 1);
	float dt;
	bool facingRight = true; // if false, then facingLeft
	bool moving = false; // if true, player is moving horizontally (A or D key)
	bool falling = false; 
	bool _static = false; 
};


#endif


