#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"
#include <typeinfo>


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/mickey.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	float x = 0.0625; 
	float y = 0.125;

	animations.resize(30);

	size = glm::ivec2(32, 48);

	addAnimation(STAND_LEFT, size, glm::ivec2(18, 30), glm::ivec2(7, 18));
	addAnimation(STAND_RIGHT, size, glm::ivec2(18, 30), glm::ivec2(7, 18));
	addAnimation(MOVE_LEFT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));
	addAnimation(MOVE_RIGHT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));
	addAnimation(JUMP_LEFT, size, glm::ivec2(20, 31), glm::ivec2(6, 17));

	addAnimation(JUMP_RIGHT, size, glm::ivec2(20, 31), glm::ivec2(6, 17));
	addAnimation(BUTT_ATTACK_LEFT, size, glm::ivec2(20, 26), glm::ivec2(6, 22));
	addAnimation(BUTT_ATTACK_RIGHT, size, glm::ivec2(20, 26), glm::ivec2(6, 22));
	addAnimation(BUTT_FALL_LEFT, size, glm::ivec2(20, 23), glm::ivec2(6, 25));
	addAnimation(BUTT_FALL_RIGHT, size, glm::ivec2(20, 23), glm::ivec2(6, 25));

	addAnimation(STOP_RIGHT, size, glm::ivec2(20, 28), glm::ivec2(6, 20));
	addAnimation(STOP_LEFT, size, glm::ivec2(20, 28), glm::ivec2(6, 20));
	addAnimation(CROUCH_DOWN_LEFT, size, glm::ivec2(18, 20), glm::ivec2(7, 28));
	addAnimation(CROUCH_DOWN_RIGHT, size, glm::ivec2(18, 20), glm::ivec2(7, 28));
	addAnimation(PREPARE_PICKUP_LEFT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));

	addAnimation(PREPARE_PICKUP_RIGHT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));
	addAnimation(ALMOST_FALLING_LEFT, size, glm::ivec2(9, 30), glm::ivec2(16, 18));
	addAnimation(ALMOST_FALLING_RIGHT, size, glm::ivec2(9, 30), glm::ivec2(7, 18));
	addAnimation(WAVING_HAND, size, glm::ivec2(20, 30), glm::ivec2(6, 18));
	addAnimation(CARRY_STAND_LEFT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));

	addAnimation(CARRY_STAND_RIGHT, size, glm::ivec2(20, 30), glm::ivec2(10, 18));
	addAnimation(CARRY_MOVE_LEFT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));
	addAnimation(CARRY_MOVE_RIGHT, size, glm::ivec2(20, 30), glm::ivec2(10, 18));
	addAnimation(CARRY_JUMP_LEFT, size, glm::ivec2(20, 30), glm::ivec2(6, 18));
	addAnimation(CARRY_JUMP_RIGHT, size, glm::ivec2(20, 30), glm::ivec2(10, 18));

	sprite = Sprite::createSprite(size, glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(animations.size());
	
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

		sprite->setAnimationSpeed(PREPARE_PICKUP_LEFT, 4);
		sprite->addKeyframe(PREPARE_PICKUP_LEFT, glm::vec2(x * 0.f, y * 5.f));
		sprite->addKeyframe(PREPARE_PICKUP_LEFT, glm::vec2(x * 1.f, y * 5.f));

		sprite->setAnimationSpeed(PREPARE_PICKUP_RIGHT, 4);
		sprite->addKeyframe(PREPARE_PICKUP_RIGHT, glm::vec2(x * 0.f, y * 4.f));
		sprite->addKeyframe(PREPARE_PICKUP_RIGHT, glm::vec2(x * 1.f, y * 4.f));

		sprite->setAnimationSpeed(ALMOST_FALLING_LEFT, 4);
		sprite->addKeyframe(ALMOST_FALLING_LEFT, glm::vec2(x * 9.f, y * 3.f));
		sprite->addKeyframe(ALMOST_FALLING_LEFT, glm::vec2(x * 10.f, y * 3.f));

		sprite->setAnimationSpeed(ALMOST_FALLING_RIGHT, 4);
		sprite->addKeyframe(ALMOST_FALLING_RIGHT, glm::vec2(x * 9.f, y * 2.f));
		sprite->addKeyframe(ALMOST_FALLING_RIGHT, glm::vec2(x * 10.f, y * 2.f));

		sprite->setAnimationSpeed(WAVING_HAND, 4);
		sprite->addKeyframe(WAVING_HAND, glm::vec2(x * 12, y * 2));
		sprite->addKeyframe(WAVING_HAND, glm::vec2(x * 13, y * 2));
		sprite->addKeyframe(WAVING_HAND, glm::vec2(x * 14, y * 2));
		sprite->addKeyframe(WAVING_HAND, glm::vec2(x * 15, y * 2));

		sprite->setAnimationSpeed(CARRY_STAND_LEFT, 4);
		sprite->addKeyframe(CARRY_STAND_LEFT, glm::vec2(x * 4, y * 5));
		sprite->addKeyframe(CARRY_STAND_LEFT, glm::vec2(x * 5, y * 5));

		sprite->setAnimationSpeed(CARRY_STAND_RIGHT, 4);
		sprite->addKeyframe(CARRY_STAND_RIGHT, glm::vec2(x * 4, y * 4));
		sprite->addKeyframe(CARRY_STAND_RIGHT, glm::vec2(x * 5, y * 4));

		sprite->setAnimationSpeed(CARRY_MOVE_LEFT, 15);
		sprite->addKeyframe(CARRY_MOVE_LEFT, glm::vec2(x * 6, y * 7));
		sprite->addKeyframe(CARRY_MOVE_LEFT, glm::vec2(x * 1, y * 7));
		sprite->addKeyframe(CARRY_MOVE_LEFT, glm::vec2(x * 2, y * 7));
		sprite->addKeyframe(CARRY_MOVE_LEFT, glm::vec2(x * 7, y * 7));
		sprite->addKeyframe(CARRY_MOVE_LEFT, glm::vec2(x * 4, y * 7));
		sprite->addKeyframe(CARRY_MOVE_LEFT, glm::vec2(x * 5, y * 7));

		sprite->setAnimationSpeed(CARRY_MOVE_RIGHT, 15);
		sprite->addKeyframe(CARRY_MOVE_RIGHT, glm::vec2(x * 6, y * 6));
		sprite->addKeyframe(CARRY_MOVE_RIGHT, glm::vec2(x * 1, y * 6));
		sprite->addKeyframe(CARRY_MOVE_RIGHT, glm::vec2(x * 2, y * 6));
		sprite->addKeyframe(CARRY_MOVE_RIGHT, glm::vec2(x * 7, y * 6));
		sprite->addKeyframe(CARRY_MOVE_RIGHT, glm::vec2(x * 4, y * 6));
		sprite->addKeyframe(CARRY_MOVE_RIGHT, glm::vec2(x * 5, y * 6));

		sprite->setAnimationSpeed(CARRY_JUMP_LEFT, 4);
		sprite->addKeyframe(CARRY_JUMP_LEFT, glm::vec2(x * 8, y * 7));
		sprite->addKeyframe(CARRY_JUMP_LEFT, glm::vec2(x * 9, y * 7));

		sprite->setAnimationSpeed(CARRY_JUMP_RIGHT, 4);
		sprite->addKeyframe(CARRY_JUMP_RIGHT, glm::vec2(x * 8, y * 6));
		sprite->addKeyframe(CARRY_JUMP_RIGHT, glm::vec2(x * 9, y * 6));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

	isStatic = false; 
	updateHitBox(STAND_RIGHT);
}


void Player::calculateVelocity()
{
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
		vel.x -= std::copysign(1.0f, vel.x) * STOP_ACCELERATION* dt;
		if (std::abs(vel.x) < MIN_VELOCITY)
		{
			vel.x = 0;
			stopping = false; 
		}
	}
}


void Player::handleMove(float direction)
{
	moving = true;
	stopping = false;
	facingRight = (direction == 1.0f);

	if (!crouching)
	{
		if (falling)
			vel.x += direction * JUMP_ACCELERATION * dt;
		else
			vel.x += direction * ACCELERATION * dt;

		if (direction * vel.x < 0) // When player changes directions
		{
			vel.x += direction * STOP_ACCELERATION * dt;
			if (std::abs(vel.x) < MIN_VELOCITY) vel.x = 0; 
		}
		// Vel must always be between (-100, -20) or (20, 100)
		vel.x = glm::clamp(vel.x, -MAX_VELOCITY, MAX_VELOCITY);
		if (std::abs(vel.x) < MIN_VELOCITY) vel.x = direction * MIN_VELOCITY; 
	}
}


void Player::handleJump()
{
	if (Game::instance().getKey(GLFW_KEY_W) && !falling)
	{
		jump(JUMP_VELOCITY); 
		crouching = false; 
	}
}


void Player::handleCrouch()
{
	if (Game::instance().getKey(GLFW_KEY_S) && carrying == nullptr)
	{
		if (!falling)
		{
			crouching = true;
			stopping = true;
			moving = false;
		}
		else
			attacking = true; 
	}
	else
	{
		crouching = false;
		if (!moving) stopping = true;
	}
}


void Player::pickUpCakeorCoin(Chest* chest)
{
	if (!chest->isPickedUp())
	{
		if (chest->state == COIN)
			addPoints(1000);
		else if (chest->state == CAKE)
			addLives(1);

		chest->destroy();
		chest->setPickedUp();
	}
}


void Player::otherChanges()
{
	if (topCollision)
		attacking = false;

	bool eKeyCurrentlyPressed = Game::instance().getKey(GLFW_KEY_E);

	if (eKeyCurrentlyPressed && !eKeyPreviouslyPressed) {
		if (moving && !falling && collidedObjectX && vel == glm::vec2(0.f, 0.f)) {

			float object_Y = collidedObjectX->getPosition().y + collidedObjectX->getHitBoxOffset().y + collidedObjectX->getHitBox().y;
			float player_Y = pos.y + hitBoxOffset.y + hitBox.y;

			if (object_Y == player_Y)
			{
				pickUp(collidedObjectX);
				collidedObjectX->pickUp(this);
			}
		}
		else if (carrying) {
			glm::vec2 velocity = THROW_VEL; 
			if (typeid(*carrying) == typeid(Barrel)) { velocity.x = 50.0f; }
			if (!facingRight) { velocity.x *= -1; }
			carrying->throwObject(velocity);
			throwObject();
		}
	}
	
	if (attacking && collidedObjectY)
	{
		if (typeid(*collidedObjectY) == typeid(Stone))
		{
			collidedObjectY->breakObject();
			jump(BOUNCE_VELOCITY);
		}
		else if (typeid(*collidedObjectY) == typeid(Chest))
		{
			Chest* chest = dynamic_cast<Chest*>(collidedObjectY);
			if (chest && chest->state != CAKE && chest->state != COIN)
			{
				chest->breakObject();
				jump(BOUNCE_VELOCITY);
			}
		}
	}
	else if (attacking && collidedEnemyY)
	{
		collidedEnemyY->kill(); 
		jump(BOUNCE_VELOCITY);
	}
	else
	{
		Chest* chestX = dynamic_cast<Chest*>(collidedObjectX);
		Chest* chestY = dynamic_cast<Chest*>(collidedObjectY);
		if (chestX) {
			if (chestX->state == COIN || chestX->state == CAKE)
				pickUpCakeorCoin(chestX); 
		}
		else if (chestY) {
			if (chestY->state == COIN || chestY->state == CAKE)
				pickUpCakeorCoin(chestY);
		}
		else if (Gem* gemX = dynamic_cast<Gem*>(collidedObjectX)) {
			WIN = true;
			delete collidedObjectX;
		}
		else if (Gem* gemY = dynamic_cast<Gem*>(collidedObjectY)) {
			WIN = true;
			delete collidedObjectY;
		}
	}

	eKeyPreviouslyPressed = eKeyCurrentlyPressed;
}


void Player::changeAnimations(int deltaTime)
{
	sprite->update(deltaTime);
	
	if (isStatic)
		return; 

	if (!moving && !stopping && !falling && !crouching)
	{
		if (carrying)
		{
			if (facingRight) {
				changeAnimation(CARRY_STAND_RIGHT);
				updateHitBox(CARRY_STAND_RIGHT);
			}
			else {
				changeAnimation(CARRY_STAND_LEFT);
				updateHitBox(CARRY_STAND_LEFT);
			}
		}
		else
		{
			pos.y += MIN_FALL_VELOCITY * dt;
			updateHitBox(ALMOST_FALLING_LEFT);
			if (!map->map->collisionMoveDown(pos, hitBox, hitBoxOffset, &pos.y, false) && !checkCollisionEntities(map->objects, true, false))
			{
				changeAnimation(ALMOST_FALLING_LEFT);
				updateHitBox(STAND_LEFT);
			}
			else
			{
				updateHitBox(ALMOST_FALLING_RIGHT);
				if (!map->map->collisionMoveDown(pos, hitBox, hitBoxOffset, &pos.y, false) && !checkCollisionEntities(map->objects, true, false))
				{
					changeAnimation(ALMOST_FALLING_RIGHT);
					updateHitBox(STAND_RIGHT);
				}
				else
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
			}
			pos.y -= MIN_FALL_VELOCITY * dt;
		}
	}

	else if (moving && !falling && collidedObjectX && std::abs(vel.x) == 20.f && vel.y == 0.f)
	{
		if (facingRight) {
			changeAnimation(PREPARE_PICKUP_RIGHT);
			updateHitBox(PREPARE_PICKUP_RIGHT);
		}
		else {
			changeAnimation(PREPARE_PICKUP_LEFT);
			updateHitBox(PREPARE_PICKUP_LEFT);
		}
	}

	else if (moving && !falling)
	{
		if (carrying)
		{
			if (facingRight) {
				changeAnimation(CARRY_MOVE_RIGHT);
				updateHitBox(CARRY_MOVE_RIGHT);
			}
			else {
				changeAnimation(CARRY_MOVE_LEFT);
				updateHitBox(CARRY_MOVE_LEFT);
			}
		}
		else
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
	}

	else if (stopping && !falling && !crouching)
	{
		if (carrying)
		{
			if (facingRight) {
				changeAnimation(CARRY_MOVE_RIGHT);
				updateHitBox(CARRY_MOVE_RIGHT);
			}
			else {
				changeAnimation(CARRY_MOVE_LEFT);
				updateHitBox(CARRY_MOVE_LEFT);
			}
		}
		else
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

	else if (falling && !attacking)
	{
		if (carrying)
		{
			if (facingRight) {
				changeAnimation(CARRY_JUMP_RIGHT);
				updateHitBox(CARRY_JUMP_RIGHT);
			}
			else {
				changeAnimation(CARRY_JUMP_LEFT);
				updateHitBox(CARRY_JUMP_LEFT);
			}
		}
		else
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
	}

	else if (falling && attacking)
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