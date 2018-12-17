/* 
* Weapon.cpp
*
* Created: 12-12-2018 11:50:00
* Author: kapte
*/


#include "Weapon.h"

// default constructor
Weapon::Weapon(float x, float y, uint8_t type, int8_t dx, int8_t dy)
{
	this->x = x;
	this->y = y;
	this->type = type;
	
	//calculate dx dy
	this->dx = (float)dx/(float)10;
	this->dy = (float)dy/(float)10;
	update();
	Main::map.explosion(this->x/blocksize,this->y/blocksize,4);
} //Weapon

// default destructor
Weapon::~Weapon()
{
} //~Weapon

void Weapon::update() {
	for(uint8_t i = 0; i < 200; i++) {
		Serial.print(dx);
		Serial.print("\t");
		Serial.println(dy);
		moveTo(x - dx, y - dy);
		this->dy -= 0.025;
		if(Main::map.getBlock(x/blocksize, y/blocksize)) return;
		_delay_ms(10);
	}
}

void Weapon::clear() {
	Main::tft.fillCircle(this->x,this->y,blocksize/2,ILI9341_CYAN);
}

void Weapon::draw() {
	Main::tft.fillCircle(this->x,this->y,blocksize/2,ILI9341_BLACK);
}

void Weapon::moveTo(float x, float y) {
	clear();
	this->x = x;
	this->y = y;
	draw();
}

String Weapon::getName(uint8_t type){
	String name;
	switch(type){
		default:
		return F("ERROR");
		case 1:
		return F("Default");
		case 2:
		return F("Grenade");
		case 3:
		return F("Nuke");
		case 4:
		return F("Strike");
		case 5:
		return F("EMP");
		case 6:
		return F("Laser");
		case 7:
		return name = F("Triple");
		case 8:
		return F("number8");
		case 9:
		return F("number9");
		
	}
}