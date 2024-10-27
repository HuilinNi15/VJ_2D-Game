#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"



void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/mickey.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	float x = 0.0625; 
	float y = 0.125;

	animations.resize(14);

	addAnimation(STAND_LEFT, glm::ivec2(18, 30), glm::vec2(7, 18));
	addAnimation(STAND_RIGHT, glm::ivec2(18, 30), glm::vec2(7, 18));
	addAnimation(MOVE_LEFT, glm::ivec2(20, 30), glm::vec2(6, 18));
	addAnimation(MOVE_RIGHT, glm::ivec2(20, 30), glm::vec2(6, 18));
	addAnimation(JUMP_LEFT, glm::ivec2(20, 31), glm::vec2(6, 17));
	addAnimation(JUMP_RIGHT, glm::ivec2(20, 31), glm::vec2(6, 17));
	addAnimation(BUTT_ATTACK_LEFT, glm::ivec2(20, 25), glm::vec2(6, 22));
	addAnimation(BUTT_ATTACK_RIGHT, glm::ivec2(20, 25), glm::vec2(6, 22));
	addAnimation(BUTT_FALL_LEFT, glm::ivec2(20, 23), glm::vec2(6, 25));
	addAnimation(BUTT_FALL_RIGHT, glm::ivec2(20, 23), glm::vec2(6, 25));
	addAnimation(STOP_RIGHT, glm::ivec2(20, 28), glm::vec2(6, 20));
	addAnimation(STOP_LEFT, glm::ivec2(20, 28), glm::vec2(6, 20));
	addAnimation(CROUCH_DOWN_LEFT, glm::ivec2(18, 20), glm::vec2(7, 28));
	addAnimation(CROUCH_DOWN_RIGHT, glm::ivec2(18, 20), glm::vec2(7, 28));

	sprite = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());

	/*sprite = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);*/
	
		sprite->setAnimationSpeed(STAND_LEFT, 2);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(x * 0.f, y * 1.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(x * 1.f, y * 1.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 2);	
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

		sprite->setAnimationSpeed(JUMP_LEFT, 3);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(x * 2.f, y * 3.f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(x * 3.f, y * 3.f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 3);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 2.f, y * 2.f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 3.f, y * 2.f));

		sprite->setAnimationSpeed(STOP_LEFT, 2);
		sprite->addKeyframe(STOP_LEFT, glm::vec2(x * 10.f, y * 1.f));

		sprite->setAnimationSpeed(STOP_RIGHT, 2);
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(x * 10.f, y * 0.f));

		sprite->setAnimationSpeed(BUTT_ATTACK_LEFT, 4);
		sprite->addKeyframe(BUTT_ATTACK_LEFT, glm::vec2(x * 5.0f, y * 3.0f));
		sprite->addKeyframe(BUTT_ATTACK_LEFT, glm::vec2(x * 6.0f, y * 3.0f));
		sprite->addKeyframe(BUTT_ATTACK_LEFT, glm::vec2(x * 7.0f, y * 3.0f));

		sprite->setAnimationSpeed(BUTT_ATTACK_RIGHT, 4);
		sprite->addKeyframe(BUTT_ATTACK_RIGHT, glm::vec2(x * 5.0f, y * 2.0f));
		sprite->addKeyframe(BUTT_ATTACK_RIGHT, glm::vec2(x * 6.0f, y * 2.0f));
		sprite->addKeyframe(BUTT_ATTACK_RIGHT, glm::vec2(x * 7.0f, y * 2.0f));

		sprite->setAnimationSpeed(BUTT_FALL_LEFT, 4);
		sprite->addKeyframe(BUTT_FALL_LEFT, glm::vec2(x * 7.0f, y * 3.0f));
		sprite->addKeyframe(BUTT_FALL_LEFT, glm::vec2(x * 8.0f, y * 3.0f));

		sprite->setAnimationSpeed(BUTT_FALL_RIGHT, 4);
		sprite->addKeyframe(BUTT_FALL_RIGHT, glm::vec2(x * 7.0f, y * 2.0f));
		sprite->addKeyframe(BUTT_FALL_RIGHT, glm::vec2(x * 8.0f, y * 2.0f));

		sprite->setAnimationSpeed(CROUCH_DOWN_LEFT, 4);
		sprite->addKeyframe(CROUCH_DOWN_LEFT, glm::vec2(x * 0.f, y * 3.f));
		sprite->addKeyframe(CROUCH_DOWN_LEFT, glm::vec2(x * 1.f, y * 3.f));

		sprite->setAnimationSpeed(CROUCH_DOWN_RIGHT, 4);
		sprite->addKeyframe(CROUCH_DOWN_RIGHT, glm::vec2(x * 0.f, y * 2.f));
		sprite->addKeyframe(CROUCH_DOWN_RIGHT, glm::vec2(x * 1.f, y * 2.f));

	/*glm::vec2 initialPosition = glm::vec2(float(tileMapDispl.x + posPlayer.x + hitBoxOffset.x), 
											float(tileMapDispl.y + posPlayer.y - hitBox.y + hitBoxOffset.y));
	sprite->setPosition(initialPosition);*/

	//sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}


void Player::addAnimation(int animId, const glm::ivec2& hitBox, const glm::vec2& hitBoxOffset)
{
	animations[animId] = { hitBox, hitBoxOffset };
}


void Player::updateHitBox(int animId)
{
	hitBox = animations[animId].hitBox;
	hitBoxOffset = animations[animId].hitBoxOffset;
}


void Player::handleInputs(int deltaTime)
{
	dt = deltaTime / 1000.0f;
	glm::vec2 velStart = velPlayer;

	if (Game::instance().getKey(GLFW_KEY_A))
		handleMove(-1.0f);
	else if (Game::instance().getKey(GLFW_KEY_D))
		handleMove(1.0f);
	else
	{
		moving = false; 
		stopping = true;
	}
	handleJump();
	handleCrouch(); 

	if (stopping)
	{
		velPlayer.x -= std::copysign(1.0f, velPlayer.x) * STOP_ACCELERATION* dt;
		if (std::abs(velPlayer.x) < MIN_VELOCITY)
		{
			velPlayer.x = 0;
			stopping = false; 
		}
	}

	//updateHitBox();
	//changeAnimations(deltaTime);

	avgVelocity.x = (velStart.x + velPlayer.x) / 2.0f;
	posPlayer.x += avgVelocity.x * dt;

	bool collisionDetected = false;
	if (velPlayer.x > 0.0f)
		collisionDetected = map->collisionMoveRight(posPlayer, hitBox, hitBoxOffset);
	else if (velPlayer.x < 0.0f)
		collisionDetected = map->collisionMoveLeft(posPlayer, hitBox, hitBoxOffset);
	if (collisionDetected)
	{
		posPlayer.x -= avgVelocity.x * dt;
		velPlayer.x = 0.0f;
	}

	velPlayer.y += GRAVITY * dt;
	avgVelocity.y = (velStart.y + velPlayer.y) / 2.0f;
	if (avgVelocity.y < MIN_FALL_VELOCITY && !jumping)
		avgVelocity.y = MIN_FALL_VELOCITY;
	posPlayer.y += avgVelocity.y * dt;
	if (map->collisionMoveDown(posPlayer, hitBox, hitBoxOffset, &posPlayer.y))
	{
		velPlayer.y = 0.0f;
		jumping = false;
		attacking = false;
	}
	else
		jumping = true; 

	changeAnimations(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}


void Player::handleMove(float direction)
{
	moving = true;
	stopping = false;
	facingRight = (direction == 1.0f);

	if (!crouching)
	{
		if (jumping)
			velPlayer.x += direction * JUMP_ACCELERATION * dt;
		else
			velPlayer.x += direction * ACCELERATION * dt;

		if (direction * velPlayer.x < 0) // When player changes directions
		{
			velPlayer.x += direction * STOP_ACCELERATION * dt;
			if (std::abs(velPlayer.x) < MIN_VELOCITY) velPlayer.x = 0; 
		}
		// Vel must always be between (-100, -20) or (20, 100)
		velPlayer.x = glm::clamp(velPlayer.x, -MAX_VELOCITY, MAX_VELOCITY);
		if (std::abs(velPlayer.x) < MIN_VELOCITY) velPlayer.x = direction * MIN_VELOCITY; 
	}
}


void Player::handleJump()
{
	if (Game::instance().getKey(GLFW_KEY_W) && !jumping)
	{
		jumping = true;
		crouching = false; 

		velPlayer.y = -JUMP_VELOCITY;
	}
}


void Player::handleCrouch()
{
	if (Game::instance().getKey(GLFW_KEY_S))
	{
		if (!jumping)
		{
			crouching = true;
			stopping = true;
			moving = false; 
		}
		else
			attacking = true; 

		hitBox = glm::ivec2(18, 19);
		hitBoxOffset = glm::ivec2(7, 28);
	}
	else
	{
		hitBox = glm::ivec2(18, 29);
		hitBoxOffset = glm::ivec2(7, 18);
		crouching = false;
		if (!moving) stopping = true;
	}
}


void Player::changeAnimation(PlayerAnims animation)
{
	if (sprite->animation() != animation)
		sprite->changeAnimation(animation);
}


void Player::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);

	if (!moving && !stopping && !jumping && !crouching)
	{
		if (facingRight) {
			changeAnimation(STAND_RIGHT);
			updateHitBox(STAND_RIGHT);
		}
		else {
			changeAnimation(STAND_LEFT);
			updateHitBox(STAND_LEFT);
		}
	}

	else if (moving && !jumping)
	{
		if (facingRight) {
			changeAnimation(MOVE_RIGHT);
			updateHitBox(MOVE_RIGHT);
		}
			
		else {
			changeAnimation(MOVE_LEFT);
			updateHitBox(MOVE_LEFT);
		}	
	}

	else if (stopping && !jumping && !crouching)
	{
		if (facingRight) {
			changeAnimation(STOP_RIGHT);
			updateHitBox(STOP_RIGHT);
		}
		else {
			changeAnimation(STOP_LEFT);
			updateHitBox(STOP_LEFT);
		}
	}

	else if (crouching)
	{
		if (facingRight) {
			changeAnimation(CROUCH_DOWN_RIGHT);
			updateHitBox(CROUCH_DOWN_RIGHT);
		}
		else {
			changeAnimation(CROUCH_DOWN_LEFT);
			updateHitBox(CROUCH_DOWN_LEFT);
		}
	}

	else if (jumping && !attacking)
	{
		if (facingRight) {
			changeAnimation(JUMP_RIGHT);
			updateHitBox(JUMP_RIGHT);
		}
		else {
			changeAnimation(JUMP_LEFT);
			updateHitBox(JUMP_LEFT);
		}
	}

	else if (jumping && attacking)
	{
		if (facingRight) {
			changeAnimation(BUTT_ATTACK_RIGHT);
			updateHitBox(BUTT_ATTACK_RIGHT);
		}
		else {
			changeAnimation(BUTT_ATTACK_LEFT);
			updateHitBox(BUTT_ATTACK_LEFT);
		}
	}
}


void Player::update(int deltaTime)
{
	handleInputs(deltaTime);
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