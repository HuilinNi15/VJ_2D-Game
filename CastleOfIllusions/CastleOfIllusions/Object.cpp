#include "Object.h"
#include "Game.h"
#include <iostream>
#include <GL/glew.h>



void Object::addAnimation(int animId, const glm::ivec2& size, const glm::ivec2& hitBox, const glm::ivec2& hitBoxOffset)
{
	animations[animId] = { size, hitBox, hitBoxOffset };
}


void Object::updateHitBox(int animId)
{
	hitBox = animations[animId].hitBox;
	hitBoxOffset = animations[animId].hitBoxOffset;
}


void Object::update(int deltaTime)
{
	glm::vec2 velStart = vel;

	if (!isStatic) {
		calculateVelocity(deltaTime);
		changeAnimations(deltaTime);
		recalculatePos(velStart);
		otherChanges();
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	}
}


void Object::calculateVelocity(int deltaTime)
{
}


void Object::otherChanges()
{
}


void Object::recalculatePos(const glm::vec2& velStart)
{
	avgVel.x = (velStart.x + vel.x) / 2.0f;
	pos.x += avgVel.x * dt;

	horizontalCollision = false; 
	if (vel.x > 0.0f)
		horizontalCollision = map->collisionMoveRight(pos, hitBox, hitBoxOffset);
	else if (vel.x < 0.0f)
		horizontalCollision = map->collisionMoveLeft(pos, hitBox, hitBoxOffset);
	if (horizontalCollision)
	{
		pos.x -= avgVel.x * dt;
		vel.x = 0.0f;
	}

	vel.y += GRAVITY * dt;
	avgVel.y = (velStart.y + vel.y) / 2.0f;
	if (avgVel.y < MIN_FALL_VELOCITY && !falling)
		avgVel.y = MIN_FALL_VELOCITY;
	pos.y += avgVel.y * dt;
	verticalCollision = false; 
	if (map->collisionMoveDown(pos, hitBox, hitBoxOffset, &pos.y))
	{
		vel.y = 0.0f;
		falling = false;
		verticalCollision = true;
	}
	else
	{
		verticalCollision = false; 
		falling = true;
	}
}



void Object::render()
{
	sprite->render();
}

void Object::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Object::setPosition(const glm::vec2& position)
{
	pos = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}