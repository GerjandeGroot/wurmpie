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
} //Map

// default destructor
Map::~Map()
{
} //~Map

void Map::createRandomMap() {
	uint8_t seed = EEPROM.read(3);
	//seed++;
	//EEPROM.write(3,seed);
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
			if(i++ < verticalSize) setBlock(x,y,1);
			else setBlock(x,y,2);
		}
	}
}

void Map::drawMap() {
	Main::tft.fillScreen(ILI9341_CYAN);
	for(uint8_t y = verticalSize-1; y > 0; y--){
		for(uint8_t x = 0; x < horizontalSize; x++) {
			drawBlock(x,y,getBlock(x,y));
		}
	}
}

void Map::clearMap() {
	for(int x = 0; x < horizontalSize; x++){
		for(int y = 0; y < verticalSize; y ++) {
			setBlock(x,y,0);
		}
	}
}

void Map::setBlock(uint8_t x,uint8_t y,uint8_t type) {
	if(x >= horizontalSize || x < 0 || y >= verticalSize || y < 0) return;
	uint8_t gridX =  x / 2;
	uint8_t bitX = x % 2 * 4;
	uint8_t gridY =  y / 2;
	uint8_t bitY = y % 2 * 2;
	grid[gridX][gridY] &= ~(0b11 << (bitX+bitY));
	grid[gridX][gridY] |= type << (bitX+bitY);
}

uint8_t Map::getBlock(uint8_t x,uint8_t y) {
	if(x >= horizontalSize || x < 0 || y >= verticalSize || y < 0) return 255;
	uint8_t gridX =  x / 2;
	uint8_t bitX = x % 2 * 4;
	uint8_t gridY =  y / 2;
	uint8_t bitY = y % 2 * 2;
	return (grid[gridX][gridY] & (0b11 << (bitX+bitY))) >> (bitX+bitY);
}

void Map::drawBlock(uint8_t x,uint8_t y, uint8_t type) {
	if(type == 1) {
		Main::tft.fillRect(x*blocksize,y*blocksize,blocksize,blocksize,ILI9341_GREEN);
	} else if (type == 2) {
		Main::tft.fillRect(x*blocksize,y*blocksize,blocksize,blocksize,0x6B6D);
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
			
			default:
				color = ILI9341_RED;
				break;
		}
		Main::tft.fillRect(x*blocksize,y*blocksize,blocksize,blocksize,color);
	}else {
		Main::tft.fillRect(x*blocksize,y*blocksize,blocksize,blocksize,ILI9341_CYAN);
	}
}

void Map::setDrawBlock(uint8_t x, uint8_t y, uint8_t type) {
	setBlock(x,y,type);
	drawBlock(x,y,getBlock(x,y));
}

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

void Map::setRadius(uint8_t x, uint8_t y, uint8_t radius, uint8_t type) {
	for(int dx = -radius; dx < radius; dx++) {
		for(int dy = -radius; dy < radius; dy++) {
			if(sqrt(dx*dx + dy*dy) < radius)
			setDrawBlock(dx+x,dy+y,type);
		}
	}
}

void Map::explosion(uint8_t x, uint8_t y, uint8_t radius) {
	for(int i = 0; i < 10; i++) {
		for(int r = 0; r < radius; r++) {
			for(int dy = -radius; dy < radius; dy++) {
				if(sqrt(r*r + dy*dy) < radius) {
					drawBlock(x+r,dy+y,10);
					drawBlock(x-r,dy+y,10);
				}
				
			}
		}
	}
	setRadius(x,y,radius,0);
}

bool Map::isEmpty(uint8_t x, uint8_t y, uint8_t size) {
	for(int dx = 0; dx < size; dx++) {
		for(int dy = 0; dy < size; dy++) {
			if(getBlock(x+dx,y+dy)) return false;
		}
	}
	return true;
}