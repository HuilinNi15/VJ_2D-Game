#ifndef _MOVABLE_ENTITY_INCLUDE
#define _MOVABLE_ENTITY_INCLUDE


#pragma once
#include "Sprite.h"


class Object; 
class Enemy; 
class TileMap; 
class Player; 


struct mapData {
	TileMap* map;
	TileMap* decorations;
	Player* player; 
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

	void changeAnimation(int animation, float cooldown = 0.0f);
	bool checkCollision(MovableEntity* other, float* posY, bool bot_or_top, const bool correctPos = true);
	Object* checkCollisionEntities(std::vector<Object*> entities, bool bot_or_top, bool correctPos = true);
	Enemy* checkCollisionEntities(std::vector<Enemy*> entities, bool bot_or_top, bool correctPos = true);

	void setTileMap(mapData* tileMap);
	void setPosition(const glm::vec2& position);
	glm::vec2 getPosition() const { return pos; };
	glm::vec2 getVelocity() const { return vel; };
	glm::ivec2 getSize() const { return size; };
	glm::ivec2 getHitBox() const { return hitBox; };
	glm::ivec2 getHitBoxOffset() const { return hitBoxOffset; };	
	bool collisionInCooldown() const { return collisionCooldown > 0; };
	bool animationInCooldown() const { return animationCooldown > 0; };
	bool deactivateInCooldown() const { return deactivateCooldown > 0; };
	
	bool getInvisible() { return renderObject; };
	bool getActive() { return isActive; }; 
	bool getStatic() { return isStatic; }; 
	void setInvisible(); 
	void setActive();
	void setStatic();

	void destroy() { renderObject = false;  };

	bool renderObject = true; 

protected:
	bool isActive = true; 
	bool isStatic; 
	bool collideWithMap = true; 
	bool collideWithEntities = true; 

	float collisionCooldown = 0.0f;
	float animationCooldown = 0.0f; 
	float deactivateCooldown = 0.0f;
	float nextActionCooldown = 0.0f; 

	float dt;

	glm::vec2 pos, vel, avgVel;
	glm::ivec2 size, hitBox, hitBoxOffset;
	bool moving, falling, horizontalCollision, topCollision, downCollision;
	Enemy* collidedEnemyX;
	Enemy* collidedEnemyY;
	Object* collidedObjectX;
	Object* collidedObjectY;
	virtual void calculateVelocity(); 
	virtual void otherChanges();
	virtual void recalculatePos(const glm::vec2& velStart, bool MapCollision = true, bool EntityCollsion = true);

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
