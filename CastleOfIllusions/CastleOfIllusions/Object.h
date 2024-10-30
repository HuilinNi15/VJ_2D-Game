#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#pragma once
#include "Sprite.h"
#include "MovableEntity.h"
#include "Player.h"


const glm::vec2 THROW_VEL = glm::vec2(150.0f, 100.0f); 
const glm::vec2 BOUNCE_VEL1 = glm::vec2(75.0f, 50); 
const glm::vec2 BOUNCE_VEL2 = glm::vec2(35.0f, 25.0f);


enum ObjectAnimations {
    STATIC, BREAK
};


class Object: public MovableEntity
{
public:
    virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0; 
    virtual void pickUp(Player* player);
    virtual void throwObject();
    virtual void breakObject();

    void render() override; 

protected:
    virtual void changeAnimations(int deltaTime) = 0;

    Player* pickedUpBy;
    bool isBroken = false; // Track if the object is broken
};


class Stone : public Object {
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

protected: 
    void changeAnimations(int deltaTime) override;
};


class Chest : public Object {
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; 
    void breakObject() override;

protected:
    void changeAnimations(int deltaTime) override;
    void releaseObject(); 
};


class Barrel : public Object {
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; 
    void breakObject() override;

protected:
    void changeAnimations(int deltaTime) override;
    int bounce = 0; 
};


#endif
