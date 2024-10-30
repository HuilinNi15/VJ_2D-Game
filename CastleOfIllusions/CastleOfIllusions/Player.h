#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include <string>
#include <iomanip>
#include <sstream>

#pragma once
#include "Sprite.h"
#include "MovableEntity.h"


const float MIN_VELOCITY = 20.0f; // Min vel when player moves horizontally
const float MAX_VELOCITY = 100.0f; // Max vel when player moves horizontally
const float ACCELERATION = 120.0f; // Horizontal acceleration
const float JUMP_ACCELERATION = 100.0f; // Horizontal acceleration while jumping
const float STOP_ACCELERATION = 120.0f; // Horizontal deceleration
const float JUMP_VELOCITY = 245.0f; // Initial vel when jumping
const float BOUNCE_VELOCITY = 200.0f; // When killing or breaking an object it bounces back up


class Chest;


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, // 0, 1, 2, 3
	JUMP_LEFT, JUMP_RIGHT, // 4, 5
	BUTT_ATTACK_LEFT, BUTT_ATTACK_RIGHT, BUTT_FALL_LEFT, BUTT_FALL_RIGHT, // 6, 7, 8, 9
	STOP_RIGHT, STOP_LEFT, // 10, 11
	CROUCH_DOWN_LEFT, CROUCH_DOWN_RIGHT, // 12, 13
	PREPARE_PICKUP_LEFT, PREPARE_PICKUP_RIGHT, // 14, 15
	ALMOST_FALLING_LEFT, ALMOST_FALLING_RIGHT,  // 16, 17
	WAVING_HAND, // 18
	CARRY_STAND_LEFT, CARRY_STAND_RIGHT,
	CARRY_MOVE_LEFT, CARRY_MOVE_RIGHT,
	CARRY_JUMP_LEFT, CARRY_JUMP_RIGHT
};


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Object; 


class Player: public MovableEntity
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;

	void addPoints(int addedPoints) { score += addedPoints; };
	void addLives(int addedLives) { lives += addedLives; if (lives > 3) lives = 3; if (lives < 0) alive = false; };
	void removeTry() { tries -= 1; }; 

	int getLives() { return lives; };

	std::string getTries() const {
		std::ostringstream oss;
		oss << std::setw(2) << std::setfill('0') << tries;  // Pads with '0' to a width of 2
		return oss.str();
	}

	std::string getScore() const {
		std::ostringstream oss;
		oss << std::setw(6) << std::setfill('0') << score;  // Pads with '0' to a width of 6
		return oss.str();
	}

protected:
	bool isActive = true;

	void handleMove(float direction);
	void jump(float velocity) { vel.y = -velocity; falling = true; };
	void handleJump();
	void handleCrouch();
	void calculateVelocity() override;
	void otherChanges() override;
	void changeAnimations(int deltaTime) override;

	void pickUp(Object* object) { carrying = object; };
	void throwObject() { carrying = nullptr; };
	void pickUpCakeorCoin(Chest* chest);

	bool facingRight = true; // if false, then facingLeft
	bool stopping = false; // if true, player is slowing down horizontally
	bool attacking = false; // if true, player attacking while jumping
	bool crouching = false; // if true, player is crouched down
	Object* carrying; 

	bool eKeyPreviouslyPressed = false; 

	int lives = 3;
	int tries = 3;
	int score = 0; 
	bool WIN = false; 
	bool alive = true; 
};


#endif // _PLAYER_INCLUDE


