#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


const float GRAVITY = 500.0f; // Determined gravity for our world
const float MIN_FALL_VELOCITY = 70.0f; // Min falling vel 


#pragma once
class Object
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& position);
	glm::ivec2 getPosition() const { return pos; };

protected:
	float dt;

	glm::vec2 pos, vel, avgVel;
	glm::ivec2 size, hitBox, hitBoxOffset;
	bool moving, falling, isStatic, horizontalCollision, verticalCollision;
	virtual void calculateVelocity(int deltaTime); 
	virtual void otherChanges();
	virtual void recalculatePos(const glm::vec2& velStart);

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
	TileMap* map;
};


#endif
