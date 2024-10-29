#include "MovableEntity.h"
#include "Game.h"
#include <iostream>
#include <GL/glew.h>



void MovableEntity::addAnimation(int animId, const glm::ivec2& size, const glm::ivec2& hitBox, const glm::ivec2& hitBoxOffset)
{
	animations[animId] = { size, hitBox, hitBoxOffset };
}

void MovableEntity::changeAnimation(int animation)
{
	if (sprite->animation() != animation)
		sprite->changeAnimation(animation);
}

void MovableEntity::updateHitBox(int animId)
{
	hitBox = animations[animId].hitBox;
	hitBoxOffset = animations[animId].hitBoxOffset;
}


void MovableEntity::update(int deltaTime)
{
	glm::vec2 velStart = vel;
	dt = deltaTime / 1000.0f;

	if (!isStatic && map->map != NULL)
		calculateVelocity(deltaTime);
	
	changeAnimations(deltaTime);

	if (!isStatic && map->map != NULL)
		recalculatePos(velStart);

	otherChanges();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}


void MovableEntity::calculateVelocity(int deltaTime)
{
}


void MovableEntity::otherChanges()
{
}


void MovableEntity::recalculatePos(const glm::vec2& velStart)
{
	avgVel.x = (velStart.x + vel.x) / 2.0f;
	pos.x += avgVel.x * dt;

	horizontalCollision = false; 
	if (vel.x > 0.0f)
		horizontalCollision = map->map->collisionMoveRight(pos, hitBox, hitBoxOffset);
	else if (vel.x < 0.0f)
		horizontalCollision = map->map->collisionMoveLeft(pos, hitBox, hitBoxOffset);
	
	if (!horizontalCollision && vel.x != 0.0f) {
		collidedEnemy = checkCollisionEntities(map->enemies, false);
		collidedObject = checkCollisionEntities(map->objects, false); 

		if (collidedObject)
		{
			horizontalCollision = true; 
		}
	}
	
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
	topCollision = false; 
	downCollision = false; 

	if (map->map->collisionMoveDown(pos, hitBox, hitBoxOffset, &pos.y))
	{
		vel.y = 0.0f;
		falling = false;
		topCollision = true;
	}
	else if (map->map->collisionMoveUp(pos, hitBox, hitBoxOffset, &pos.y))
	{
		vel.y = 0.0f;
		falling = true;
		downCollision = true;
	}
	else
	{
		falling = true;
	}

	if (!topCollision && !downCollision)
	{
		collidedEnemy = checkCollisionEntities(map->enemies, true);
		collidedObject = checkCollisionEntities(map->objects, true);

		if (collidedObject)
		{
			std::cout << "COLLIDE" << std::endl;
			if (vel.y >= 0)
				falling = false;
			vel.y = 0.0f;
		}
	}
}


bool MovableEntity::checkCollision(MovableEntity* other, float* posY, bool bot_or_top, const bool correctPos)
{
	float left = pos.x + hitBoxOffset.x, right = left + hitBox.x;
	float top = pos.y + hitBoxOffset.y, bottom = top + hitBox.y;
	float otherLeft = other->pos.x + other->hitBoxOffset.x, otherRight = otherLeft + other->hitBox.x;
	float otherTop = other->pos.y + other->hitBoxOffset.y, otherBottom = otherTop + other->hitBox.y;

	bool collision = right > otherLeft && left < otherRight && bottom > otherTop && top < otherBottom;

	if (collision)
	{
		if (bot_or_top)
		{
			if (vel.y < 0 && correctPos) // Correct position to be on top
			{
				*posY = otherBottom - hitBoxOffset.y;
				topCollision = true;
			}
			else if (correctPos) // Correct position to be underneath
			{
				*posY = otherTop - hitBoxOffset.y - hitBox.y;
				downCollision = true; 
			}
		}
	}

	return collision;
}

Object* MovableEntity::checkCollisionEntities(std::vector<Object*> entities, bool bot_or_top, bool correctPos)
{
	for (Object* entity : entities) {
		if (entity == this) continue; 
		if (checkCollision(entity, &pos.y, bot_or_top, correctPos))
			return entity; 
	}
	return nullptr;
}

Enemy* MovableEntity::checkCollisionEntities(std::vector<Enemy*> entities, bool bot_or_top, bool correctPos)
{
	for (Enemy* entity : entities) 
	{
		if (entity == this) continue; 
		if (checkCollision(entity, &pos.y, bot_or_top, correctPos))
			return entity;
	}
	return nullptr;
}


bool MovableEntity::isColliding()
{
	return false; 
}


void MovableEntity::render()
{
	sprite->render();
}

void MovableEntity::setStatic()
{
	isStatic = !isStatic;
}

void MovableEntity::setTileMap(mapData* tileMap)
{
	map = tileMap;
}

void MovableEntity::setPosition(const glm::vec2& position)
{
	pos = position;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}