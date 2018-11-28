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

#define tankSize 20


class Player
{
//variables
public:
uint16_t x;
uint16_t y;
uint8_t health;
uint16_t color;
uint8_t weapon;

protected:
private:

//functions
public:
	Player();
	~Player();
	void draw(Adafruit_ILI9341 tft);
	void clear(Adafruit_ILI9341 tft);
	void moveTo(int x, int y);
	void sendLocation();
protected:
private:
}; //Player

#endif //__PLAYER_H__
