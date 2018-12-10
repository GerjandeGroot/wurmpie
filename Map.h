/* 
* Map.h
*
* Created: 6-12-2018 15:48:04
* Author: gerja
*/


#ifndef __MAP_H__
#define __MAP_H__

#include "Arduino.h"
#include <Adafruit_ILI9341.h>
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
protected:
private:

//functions
public:
	Map();
	~Map();
	void createRandomMap();
	void drawMap();
	void clearMap();
	void setBlock(uint8_t x,uint8_t y,uint8_t type);
	uint8_t getBlock(uint8_t x,uint8_t y);
	void drawBlock(uint8_t x,uint8_t y, uint8_t type);
	void setDrawBlock(uint8_t x, uint8_t y, uint8_t type);
	bool updateMap();
	void setRadius(uint8_t x, uint8_t y, uint8_t radius, uint8_t type);
	void explosion(uint8_t x, uint8_t y, uint8_t radius);
	bool isEmpty(uint8_t x, uint8_t y, uint8_t size);
protected:
private:

}; //Map

#include "Main.h"

#endif //__MAP_H__
