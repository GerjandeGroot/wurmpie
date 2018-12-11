/* 
* Player.h
*
* Created: 28-11-2018 09:20:05
* Author: gerja
*/


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Adafruit_ILI9341.h>
#include "Communication.h"
#include "Map.h"

#define tankSize 2


class Player
{
//variables
public:
uint8_t x;
uint8_t y;
uint8_t health;
uint16_t color;
uint8_t weapon;
uint8_t aimDirection;
uint8_t aimStrength;
uint8_t fuel;

protected:
private:

//functions
public:
	Player(uint16_t color);
	~Player();
	void draw();
	void clear();
	void moveTo(int x, int y);
	void sendLocation();
	bool moveToDirection(Map map, uint8_t direction);
protected:
private:
}; //Player

#endif //__PLAYER_H__
