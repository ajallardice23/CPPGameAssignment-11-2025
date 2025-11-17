#pragma once
#include "GamesEngineeringBase.h"
#include <fstream>

//Rgb values, slightly similar to river raid but no alpha used
struct Colour{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};


//Tiles class
class tile {
	GamesEngineeringBase::Image sprite;
public:
	tile() {}
	void loadTile(std::string tileFileLoc);
	void drawTile(GamesEngineeringBase::Window& canvas, int x, int y);
	GamesEngineeringBase::Image& getSprite() { return sprite; };
};
//TileAmount (23 from tiles folder)
const unsigned int tileNum = 26;

//Tile Set storing tiles
//Note to self - refer to river raid from lecture (very similar but mine will be static tiles and x and y value rather than just y)
//Used terrain tiles from the moodle resources, but there was technically only 3 terrain types (but different patterns) so added a custom snow terrain
class tileSet {
	tile t[tileNum];
	unsigned int size = tileNum;
public:
	tileSet(std::string pre = "");
	tile& operator[](unsigned int index) { return t[index]; }

};

const int environmentSize = 1000;
class Environment {
	tileSet tSet;
	unsigned int* tileArray;
	unsigned int size;

	//{FIXED MAP}
	GamesEngineeringBase::Image map;

public:
	Environment() : tSet() {
		tileArray = new unsigned int[environmentSize];
		size = environmentSize;
		for (unsigned int i = 0; i < environmentSize; i++) {
			//Chance of water/snow tile 1/5 as too many in map
			int specialChance = rand() % 4;
			//if chance pick water otherwise put a normal tile (water/snow = tile 14-25 in folder)
			if (specialChance == 0) {
				tileArray[i] = (rand() + 14) % 25;
			}
			else {
				tileArray[i] = rand() % 13;
			}
		}
	}

	void drawEnvironment(GamesEngineeringBase::Window& canvas, unsigned int x, unsigned int y);

	void drawFixedEnvironment(GamesEngineeringBase::Window& canvas, int x, int y);
	void loadFixedEnvironment(const std::string mapFileLoc);

	Colour getColour(int posX, int posY);
};

/* DATA LEVEL LOADING (TEST)
class DataLevelLoader {
	int tilesWide;
	int tilesHigh;
	int tilesWidth;
	int tilesHeight;

	int* tileNumber;
	tileSet tSet;
public:
	void loadDataMap(const std::string& dataFileLoc);

};
*/