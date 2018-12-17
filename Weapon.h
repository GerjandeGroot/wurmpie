/* 
* Weapon.h
*
* Created: 12-12-2018 11:50:00
* Author: kapte
*/


#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Arduino.h"
#include "Main.h"
#include "Map.h"

class Weapon
{
//variables
public:
protected:
private:
	uint8_t type;
	float x;
	float y;
	float dx;
	float dy;

//functions
public:
	Weapon(float x, float y, uint8_t type, int8_t dx, int8_t dy);
	~Weapon();
protected:
private:
	void update();
	void draw();
	void clear();
	void moveTo(float x, float y);
	bool collisionDetect();
	void explode();

}; //Weapon

#endif //__WEAPON_H__
