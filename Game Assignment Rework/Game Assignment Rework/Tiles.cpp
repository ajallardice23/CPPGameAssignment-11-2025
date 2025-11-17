#include "Tiles.h"
#include <iostream>   

//32px tilesize
const int tileSize = 32;



void tile::loadTile(std::string tileFileLoc) {
    sprite.load(tileFileLoc);
}


//Note to self - diff from class code as includes X for x axis too (River was just drawing Y)
void tile::drawTile(GamesEngineeringBase::Window& canvas, int x, int y) {
    for (unsigned int i = 0; i < sprite.height; i++)
        if (y + i > 0 && (y + i) < (canvas.getHeight()))
            for (unsigned int j = 0; j < sprite.width; j++)
                canvas.draw(x + j, y + i, sprite.atUnchecked(j, i));
}

//Loop through load tiles
tileSet::tileSet(std::string pre) {
    //Load tiles upto
    for (unsigned int i = 0; i < tileNum; i++) {
        std::string filename;
        filename = "Resources/Tiles/" + std::to_string(i) + ".png";
        t[i].loadTile(filename);
    }
}


//Note to self - refer to river raid from lecture
void Environment::drawEnvironment(GamesEngineeringBase::Window& canvas, unsigned int camX, unsigned int camY) {
    //Tile size = 32x32
    const unsigned int tileScale = 32;

    //How many fit on screen
    const unsigned int amountTileX = canvas.getWidth() / tileScale;
    const unsigned int amountTileY = canvas.getHeight() / tileScale;

    //create offsetr
    unsigned int offsetY = camY / tileScale;
    unsigned int offsetX = camX / tileScale;

    unsigned int camBX = camX % tileScale;
    unsigned int camBY = camY % tileScale;


    for (unsigned int y = 0; y < amountTileY; y++) {
        for (unsigned int x = 0; x < amountTileX; x++) {
            //add offset per loop for next tile locations
            int enviroX = x + offsetX;
            int enviroY = y + offsetY;

            //Tile from array with offset calculation
            tSet[tileArray[(enviroY * amountTileY + enviroX + amountTileX) % size]].drawTile(canvas, (x * tileScale) - camBX, (y * tileScale) - camBY);
        }
    } 
}



//{FIXED MAP (NO TILES)}

void Environment::loadFixedEnvironment(const std::string mapFileLoc) {
    map.load(mapFileLoc);
}

void Environment::drawFixedEnvironment(GamesEngineeringBase::Window& canvas, int x, int y) {
    for (unsigned int i = 0; i < map.height; i++) {
        int pY = y + i;
        if (pY < 0 || pY >= (int)canvas.getHeight()) {
            continue;
        } 

        for (unsigned int j = 0; j < map.width; j++) {
            int pX = x + j;
                if (pX < 0 || pX >= (int)canvas.getWidth()) {
                    continue;
            }
            canvas.draw(pX, y + i, map.atUnchecked(j, i));

        }
        
    }
}





//{COLOUR FOR IMPASSIBLE TERRAIN}
Colour Environment::getColour(int posX, int posY) {
    unsigned char* pixel = map.atUnchecked(posX, posY);
    Colour colour;
    colour.r = pixel[0];
    colour.g = pixel[1];
    colour.b = pixel[2];

    return colour;
}



/*
void DataLevelLoader::loadDataMap(const std::string& dataFileLoc) {
    std::ifstream fileTiles("Resources/Tiles/tiles.txt");

    //tileshigh and tiles wide is 42 in file so 42x42 = map size/tile amount?
    for (int i = 0; i < 1764; i++) {
       
        fileTiles >> tilesWide >> tilesHigh >> tilesWidth >> tilesHeight;

    }
}*/