/* 
* Player.cpp
*
* Created: 28-11-2018 09:20:05
* Author: gerja
*/


#include "Player.h"

// default constructor
Player::Player(uint16_t color)
{
	x = 255;
	y = 255;
	aimDirection = 20;
	aimStrength = 10;
	fuel = 10;
} //Player

// default destructor
Player::~Player()
{
} //~Player

void Player::draw() {
	Main::tft.fillRoundRect(this->x*blocksize, this->y*blocksize+blocksize, blocksize*2,blocksize, blocksize/4,this->color);
	Main::tft.fillCircle(this->x*blocksize+blocksize, this->y*blocksize+blocksize, blocksize/2, this->color);
// 	uint8_t a = aimDirection++;
// 	uint8_t b = 180-90-a;
// 	uint8_t dy = (double)aimStrength/sin(90)*sin(a);
// 	uint8_t dx = (double)aimStrength/sin(90)*sin(b);
// 	Main::tft.drawLine(this->x*blocksize+blocksize, this->y*blocksize+blocksize, this->x*blocksize+blocksize-dx, this->y*blocksize+blocksize-dy, this->color);
// 	Serial.print(a);
// 	Serial.print("/t");
// 	Serial.println(dy);
}

void Player::clear() {
	Main::tft.fillRect(this->x*blocksize, this->y*blocksize, blocksize*2,blocksize*2, ILI9341_CYAN);
}

bool Player::moveToDirection(Map map, uint8_t direction) {
	uint8_t fuel = 100;
	if(direction == 0) {
		if(y > 0 && map.getBlock(x,y-2) == 0,map.getBlock(x+1,y-2) == 0) {
			y--;
			return true;
		}
	} else if (direction == 1) {			//boven
		if(map.isEmpty(x,y-1,tankSize)) {
			moveTo(x,y-1);
			return true;
		}
		if(map.isEmpty(x+1,y-1,tankSize)) {
			moveTo(x+1,y-1);
			return true;
		}
		if(map.isEmpty(x-1,y-1,tankSize)) {
			moveTo(x-1,y-1);
			return true;
		}
	} else if (direction == 2) {			//rechts
		if(map.isEmpty(x+1,y,tankSize)) {
			moveTo(x+1,y);
			return true;	
		}
		if(map.isEmpty(x+1,y-1,tankSize)) {
			moveTo(x+1,y-1);
			return true;
		}
	} else if (direction == 3) {			//beneden
		if(map.isEmpty(x,y+1,tankSize)) {
			moveTo(x,y+1);
			return true;
		}
		if(map.isEmpty(x+1,y+1,tankSize)) {
			moveTo(x+1,y+1);
			return true;
		}
		if(map.isEmpty(x-1,y+1,tankSize)) {
			moveTo(x-1,y+1);
			return true;
		}
	} else if (direction == 4) {			//links
			if(map.isEmpty(x-1,y,tankSize)) {
				moveTo(x-1,y);
				return true;
			}
			if(map.isEmpty(x-1,y-1,tankSize)) {
					moveTo(x-1,y-1);
					return true;
			}

	} else if (direction == 5) {			
		if(map.isEmpty(x,y+1,tankSize)) {
			moveTo(x,y+1);
			return true;
		}

	} else {
		
	}
	return false;
}

void Player::moveTo(int x, int y) {
	clear();
	this->x = x;
	this->y = y;
	draw();
}

void Player::sendLocation() {
	Communication::send(this->y);
	Communication::send(this->x);
	Communication::send(10);
	Communication::endCommand();
}