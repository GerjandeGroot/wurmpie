/* 
* Player.h
*
* Created: 28-11-2018 09:20:05
* Author: gerja
*/


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Custom_ILI9341.h"
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
uint8_t weapon[9] = {1,2,3,4,5,6,7,8,9};
uint8_t selectedWeapon;
int8_t aimDx;
int8_t aimDy;
uint8_t fuel;

protected:
private:

//functions
public:
	Player(uint16_t color);
	Player();
	~Player();
	void draw();
	void clear();
	void moveTo(int x, int y, bool send=true);
	void sendAim();
	bool moveToDirection(uint8_t direction);
	void shoot();

protected:
private:
}; //Player

#endif //__PLAYER_H__
