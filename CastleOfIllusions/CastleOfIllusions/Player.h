#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


const float MIN_VELOCITY = 20.0f; // Min vel when player moves horizontally
const float MAX_VELOCITY = 100.0f; // Max vel when player moves horizontally
const float ACCELERATION = 120.0f; // Horizontal acceleration
const float JUMP_ACCELERATION = 100.0f; // Horizontal acceleration while jumping
const float STOP_ACCELERATION = 120.0f; // Horizontal deceleration
const float GRAVITY = 500.0f; // Determined gravity for our world
const float MIN_FALL_VELOCITY = 70.0f; // Min falling vel 
const float JUMP_VELOCITY = 245.0f; // Initial vel when jumping


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,
	JUMP_LEFT, JUMP_RIGHT, 
	BUTT_ATTACK_LEFT, BUTT_ATTACK_RIGHT, BUTT_FALL_LEFT, BUTT_FALL_RIGHT,
	STOP_RIGHT, STOP_LEFT,
	CROUCH_DOWN_LEFT, CROUCH_DOWN_RIGHT,
};


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition() const { return posPlayer; };
	
private:
	void handleMove(float direction);
	void handleJump();
	void handleCrouch();
	void handleInputs(int deltaTime);
	void changeAnimation(PlayerAnims animation);
	void changeAnimations(int deltaTime);

	glm::ivec2 tileMapDispl;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	glm::vec2 posPlayer, velPlayer, avgVelocity;
	glm::ivec2 hitBox = glm::ivec2(18, 30);
	glm::ivec2 hitBoxOffset = glm::ivec2(7, 1);
	float dt; 
	bool facingRight = true; // if false, then facingLeft
	bool moving = false; // if true, player is moving horizontally (A or D key)
	bool stopping = false; // if true, player is slowing down horizontally
	bool jumping = false; // if true, player is jumping
	bool attacking = false; // if true, player attacking while jumping
	bool crouching = false; // if true, player is crouched down
	bool pressedAgain = false; // 
};


#endif // _PLAYER_INCLUDE


