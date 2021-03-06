/* 
* Map.cpp
*
* Created: 6-12-2018 15:48:04
* Author: gerja
*/


#include "Map.h"

// default constructor
Map::Map()
{
	Main::tft.begin();
	Main::tft.setRotation(3);
} //Map

// default destructor
Map::~Map()
{
} //~Map
//function to create a random map in the game
void Map::createRandomMap(uint16_t seed) {
	this->seed = seed;
	clearMap();
	randomSeed(seed);
	float hoogte = random(verticalSize/2,verticalSize);
	float deltaHoogte = 0;

	int count = 0;
	for(int x = 0; x < horizontalSize; x++) {
		if(count == 0) {
			deltaHoogte = 0.1 * random(-verticalDifference,verticalDifference);
			count = random(horizontalDifference/2,horizontalDifference);
		}

		hoogte += deltaHoogte;
		count--;
		
		if (hoogte < verticalSize/3) hoogte = verticalSize/3;
		if (hoogte > verticalSize) hoogte = verticalSize;
		
		int i = 0;
		int iHoogte = random(10,20);
		for(int y = hoogte; y < verticalSize; y++) {
			if(i++ < 4) setBlock(x,y,1);
			else setBlock(x,y,2);
		}
	}
}
//function to draw the map
void Map::drawMap() {
	for(int y = verticalSize-1; y >= 0; y--){
		for(int x = 0; x < horizontalSize; x++) {
			drawBlock(x*blocksize,y*blocksize,getBlock(x,y),blocksize);
		}
	}
}
//function the clear the map
void Map::clearMap() {
	for(int x = 0; x < horizontalSize; x++){
		for(int y = 0; y < verticalSize; y ++) {
			setBlock(x,y,0);
		}
	}
}
//function to set a block in the map
void Map::setBlock(uint8_t x,uint8_t y,uint8_t type) {
	if(x >= horizontalSize || x < 0 || y >= verticalSize || y < 0) return;
	uint8_t gridX =  x / 2;
	uint8_t bitX = x % 2 * 4;
	uint8_t gridY =  y / 2;
	uint8_t bitY = y % 2 * 2;
	grid[gridX][gridY] &= ~(0b11 << (bitX+bitY));
	grid[gridX][gridY] |= type << (bitX+bitY);
}
//function to get a block in the map
uint8_t Map::getBlock(uint8_t x,uint8_t y) {
	if(x >= horizontalSize || y >= verticalSize) return 0;
	uint8_t gridX =  x / 2;
	uint8_t bitX = x % 2 * 4;
	uint8_t gridY =  y / 2;
	uint8_t bitY = y % 2 * 2;
	return (grid[gridX][gridY] & (0b11 << (bitX+bitY))) >> (bitX+bitY);
}
//function to draw all bloks in the map
void Map::drawBlock(uint16_t x,uint16_t y, uint8_t type, uint8_t size) {
	y += verticalOffset;
	if(x > 320 || x < 0 || y > 240 || y < verticalOffset) return;
	if(type == 1) {
		Main::tft.fillRect(x,y,size,size,ILI9341_GREEN);
	} else if (type == 2) {
		Main::tft.fillRect(x,y,size,size,0x6B6D);
	} else if (type == 10) {
		uint8_t rgn = random(5);
		uint16_t color;
		switch(rgn) {
			case 0:
			color = 0xFFFF;
			break;
			case 1:
			color = 0xFFCC;
			break;
			case 2:
			color = 0xF000;
			break;
			case 3:
			color = 0xF520;
			break;
			case 4:
			color=0x5B4C;
			break;
		}
		Main::tft.fillRect(x,y,size,size,color);
	}else if (type == 11) {
		uint8_t rgn = random(5);
		uint16_t color;
		switch(rgn) {
			case 0:
			color = 0x041F;
			break;
			case 1:
			color = 0x87FF;
			break;
			case 2:
			color = 0xFFFF;
			break;
			case 3:
			color = 0x001F;
			break;
			case 4:
			color = 0x9CDF;
			break;
		}
		Main::tft.fillRect(x,y,size,size,color);
	}else {
		Main::tft.fillRect(x,y,size,size,ILI9341_CYAN);
	}
}
//function to set the drawn block 
void Map::setDrawBlock(uint8_t x, uint8_t y, uint8_t type) {
	setBlock(x,y,type);
	drawBlock(x*blocksize,y*blocksize,getBlock(x,y),blocksize);
}
//updating the map with specific blocks
bool Map::updateMap() {
	bool updated = false;
	for(int x = 0; x < horizontalSize; x++){
		bool falling = false;
		for(int y = verticalSize-1; y > 0; y--) {
			if(getBlock(x,y) == 0 && getBlock(x,y-1) == 1) {
				setDrawBlock(x,y,1);
				falling = true;
				updated = true;
			} else if(getBlock(x,y) == 1 && getBlock(x,y-1) == 0 && falling) {
				falling = false;
				setDrawBlock(x,y,0);
			}
		}
	}
	return updated;
}
//function to create a circle for explosion
void Map::setRadius(uint8_t x, uint8_t y, uint8_t radius, uint8_t type, bool draw) {
	for(int dx = -radius; dx < radius; dx++) {
		for(int dy = -radius; dy < radius; dy++) {
			if(sqrt(dx*dx + dy*dy) < radius)
				if(draw){
					setDrawBlock(dx+x,dy+y,type);
				}
				else{
					setBlock(dx+x,dy+y,type);
				}
		}
	}
}
//function to draw the radius
void Map::drawRadius(uint8_t x, uint8_t y, uint8_t radius, uint8_t type) {
	for(int dx = -radius; dx < radius; dx++) {
		for(int dy = -radius; dy < radius; dy++) {
			if(sqrt(dx*dx + dy*dy) < radius)
			drawBlock((dx+x)*blocksize,(dy+y)*blocksize,type, blocksize);
		}
	}
}
//function to create an explosion
void Map::explosion(uint8_t x, uint8_t y, uint8_t radius) {
	for(int i = 0; i < 10; i++) {
		for(int r = 0; r < radius; r++) {
			for(int dy = -radius; dy < radius; dy++) {
				if(sqrt(r*r + dy*dy) < radius) {
					drawBlock((x+r)*blocksize,(dy+y)*blocksize,10,blocksize);
					drawBlock((x-r)*blocksize,(dy+y)*blocksize,10,blocksize);
				}
				
			}
		}
	}
	setRadius(x,y,radius,0);
}
//checking if block disappeared
bool Map::isEmpty(uint8_t x, uint8_t y, uint8_t size) {
	for(int dx = 0; dx < size; dx++) {
		for(int dy = 0; dy < size; dy++) {
			if(getBlock(x+dx,y+dy)) return false;
		}
	}
	return true;
}
//function to draw a part of a block
void Map::drawPart(int8_t x, int8_t y, uint8_t size) {
	for(int dx = 0; dx < size; dx++) {
		for(int dy = 0; dy < size; dy++) {
			if(x+dx < horizontalSize && y+dy < verticalSize)
				drawBlock((x+dx)*blocksize,(y+dy)*blocksize,getBlock(x+dx,y+dy),blocksize);
		}
	}
}
//function to draw a small preview of a map in the map menu
void Map::drawMapSmall(uint8_t x, uint8_t y, uint8_t size) {
	for(int dy = verticalSize-1; dy >= 0; dy--){
		for(int dx = 0; dx < horizontalSize; dx++) {
			drawBlock(x+dx*size,y+dy*size,getBlock(dx,dy),size);
		}
	}
}