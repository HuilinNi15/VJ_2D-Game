#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,
	JUMP_LEFT, JUMP_RIGHT, BUTT_ATTACK,
	STOP_RIGHT, STOP_LEFT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	//spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.loadFromFile("images/mickey.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	float x = 0.0625; 
	float y = 0.125; 
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 4);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(x * 0.f, y * 1.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(x * 1.f, y * 1.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 4);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(x * 0.f, y * 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(x * 1.f, y * 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 25);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 2.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 3.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 4.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 5.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 6.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 7.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 8.f, y * 1.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x * 9.f, y * 1.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 25);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 2.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 3.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 4.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 5.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 6.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 7.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 8.f, y * 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x * 9.f, y * 0.f));

		sprite->setAnimationSpeed(JUMP_LEFT, 1);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(x * 2.f, y * 3.f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(x * 3.f, y * 3.f));
		//sprite->addKeyframe(JUMP_LEFT, glm::vec2(x * 4.f, y * 3.f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 1);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 2.f, y * 2.f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 3.f, y * 2.f));
		//sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 4.f, y * 2.f));

		sprite->setAnimationSpeed(STOP_LEFT, 2);
		sprite->addKeyframe(STOP_LEFT, glm::vec2(x * 9.f, y * 1.f));

		sprite->setAnimationSpeed(STOP_RIGHT, 2);
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(x * 9.f, y * 0.f));

		//sprite->setAnimationSpeed(BUTT_ATTACK, 2);

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getKey(GLFW_KEY_A))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getKey(GLFW_KEY_D))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	} 
	else if (Game::instance().getKey(GLFW_KEY_W))
	{
		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(JUMP_LEFT);
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(JUMP_RIGHT);

		if (!bJumping) {
			bJumping = true;
			jumpAngle = 0;
			startY = posPlayer.y;
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_S))
	{

	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180) {
			bJumping = false;
			posPlayer.y = startY;
			
			if (sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == JUMP_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				//bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
				if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
					bJumping = false;
					if (sprite->animation() == JUMP_LEFT)
						sprite->changeAnimation(STAND_LEFT);
					else if (sprite->animation() == JUMP_RIGHT)
						sprite->changeAnimation(STAND_LEFT);
				}
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getKey(GLFW_KEY_W)){
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			} else {
				if (sprite->animation() == JUMP_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == JUMP_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}