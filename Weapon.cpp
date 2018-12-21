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
		case 6:
		laser();
		break;
		case 7:
		tripleShot();
		break;
		case 3:
		nukeShot();
		break;
	}
}

void Weapon::damageToPlayers(double damageMultiplier, uint8_t range) {
	float damage = hitDectectie(x/blocksize, y/blocksize, Main::player1.x+1, Main::player1.y+1, range);
	int8_t health = Main::player1.health - damage*damageMultiplier;
	if(health < 1)	{
		Main::player1.health = 0;
		} else {
		Main::player1.health = health;
	}
	
	damage = hitDectectie(x/blocksize, y/blocksize, Main::player2.x+1, Main::player2.y+1, range);
	health = Main::player2.health - damage*damageMultiplier;
	if(health < 1)	{
		Main::player2.health = 0;
	} else {
		Main::player2.health = health;
	}
	//Serial.println(damage);
}

float Weapon::hitDectectie(uint8_t explosionX,uint8_t explosionY, uint8_t middleX,uint8_t middleY, uint8_t radius){
	uint8_t dx = abs(explosionX - middleX);
	uint8_t dy = abs(explosionY - middleY);
	float distance = sqrt(dx*dx + dy*dy);
	
	Serial.println(distance/radius);
	
	if(distance > radius) {
		Serial.println("not hit");
		return 0;
	} else {
		Serial.println("hit");
		return 1-distance/radius;
	}
	
// 	int dmg = radius;
// 	for(int i = 0; i <= radius +1 ; i++){
// 		if(explosionX != middleX){
// 			explosionX++;
// 			} if (explosionY != middleY){
// 			explosionY++;
// 		}
// 		dmg--;
// 		if(explosionX == middleX && explosionY == middleY){
// 			dmg * 0,5;
// 			i = radius;
// 			return dmg;
// 		}
// 	}
// 	return 0;

}

void Weapon::defaultShot() {
	for(uint8_t i = 0; i < 200; i++) {
		moveTo(x - dx, y - dy);
		this->dy -= 0.025;
		if(Main::map.getBlock(x/blocksize, y/blocksize)) break;
		_delay_ms(10);
	}
	Main::map.explosion(this->x/blocksize,this->y/blocksize,2);
	damageToPlayers(10,2);
}

void Weapon::nukeShot() {
	for(uint8_t i = 0; i < 200; i++) {
		moveTo(x - dx, y - dy);
		this->dy -= 0.025;
		if(Main::map.getBlock(x/blocksize, y/blocksize)) break;
		_delay_ms(10);
	}
	Main::map.explosion(this->x/blocksize,this->y/blocksize,10);
	damageToPlayers(500,10);
}


void Weapon::grenade() {
	for(uint8_t i = 0; i < 200; i++) {
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
	damageToPlayers(15,4);
}

void Weapon::tripleShot() {
	for(uint8_t count = 0; count < 3; count++){
		Weapon(x, y, 1, dx*10, dy*10);
	}
}

void Weapon::laser(){
	while(1){
		Main::map.setRadius((x - dx*2)/8, (y - dy*2)/8, 2, 0, false);
		damageToPlayers(2,2);
		moveTo(x - dx*2, y - dy*2);
		if(x > 320 || x < 0 || y > 240 || y < 0){
			break;
		}
	}
	_delay_ms(500);
	Main::draw();
}

void Weapon::clear() {
	if(type == 6){
		
	}
	else{
		Main::tft.fillCircle(this->x,this->y,blocksize/2,ILI9341_CYAN);
	}
}

void Weapon::draw() {
	if(type == 6){
		Main::tft.fillCircle(this->x,this->y,blocksize/2,ILI9341_YELLOW);
	}
	else{
		Main::tft.fillCircle(this->x,this->y,blocksize/2,ILI9341_BLACK);
	}
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
