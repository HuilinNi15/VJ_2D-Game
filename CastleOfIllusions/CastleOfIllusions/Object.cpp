#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <random>
#include "Object.h"
#include "Game.h"


const float x = 0.2f;
const float y = 0.5f;


void Object::pickUp(Player* player)
{
	pickedUpBy = player;
	isStatic = true; 
	isActive = false; 
}

void Object::throwObject(glm::vec2 velocity)
{
	isActive = true; 
	isStatic = false; 
	pickedUpBy = NULL;
	vel = velocity;
	collisionCooldown = 0.5f;
}

void Object::breakObject()
{
	if (!justBroken)
	{
		vel = glm::vec2(0.f, 0.f); 
		isStatic = true; 
		isActive = false;
		justBroken = true; 
		deactivateCooldown = 0.5; 
		changeAnimation(BREAK, 0.5f);
	}
}

void Object::deactivating()
{
	if (justBroken && deactivateCooldown < 0.0f)
	{
		isBroken = true;
		justBroken = false;
	}
}


void Object::breakOtherObject(Object* object)
{
	breakObject();
	object->breakObject();
	object = nullptr;
}

void Object::otherChanges()
{
	deactivating();
	if (!isBroken)
	{
		if (collidedObjectX)
			breakOtherObject(collidedObjectX);
		else if (collidedObjectY)
			breakOtherObject(collidedObjectY);

		else if (collidedEnemyX)
		{
			breakObject();
			//KILL ENEMY
		}
		else if (collidedEnemyY)
		{
			breakObject();
			// KILL ENEMY
		}

		if (pickedUpBy)
		{
			glm::vec2 pPlayer = pickedUpBy->getPosition();
			glm::vec2 hPlayer = pickedUpBy->getHitBoxOffset();
			float x, y;
			x = pPlayer.x + hPlayer.x;
			y = pPlayer.y + hPlayer.y - hitBox.y / 2.f;
			pos = glm::vec2(x, y);
		}
		else if (topCollision && !isStatic)
		{
			breakObject();
		}
	}
}

void Object::render()
{
	if (!isBroken && renderObject)
	{
		sprite->render();
	}
}


void Stone::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	animations.resize(2);

	size = glm::ivec2(16, 16);
	addAnimation(STATIC, size, glm::ivec2(16, 16), glm::ivec2(0, 0));
	addAnimation(BREAK, size, glm::ivec2(16, 16), glm::ivec2(0, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	sprite->setAnimationSpeed(STATIC, 1);
	sprite->addKeyframe(STATIC, glm::vec2(x * 0.f, y * 0.f));
	
	sprite->setAnimationSpeed(BREAK, 1);
	sprite->addKeyframe(BREAK, glm::vec2(x * 4.f, y * 0.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	setStatic();
	updateHitBox(STATIC);
	changeAnimation(STATIC);
}

void Stone::changeAnimations(int deltaTime) 
{
	sprite->update(deltaTime);

	if (isStatic)
		return;

	if (isBroken)
		changeAnimation(BREAK, 0.5f);
}



void Chest::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	animations.resize(4);

	size = glm::ivec2(16, 16);
	addAnimation(STATIC, size, glm::ivec2(16, 16), glm::ivec2(0, 0));
	addAnimation(BREAK, size, glm::ivec2(16, 16), glm::ivec2(0, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	sprite->setAnimationSpeed(STATIC, 1);
	sprite->addKeyframe(STATIC, glm::vec2(x * 0.f, y * 1.f));

	sprite->setAnimationSpeed(BREAK, 1);
	sprite->addKeyframe(BREAK, glm::vec2(x * 4.f, y * 0.f));

	sprite->setAnimationSpeed(CAKE, 1);
	sprite->addKeyframe(CAKE, glm::vec2(x * 2.f, y * 0.f));

	sprite->setAnimationSpeed(COIN, 1);
	sprite->addKeyframe(COIN, glm::vec2(x * 3.f, y * 0.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	setStatic();
	updateHitBox(STATIC);
	changeAnimation(STATIC);
}

void Chest::breakObject()
{
	if (!justBroken)
	{
		throwObject(glm::vec2(0.f, -150.f));
		isActive = false;
		justBroken = true;
		collisionCooldown = 0.5f; 
		deactivateCooldown = 2.0f;
		releaseObject();
	}
}

void Chest::releaseObject()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, 1);
	int randomValue = distrib(gen);

	if (randomValue == 0)
	{
		changeAnimation(CAKE);
		state = CAKE;
	}
	else if (randomValue == 1)
	{
		changeAnimation(COIN);
		state = COIN;
	}
}

void Chest::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);
}


void Barrel::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	animations.resize(1);

	size = glm::ivec2(16, 16);
	addAnimation(STATIC, size, glm::ivec2(16, 16), glm::ivec2(0, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	sprite->setAnimationSpeed(STATIC, 1);
	sprite->addKeyframe(STATIC, glm::vec2(x * 2.f, y * 1.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	setStatic(); 
	updateHitBox(STATIC);
	changeAnimation(STATIC);
}


void Barrel::breakObject()
{
	if (topCollision)
	{
		vel = glm::vec2(0.f, 0.f);
		isStatic = true;
		topCollision = false;
	}
}

void Barrel::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);
}



void Gem::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	animations.resize(1);

	size = glm::ivec2(16, 16);
	addAnimation(STATIC, size, glm::ivec2(16, 16), glm::ivec2(0, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	sprite->setAnimationSpeed(STATIC, 1);
	sprite->addKeyframe(STATIC, glm::vec2(x * 1.f, y * 0.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	setStatic();
	updateHitBox(STATIC);
	changeAnimation(STATIC);
}

void Gem::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);
}

void Gem::otherChanges()
{
	
}
