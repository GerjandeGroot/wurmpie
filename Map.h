/* 
* Map.h
*
* Created: 6-12-2018 15:48:04
* Author: gerja
*/


#ifndef __MAP_H__
#define __MAP_H__

#include "Arduino.h"
#include "Custom_ILI9341.h"
#include "EEPROM.h"

#define blocksize 8
#define verticalSize 30 //60
#define horizontalSize 40 //80
#define verticalDifference 10
#define horizontalDifference 10

class Map
{
//variables
public:
	uint8_t grid[horizontalSize/2][verticalSize/2];
	uint8_t seed;
	uint16_t backgroundColor = ILI9341_CYAN;
	uint16_t groundColor = ILI9341_GREEN;
	uint16_t underGroundColor = ILI9341_LIGHTGREY;
protected:
private:

//functions
public:
	Map();
	~Map();
	void createRandomMap(uint16_t seed);
	void drawMap();
	void drawMapSmall(uint8_t x, uint8_t y, uint8_t size);
	void clearMap();
	void setBlock(uint8_t x,uint8_t y,uint8_t type);
	uint8_t getBlock(uint8_t x,uint8_t y);
	void drawBlock(uint16_t x,uint16_t y, uint8_t type, uint8_t size);
	void setDrawBlock(uint8_t x, uint8_t y, uint8_t type);
	bool updateMap();
	void setRadius(uint8_t x, uint8_t y, uint8_t radius, uint8_t type);
	void explosion(uint8_t x, uint8_t y, uint8_t radius);
	bool isEmpty(uint8_t x, uint8_t y, uint8_t size);
	void drawPart(int8_t x, int8_t y, uint8_t size);
protected:
private:

}; //Map

#include "Main.h"

#endif //__MAP_H__
