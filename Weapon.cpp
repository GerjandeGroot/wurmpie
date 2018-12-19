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
	Serial.print("type = ");
	Serial.println(type);
	this->x = x;
	this->y = y;
	this->type = type;
	
	//calculate dx dy
	this->dx = (float)dx/(float)10;
	this->dy = (float)dy/(float)10;
	fireShot(type);
} //Weapon

// default destructor
Weapon::~Weapon()
{
} //~Weapon
void Weapon::fireShot(uint8_t type){
		switch(type){
			case 1:
				defaultShot();
				break;
			case 2:
				grenade();
				break;
			case 7:
				tripleShot();
				break;
		}
}

void Weapon::defaultShot() {
	for(uint8_t i = 0; i < 200; i++) {
		Serial.print(dx);
		Serial.print("\t");
		Serial.println(dy);
		moveTo(x - dx, y - dy);
		this->dy -= 0.025;
		if(Main::map.getBlock(x/blocksize, y/blocksize)) break;
		_delay_ms(10);
	}
	Main::map.explosion(this->x/blocksize,this->y/blocksize,2);
}

void Weapon::grenade() {
	for(uint8_t i = 0; i < 200; i++) {
		Serial.print(dx);
		Serial.print("\t");
		Serial.println(dy);
		moveTo(x - dx, y - dy);
		this->dy -= 0.025;
		if(Main::map.getBlock((x-dx)/blocksize, y/blocksize)){
			dx = dx*-0.65;			
		}
		if(Main::map.getBlock(x/blocksize, (y-dy)/blocksize)){
			dy = dy*-0.65;
		}
		_delay_ms(10);
	}
	Main::map.explosion(this->x/blocksize,this->y/blocksize,4);
}

void Weapon::tripleShot() {
	for(uint8_t count = 0; count < 3; count++){
		Weapon(x, y, 1, dx*10, dy*10);
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
		return F("Triple");
		case 8:
		return F("number8");
		case 9:
		return F("number9");
		
	}
}