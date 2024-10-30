#include <iostream>
#include <GL/glew.h>
#include "Enemy.h"


void Enemy::spawn()
{
	sprite->setPosition(initialPosition);
	spawned = true; 

	isAlive = true;
	renderObject = true;
	isActive = true;
	isStatic = false;

	collideWithMap = true;
	collideWithEntities = true;
}


void Enemy::kill()
{
	if (isAlive)
	{
		doKillAnimation = true;
		nextActionCooldown = 1.0f;
		collideWithMap = false;
		collideWithEntities = false;
	}
}

void Enemy::instaKill()
{
	isAlive = false;
	renderObject = false;
	isActive = false;
	isStatic = true;
	doKillAnimation = false;
	collideWithMap = false;
	collideWithEntities = false;
	spawned = false; 
}

void Enemy::render()
{
	if (isAlive && renderObject)
	{
		sprite->render();
	}
}

void Enemy::detectInRange()
{
	glm::vec2 playerPos = player->getPosition();
	float horizontalDistance = std::abs(playerPos.x - initialPosition.x);
	float verticalDistance = std::abs(playerPos.y - initialPosition.y);

	std::cout << horizontalDistance << " " << verticalDistance << std::endl; 

	const float horizontalRangeThreshold = 100.0f;
	const float verticalRangeThreshold = 20.0f;   

	isInRange = (horizontalDistance <= horizontalRangeThreshold) &&
		(verticalDistance <= verticalRangeThreshold);
}

void Enemy::otherChanges()
{
	detectInRange(); 

	if (doKillAnimation && nextActionCooldown <= 0.0f) {
		instaKill(); 
	}
	if (isInRange)
	{
		if (!spawned)
		{
			spawn();
		}
	}
	else if (isAlive)
	{
		instaKill(); 
	}
}



void Tree::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/enemies_forest.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	animations.resize(4);

	float x = 0.25f;
	float y = 0.25f;

	size = glm::ivec2(32, 32);

	addAnimation(TREE_MOVE_LEFT, size, glm::ivec2(26, 32), glm::ivec2(3, 0));
	addAnimation(TREE_MOVE_RIGHT, size, glm::ivec2(26, 32), glm::ivec2(3, 0));
	addAnimation(TREE_DIE_LEFT, size, glm::ivec2(26, 32), glm::ivec2(3, 0));
	addAnimation(TREE_DIE_RIGHT, size, glm::ivec2(26, 32), glm::ivec2(3, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

		sprite->setAnimationSpeed(TREE_MOVE_LEFT, 10);
		sprite->addKeyframe(TREE_MOVE_LEFT, glm::vec2(x * 0.f, y * 1.f));
		sprite->addKeyframe(TREE_MOVE_LEFT, glm::vec2(x * 1.f, y * 1.f));
		//sprite->addKeyframe(TREE_MOVE_LEFT, glm::vec2(x * 0.f, y * 0.f));

		sprite->setAnimationSpeed(TREE_MOVE_RIGHT, 10);
		sprite->addKeyframe(TREE_MOVE_RIGHT, glm::vec2(x * 0.f, y * 0.f));
		sprite->addKeyframe(TREE_MOVE_RIGHT, glm::vec2(x * 1.f, y * 0.f));
		//sprite->addKeyframe(TREE_MOVE_RIGHT, glm::vec2(x * 0.f, y * 0.f));

		sprite->setAnimationSpeed(TREE_DIE_LEFT, 1);
		sprite->addKeyframe(TREE_DIE_LEFT, glm::vec2(x * 3.f, y * 1.f));

		sprite->setAnimationSpeed(TREE_DIE_RIGHT, 1);
		sprite->addKeyframe(TREE_DIE_RIGHT, glm::vec2(x * 3.f, y * 0.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	initialPosition = glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)); 

	changeAnimation(TREE_MOVE_LEFT);
	updateHitBox(TREE_MOVE_LEFT);
	isStatic = false; 
	kill(); 
}

void Tree::calculateDirection()
{

}

void Tree::calculateVelocity()
{

}

void Tree::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);

	if (isStatic)
		return;

	if (doKillAnimation)
	{
		if (facingRight)
		{
			changeAnimation(TREE_DIE_RIGHT);
			updateHitBox(TREE_DIE_RIGHT);
		}
		else
		{
			changeAnimation(TREE_DIE_LEFT);
			updateHitBox(TREE_DIE_LEFT);
		}
	}
	else
	{
		if (facingRight)
		{
			changeAnimation(TREE_MOVE_RIGHT);
			updateHitBox(TREE_MOVE_RIGHT);
		}
		else
		{
			changeAnimation(TREE_MOVE_LEFT);
			updateHitBox(TREE_MOVE_LEFT);
		}
	}
}