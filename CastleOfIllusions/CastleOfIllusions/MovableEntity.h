#ifndef _MOVABLE_ENTITY_INCLUDE
#define _MOVABLE_ENTITY_INCLUDE


#pragma once
#include "Sprite.h"


class Object; 
class Enemy; 
class TileMap; 


struct mapData {
	TileMap* map;
	TileMap* decorations;
	Object* object; 
	std::vector<Enemy*> enemies;
	std::vector<Object*> objects;
};


const float GRAVITY = 500.0f; // Determined gravity for our world
const float MIN_FALL_VELOCITY = 70.0f; // Min falling vel 


class MovableEntity
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0; 
	virtual void update(int deltaTime);
	virtual void render();

	void changeAnimation(int animation);
	bool checkCollision(MovableEntity* other, float* posY, bool bot_or_top, const bool correctPos = true);
	Object* checkCollisionEntities(std::vector<Object*> entities, bool bot_or_top, bool correctPos = true);
	Enemy* checkCollisionEntities(std::vector<Enemy*> entities, bool bot_or_top, bool correctPos = true);

	void setStatic();
	void setTileMap(mapData* tileMap);
	void setPosition(const glm::vec2& position);
	glm::vec2 getPosition() const { return pos; };
	glm::vec2 getVelocity() const { return vel; };
	glm::ivec2 getSize() const { return size; };
	glm::ivec2 getHitBox() const { return hitBox; };
	glm::ivec2 getHitBoxOffset() const { return hitBoxOffset; };

protected:
	float dt;

	glm::vec2 pos, vel, avgVel;
	glm::ivec2 size, hitBox, hitBoxOffset;
	bool moving, falling, isStatic, horizontalCollision, topCollision, downCollision;
	Enemy* collidedEnemy;
	Object* collidedObject;
	virtual void calculateVelocity(int deltaTime); 
	virtual void otherChanges();
	virtual void recalculatePos(const glm::vec2& velStart);

	bool isColliding(); 

	struct AnimationData {
		glm::ivec2 size;
		glm::ivec2 hitBox;
		glm::ivec2 hitBoxOffset;
	};
	std::vector<AnimationData> animations;
	void addAnimation(int animId, const glm::ivec2& size, const glm::ivec2& hitBox, const glm::ivec2& hitBoxOffset);
	void updateHitBox(int animId); // update hitbox based on current animation
	virtual void changeAnimations(int deltaTime) = 0;

	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
	mapData* map;
};


#endif
