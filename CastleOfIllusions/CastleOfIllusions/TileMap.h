#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Object.h"
#include "Interface.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.



class TileMap
{

private:
	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, bool save_decoration = false);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, bool save_decoration = false);
	static std::vector<Enemy*> TileMap::getEnemies(const std::string& levelFile, ShaderProgram& program, mapData* map);
	static std::vector<Object*> TileMap::getObjects(const std::string& levelFile, ShaderProgram& program, mapData* map);

	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }
	glm::ivec2 getMapSize() const { return mapSize; }
	glm::ivec2 getMapPixelSize() const { return mapPixelSize; }

	glm::ivec2 TileMap::addOffset(glm::ivec2 pos, const glm::ivec2& boxOffset) const;
	bool collisionMoveLeft(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset) const;
	bool collisionMoveRight(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset) const;
	bool collisionMoveDown(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset, float* posY, const bool correctPos = true) const;
	bool collisionMoveUp(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset, float* posY, const bool correctPos = true) const;

private:
	bool loadLevel(const string& levelFile, bool save_decoration);
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize, mapPixelSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;

	//std::vector<int> checkList = {8, 9, 10, 11, 12, 24, 25, 27, 40, 41, 42}; 
							/*{0, 1, 2, 3, 4, 5, 6, 7, 17, 18, 19, 20, 21, 22, 23,
							28, 33, 34, 35, 37, 38, 39, 49, 50, 52, 54, 65, 66,
							81, 82, 83, 84, 97, 98, 99, 100, 101, 102, 103 };*/

	//std::vector<int> checkList = { 9, 10, 17, 18, 29, 30 };
};


#endif // _TILE_MAP_INCLUDE


