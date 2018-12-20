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
	static String getName(uint8_t type);
protected:
private:
  uint8_t hitDectectie(uint16_t explosionX,uint16_t explosionY, uint16_t middleX,uint16_t middleY, uint8_t radius);
	void fireShot(uint8_t type);
	void defaultShot();
	void grenade();
	void tripleShot();
	void laser();
	void draw();
	void clear();
	void moveTo(float x, float y);
	bool collisionDetect();
	void explode();
}; //Weapon

#endif //__WEAPON_H__
