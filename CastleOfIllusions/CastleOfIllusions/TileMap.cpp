
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "TileMap.h"


using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, bool save_decoration)
{
	TileMap* map = new TileMap(levelFile, minCoords, program, save_decoration);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, bool save_decoration)
{
	loadLevel(levelFile, save_decoration);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string& levelFile, bool save_decoration)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;

	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	mapPixelSize.x = mapSize.x * tileSize;
	mapPixelSize.y = mapSize.y * tileSize;

	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	if (save_decoration) {
		while (getline(fin, line)) {
			if (line.find("DECORATIONS") != std::string::npos) {
				for (int j = 0; j < mapSize.y; j++) {
					//std::cout << line << std::endl;
					getline(fin, line);
					std::stringstream ss(line);
					int decoration;

					for (int i = 0; i < mapSize.x; i++) {
						ss >> decoration;
						map[j * mapSize.x + i] = decoration; 
					}
				}
				break;
			}
		}
	}
	else {
		while (getline(fin, line)) {
			if (line.find("MAP") != std::string::npos) {
				for (int j = 0; j < mapSize.y; j++) {
					//std::cout << line << std::endl;
					getline(fin, line);
					std::stringstream ss(line);
					int tile;

					for (int i = 0; i < mapSize.x; i++) {
						ss >> tile;
						map[j * mapSize.x + i] = tile;
					}
				}
				break; 
			}
		}
	}

	//for (int i = 0; i < mapSize.x; ++i) {
	//	for (int j = 0; j < mapSize.y; ++j) {
	//		std::cout << map[i * mapSize.x + j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}


std::vector<Enemy*> TileMap::getEnemies(const std::string& levelFile, ShaderProgram& program, mapData* map) {
	std::ifstream file(levelFile);
	std::string line;
	std::vector<Enemy*> enemies;
	bool inEnemiesSection = false;
	
	int tilesize = map->map->getTileSize();

	if (file.is_open()) {
		while (getline(file, line)) {
			if (line.find("ENEMIES") != std::string::npos) {
				inEnemiesSection = true;
				continue;
			}
			if (inEnemiesSection) {
				if (line.empty() || line.find("OBJECTS") != std::string::npos) break;

				std::istringstream lineStream(line);
				int id, x, y;
				lineStream >> id >> x >> y;

				Enemy* enemy = nullptr;
				if (id == 0)
					enemy = new Tree;
				//else if (line[0] == 8)
				//	enemy = new Plant; 

				if (enemy)
				{
					enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), program);
					enemy->setPosition(glm::vec2(tilesize * x, tilesize * y - 16));
					enemy->setPlayer(map->player);
					enemy->setTileMap(map);
					enemies.push_back(enemy);
				}
			}
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file: " << levelFile << std::endl;
	}
	return enemies;
}



std::vector<Object*> TileMap::getObjects(const std::string& levelFile, ShaderProgram& program, mapData* map) {
	std::ifstream file(levelFile);
	std::string line;
	std::vector<Object*> objects;
	bool inObjectsSection = false;

	int tilesize = map->map->getTileSize();

	if (file.is_open()) {
		while (getline(file, line)) {
			if (line.find("OBJECTS") != std::string::npos) {
				inObjectsSection = true;
				continue;
			}
			if (inObjectsSection) {
				if (line.empty()) break;

				std::istringstream lineStream(line);
				int id, x, y;
				lineStream >> id >> x >> y; // Extract ID, x, and y from the line

				Object* object = nullptr;
				if (id == 1)
					object = new Gem();
				else if (id == 0)
					object = new Stone();
				else if (id == 5)
					object = new Chest();

				if (object) { // Only proceed if object was successfully created
					object->init(glm::ivec2(SCREEN_X, SCREEN_Y), program);
					object->setPosition(glm::vec2(tilesize * x, tilesize * y));
					object->setTileMap(map);
					objects.push_back(object);
				}
			}
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file: " << levelFile << std::endl;
	}
	return objects;
}




// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.


glm::ivec2 TileMap::addOffset(glm::ivec2 pos, const glm::ivec2& boxOffset) const
{
	pos.x += boxOffset.x;
	pos.y += boxOffset.y;
	return pos;
}


bool TileMap::collisionMoveLeft(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset) const
{
	int x, y0, y1;

	glm::ivec2 intPos = addOffset(glm::ivec2(pos), offset);

	x = intPos.x / tileSize;
	y0 = intPos.y / tileSize;
	y1 = (intPos.y + size.y - 1) / tileSize;

	for (int y = y0; y <= y1; y++)
	{
		int value = map[y * mapSize.x + x];
		if (value != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset) const
{
	int x, y0, y1;

	glm::ivec2 intPos = addOffset(glm::ivec2(pos), offset);

	x = (intPos.x + size.x - 1) / tileSize;
	y0 = intPos.y / tileSize;
	y1 = (intPos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		int value = map[y * mapSize.x + x];
		if (value != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset, float* posY, const bool correctPos) const
{
	int x0, x1, y;

	glm::ivec2 intPos = addOffset(glm::ivec2(pos), offset);

	x0 = intPos.x / tileSize;
	x1 = (intPos.x + size.x - 1) / tileSize;
	y = (intPos.y + size.y - 1) / tileSize;

	for (int x = x0; x <= x1; x++)
	{
		int value = map[y * mapSize.x + x];

		if (value != 0)
		{
			if (*posY - tileSize * y + size.y <= 8)
			{
				if (correctPos)
					*posY = tileSize * y - size.y - offset.y;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveUp(const glm::vec2& pos, const glm::ivec2& size, const glm::ivec2& offset, float* posY, const bool correctPos) const
{
	int x0, x1, y;

	glm::ivec2 intPos = addOffset(glm::ivec2(pos), offset);

	x0 = intPos.x / tileSize;
	x1 = (intPos.x + size.x - 1) / tileSize;
	y = intPos.y / tileSize; // Check the tile above

	for (int x = x0; x <= x1; x++)
	{
		int value = map[y * mapSize.x + x];

		if (value != 0)
		{
			if (*posY + tileSize * y >= 0) // Adjust for upward collision
			{
				if (correctPos)
					*posY = tileSize * y + tileSize - offset.y; // Adjust position to be below the tile
				return true;
			}
		}
	}

	return false;
}
