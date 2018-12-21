/* 
* Powerup.h
*
* Created: 19-12-2018 11:10:53
* Author: kapte
*/


#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Main.h"

class Powerup
{
//variables
public:
	uint8_t xpos;
	uint8_t ypos;
	static Powerup* powerups[10];
	static uint8_t powerupAmount;
protected:
private:

//functions
public:
	Powerup(uint8_t xpos);
	~Powerup();
	void draw();
	void drop();
	bool send();
protected:
private:
	void clear();
	void moveTo(uint8_t ypos);
	
}; //Powerup

#endif //__POWERUP_H__
