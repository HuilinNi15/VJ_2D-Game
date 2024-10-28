#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "MovableEntity.h"
#include "Player.h"


#pragma once
class Object: public MovableEntity
{
public:
    virtual void pickUp(Player* player);
    virtual void throwObject();
    virtual void breakObject();

protected:
    bool isBroken = false; // Track if the object is broken
};


class Stone : public Object {
public:
    void throwObject() override {
        // Logic for throwing a stone
        isBroken = true; // Stone breaks when thrown
    }
};


class Chest : public Object {
public:
    void throwObject() override {
        isBroken = true; // Chess piece breaks when thrown
        releaseObject(); // Releases an object upon breaking
    }

private:
    void releaseObject() {
        // Logic to release an object
    }
};


class Barrel : public Object {
public:
    void throwObject() override {
        // Logic for throwing a box
        // Box does not break; simply remains in the world
    }
};


#endif
