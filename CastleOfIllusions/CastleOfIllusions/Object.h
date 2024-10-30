#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#pragma once
#include "Sprite.h"
#include "MovableEntity.h"
#include "Player.h"


const glm::vec2 THROW_VEL = glm::vec2(125.0f, -125.0f); 
const glm::vec2 BOUNCE_VEL1 = glm::vec2(75.0f, -70); 
const glm::vec2 BOUNCE_VEL2 = glm::vec2(35.0f, -55.0f);


enum ObjectAnimations {
    STATIC, BREAK, CAKE, COIN
};


class Object: public MovableEntity
{
public:
    virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0; 
    virtual void pickUp(Player* player);
    virtual void throwObject(glm::vec2 velocity);
    virtual void breakObject();

    void render() override; 

protected:
    void breakOtherObject(Object* object);
    void deactivating(); 
    virtual void otherChanges() override; 
    virtual void changeAnimations(int deltaTime) = 0;

    Player* pickedUpBy;
    bool isBroken = false; // Track if the object is broken
    bool justBroken = false; 
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
    int state = STATIC; 
    void setPickedUp() { pickedUp = true; };
    bool isPickedUp() { return pickedUp; }; 

protected:
    bool pickedUp = false; 
    void changeAnimations(int deltaTime) override;
    void releaseObject(); 
};


class Barrel : public Object {
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; 
    void breakObject() override;

protected:
    //void otherChanges() override; 
    void changeAnimations(int deltaTime) override;
};


//class Consumable : public Object {
//public: 
//    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
//    void breakObject() override;
//
//protected: 
//    virtual void otherChanges() override;
//    void changeAnimations(int deltaTime) = 0;
//};


//class Coin : public Consumable {
//public:
//    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
//    void release();
//
//protected:
//    void throwCoin();
//    virtual void otherChanges() override;
//    void changeAnimations(int deltaTime) override;
//
//};
//
//
//class Cake : public Consumable {
//public:
//    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
//    void release();
//
//protected:
//    void throwCake(); 
//    virtual void otherChanges() override;
//    void changeAnimations(int deltaTime) override;
//};


class Gem : public Object {
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

protected:
    virtual void otherChanges() override;
    void changeAnimations(int deltaTime) override;
};


#endif
