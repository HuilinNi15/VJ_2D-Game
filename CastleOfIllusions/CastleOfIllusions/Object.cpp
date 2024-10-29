#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Object.h"
#include "Game.h"



void Object::pickUp(Player* player)
{
	pickedUpBy = player;
	isStatic = false; 
}

void Object::throwObject()
{
	pickedUpBy = NULL;
	vel = THROW_VEL;
}

void Object::breakObject()
{
	vel = glm::vec2(0.f, 0.f); 
	isBroken = true;
}

void Object::render()
{
	if (!isBroken)
		sprite->render();
}


void Stone::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	float x = 0.25f;
	float y = 0.5f;

	animations.resize(2);

	size = glm::ivec2(16, 16);
	addAnimation(STATIC, size, glm::ivec2(16, 16), glm::ivec2(0, 0));
	addAnimation(BREAK, size, glm::ivec2(16, 16), glm::ivec2(0, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	sprite->setAnimationSpeed(STATIC, 1);
	sprite->addKeyframe(STATIC, glm::vec2(x * 0.f, y * 0.f));
	
	sprite->setAnimationSpeed(BREAK, 1);
	sprite->addKeyframe(BREAK, glm::vec2(x * 3.f, y * 1.f));

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
		changeAnimation(BREAK);
}


void Chest::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	float x = 0.25f;
	float y = 0.5f;

	animations.resize(2);

	size = glm::ivec2(16, 16);
	addAnimation(STATIC, size, glm::ivec2(16, 16), glm::ivec2(0, 0));
	addAnimation(BREAK, size, glm::ivec2(16, 16), glm::ivec2(0, 0));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	sprite->setAnimationSpeed(STATIC, 1);
	sprite->addKeyframe(STATIC, glm::vec2(x * 0.f, y * 1.f));

	sprite->setAnimationSpeed(BREAK, 1);
	sprite->addKeyframe(BREAK, glm::vec2(x * 3.f, y * 1.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

	setStatic();
	updateHitBox(STATIC);
	changeAnimation(STATIC);
}

void Chest::breakObject()
{
	Object::breakObject();
	releaseObject();
}

void Chest::releaseObject()
{

}

void Chest::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);

	if (isStatic)
		return;

	if (isBroken)
		changeAnimation(BREAK);
}


void Barrel::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/interactive_objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	float x = 0.25f;
	float y = 0.5f;

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
	bounce++;
	if (bounce == 1)
		vel = BOUNCE_VEL1;
	else if (bounce == 2)
		vel = BOUNCE_VEL2;
	else if (bounce == 3)
	{
		bounce = 0; 
		vel = glm::vec2(0.f, 0.f); 
		isStatic = true; 
	}
}

void Barrel::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);
}