#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "MovableEntity.h"


const float MIN_VELOCITY = 20.0f; // Min vel when player moves horizontally
const float MAX_VELOCITY = 100.0f; // Max vel when player moves horizontally
const float ACCELERATION = 120.0f; // Horizontal acceleration
const float JUMP_ACCELERATION = 100.0f; // Horizontal acceleration while jumping
const float STOP_ACCELERATION = 120.0f; // Horizontal deceleration
const float JUMP_VELOCITY = 245.0f; // Initial vel when jumping


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, // 0, 1, 2, 3
	JUMP_LEFT, JUMP_RIGHT, // 4, 5
	BUTT_ATTACK_LEFT, BUTT_ATTACK_RIGHT, BUTT_FALL_LEFT, BUTT_FALL_RIGHT, // 6, 7, 8, 9
	STOP_RIGHT, STOP_LEFT, // 10, 11
	CROUCH_DOWN_LEFT, CROUCH_DOWN_RIGHT, // 12, 13
	PREPARE_PICKUP_LEFT, PREPARE_PICKUP_RIGHT, // 14, 15
	ALMOST_FALLING_LEFT, ALMOST_FALLING_RIGHT,  // 16, 17
	WAVING_HAND // 18
};


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player: public MovableEntity
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;

private:
	void handleMove(float direction);
	void handleJump();
	void handleCrouch();
	void calculateVelocity(int deltaTime) override;
	void otherChanges() override;
	void changeAnimation(PlayerAnims animation);
	void changeAnimations(int deltaTime) override;

	bool facingRight = true; // if false, then facingLeft
	bool stopping = false; // if true, player is slowing down horizontally
	bool attacking = false; // if true, player attacking while jumping
	bool crouching = false; // if true, player is crouched down
};


#endif // _PLAYER_INCLUDE


