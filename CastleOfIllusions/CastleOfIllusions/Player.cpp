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
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);
	
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
		//sprite->addKeyframe(JUMP_LEFT, glm::vec2(x * 4.f, y * 3.f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 3);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 2.f, y * 2.f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 3.f, y * 2.f));
		//sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x * 4.f, y * 2.f));

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

		sprite->setAnimationSpeed(CROUCH_DOWN_LEFT, 4);
		sprite->addKeyframe(CROUCH_DOWN_LEFT, glm::vec2(x * 0.f, y * 3.f));
		sprite->addKeyframe(CROUCH_DOWN_LEFT, glm::vec2(x * 1.f, y * 3.f));

		sprite->setAnimationSpeed(CROUCH_DOWN_RIGHT, 4);
		sprite->addKeyframe(CROUCH_DOWN_RIGHT, glm::vec2(x * 0.f, y * 2.f));
		sprite->addKeyframe(CROUCH_DOWN_RIGHT, glm::vec2(x * 1.f, y * 2.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
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
		stoping = true;
	}
	handleJump();
	handleCrouch(); 

	if (stoping)
	{
		velPlayer.x -= std::copysign(1.0f, velPlayer.x) * STOP_ACCELERATION* dt;
		if (std::abs(velPlayer.x) < MIN_VELOCITY)
		{
			velPlayer.x = 0;
			stoping = false; 
		}
	}

	avgVelocity.x = (velStart.x + velPlayer.x) / 2.0f;
	posPlayer.x += avgVelocity.x * dt;

	bool collisionDetected = false;
	if (velPlayer.x > 0.0f)
		collisionDetected = map->collisionMoveRight(posPlayer, glm::vec2(32, 32));
	else if (velPlayer.x < 0.0f)
		collisionDetected = map->collisionMoveLeft(posPlayer, glm::vec2(32, 32));
	if (collisionDetected)
	{
		posPlayer.x -= avgVelocity.x * dt;
		velPlayer.x = 0.0f;
	}

	velPlayer.y += GRAVITY * dt;
	avgVelocity.y = (velStart.y + velPlayer.y) / 2.0f;
	if (avgVelocity.y < MIN_FALL_VELOCITY && !jumping)
		avgVelocity.y = MIN_FALL_VELOCITY;
	std::cout << avgVelocity.y << std::endl; 
	posPlayer.y += avgVelocity.y * dt;
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
	{
		velPlayer.y = 0.0f;
		jumping = false;
		attacking = false;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}


void Player::handleMove(float direction)
{
	moving = true;
	stoping = false;
	facingRight = (direction == 1.0f);

	if (!crouching)
	{
		if (jumping)
			velPlayer.x += direction * JUMP_ACCELERATION * dt;
		else
			velPlayer.x += direction * ACCELERATION * dt;

		if (direction * velPlayer.x < 0) 
		{
			velPlayer.x += direction * STOP_ACCELERATION * dt;
			if (std::abs(velPlayer.x) < MIN_VELOCITY) velPlayer.x = 0; 
		}
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
			stoping = true;
			moving = false; 
		}
		else
			attacking = true; 
	}
	else
	{
		crouching = false;
		if (!moving) stoping = true;
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

	if (!moving && !stoping && !jumping && !crouching)
	{
		if (facingRight)
			changeAnimation(STAND_RIGHT);
		else
			changeAnimation(STAND_LEFT);
	}

	else if (moving && !jumping)
	{
		if (facingRight)
			changeAnimation(MOVE_RIGHT);
		else
			changeAnimation(MOVE_LEFT);
	}

	else if (stoping && !jumping && !crouching)
	{
		if (facingRight)
			changeAnimation(STOP_RIGHT);
		else
			changeAnimation(STOP_LEFT);
	}

	else if (crouching)
	{
		if (facingRight)
			changeAnimation(CROUCH_DOWN_RIGHT);
		else
			changeAnimation(CROUCH_DOWN_LEFT);
	}

	else if (jumping && !attacking)
	{
		if (facingRight)
			changeAnimation(JUMP_RIGHT);
		else
			changeAnimation(JUMP_LEFT);
	}

	else if (jumping && attacking)
	{
		if (facingRight)
			changeAnimation(BUTT_ATTACK_RIGHT);
		else
			changeAnimation(BUTT_ATTACK_LEFT);
	}
}


void Player::update(int deltaTime)
{
	handleInputs(deltaTime);
	changeAnimations(deltaTime);
}


//void Player::update(int deltaTime)
//{
//	sprite->update(deltaTime);
//
//	bool isKeyAPressed = Game::instance().getKey(GLFW_KEY_A);
//	bool isKeyDPressed = Game::instance().getKey(GLFW_KEY_D);
//	bool isKeyWPressed = Game::instance().getKey(GLFW_KEY_W);
//	bool isKeySPressed = Game::instance().getKey(GLFW_KEY_S);
//
//	if (isKeyWPressed && !bJumping) {
//		if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
//			sprite->changeAnimation(JUMP_LEFT);
//		else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
//			sprite->changeAnimation(JUMP_RIGHT);
//	}
//	if (isKeyAPressed) {
//		if (sprite->animation() != MOVE_LEFT)
//			sprite->changeAnimation(MOVE_LEFT);
//		posPlayer.x -= 2;
//	
//		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
//			posPlayer.x += 2;
//	}
//	else if (isKeyDPressed) {
//		if(sprite->animation() != MOVE_RIGHT)
//			sprite->changeAnimation(MOVE_RIGHT);
//		posPlayer.x += 2;
//		
//		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
//			posPlayer.x -= 2;
//	}
//	else if (isKeySPressed) {
//		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
//			sprite->changeAnimation(CROUCH_DOWN_LEFT);
//		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
//			sprite->changeAnimation(CROUCH_DOWN_RIGHT);
//	}
//	else {
//		if (sprite->animation() == MOVE_LEFT)
//			sprite->changeAnimation(STAND_LEFT);
//		else if (sprite->animation() == MOVE_RIGHT)
//			sprite->changeAnimation(STAND_RIGHT);
//	}
//	
//	if(bJumping) {
//		jumpAngle += JUMP_ANGLE_STEP;
//		if (jumpAngle == 180) {
//			bJumping = false;
//			posPlayer.y = startY;
//		}
//		else {
//			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
//			if (jumpAngle > 90) {
//				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
//
//				if (sprite->animation() == JUMP_LEFT || sprite->animation() == MOVE_LEFT) {
//					sprite->changeAnimation(JUMP_LEFT);
//					/*posPlayer.x -= 1;*/
//					/*if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
//						posPlayer.x += 2;*/
//				}
//				else if (sprite->animation() == JUMP_RIGHT || sprite->animation() == MOVE_RIGHT) {
//					sprite->changeAnimation(JUMP_RIGHT);
//					/*posPlayer.x += 1;*/
//					/*if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32))) 
//						posPlayer.x -= 2;*/
//				}
//			}
//		}
//	}
//	else {
//		posPlayer.y += FALL_STEP;
//		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
//		{
//			if(isKeyWPressed){
//				bJumping = true;
//				jumpAngle = 0;
//				startY = posPlayer.y;
//			} else {
//				if (sprite->animation() == JUMP_LEFT)
//					sprite->changeAnimation(STAND_LEFT);
//				else if (sprite->animation() == JUMP_RIGHT)
//					sprite->changeAnimation(STAND_RIGHT);
//			}
//		}
//	}
//	
//	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
//}

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