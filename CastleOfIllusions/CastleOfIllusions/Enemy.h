#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <string>
#include <iomanip>
#include <sstream>
#include "MovableEntity.h"
#include "Player.h"


enum TreeAnims {
	TREE_MOVE_LEFT, TREE_MOVE_RIGHT,
	TREE_DIE_LEFT, TREE_DIE_RIGHT
};


#pragma once
class Enemy : public MovableEntity
{
public: 
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	void setPlayer(Player* p) { player = p; }; 

	void spawn(); 
	void kill(); 
	void instaKill(); 
	bool checkAlive() { return isAlive; }; 
	bool checkKillable() { return isKillable; }; 
	bool checkBounce() { return canBounce; }; 
	bool checkRange() { return isInRange; }; 
	void setIsInRange(bool inRange) { isInRange = inRange; }; 
	void render() override;

protected:
	void detectInRange(); 
	virtual void calculateVelocity() {};
	virtual void otherChanges() override; 
	virtual void changeAnimations(int deltaTime) = 0; 

	Player* player; 

	glm::vec2 initialPosition; 
	bool isInRange = false; 
	bool isAlive = true;
	bool isKillable = true; 
	bool canBounce = true; 
	bool spawned = false; 

	bool doKillAnimation = false; 
};


class Tree : public Enemy
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

protected:
	bool facingRight = true; 

	void calculateDirection();
	void calculateVelocity() override;
	void changeAnimations(int deltaTime) override;
};


//class Plant : public Enemy
//{
//public:
//	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
//
//protected: 
//	bool isStatic = true; 
//	Ball* leftBall;
//	Ball* rightBall; 
//
//	void changeAnimations();
//};
//
//class Ball : public Enemy
//{
//public: 
//	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
//
//protected: 
//	bool isKillable = false; 
//	void calculateVelocity(int deltaTime) override;
//};
//
//
//class ChocolateChip : public Enemy
//{
//public:
//	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
//
//protected:
//	void calculateVelocity(int deltaTime) override;
//};
//
//
//class Donut : public Enemy
//{
//public:
//	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
//
//protected:
//	bool isKillable = false;
//	void calculateVelocity(int deltaTime) override;
//};


#endif