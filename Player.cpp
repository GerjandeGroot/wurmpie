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
	this->color = color;
	x = 255;
	y = 255;
	aimDx = 10;
	aimDy = 10;
	fuel = 10;
	health = 100;
} //Player
Player::Player()
{
	
}

// default destructor
Player::~Player()
{
} //~Player

void Player::draw() {
	Main::tft.fillRoundRect(this->x*blocksize, this->y*blocksize+blocksize, blocksize*2,blocksize, blocksize/4,this->color);
	Main::tft.fillCircle(this->x*blocksize+blocksize, this->y*blocksize+blocksize, blocksize/2, this->color);
 	Main::tft.drawLine(this->x*blocksize+blocksize, this->y*blocksize+blocksize, this->x*blocksize+blocksize-aimDx, this->y*blocksize+blocksize-aimDy, this->color);
	Main::tft.setCursor(x*blocksize-10, y*blocksize-10);
	Main::tft.setTextColor(ILI9341_RED);
	Main::tft.setTextSize(1);
	Main::tft.println(health);
	Main::tft.setCursor(x*blocksize+10, y*blocksize-10);
	Main::tft.setTextColor(ILI9341_BLUE);
	Main::tft.println(fuel);
}

void Player::clear() {
	Main::map.drawPart(x-3,y-3,8);
}

bool Player::moveToDirection(uint8_t direction) {
	if(direction == 0) {
		if(y > 0 && Main::map.getBlock(x,y-2) == 0,Main::map.getBlock(x+1,y-2) == 0) {
			y--;
			return true;
		}
	} else if (direction == 1) {			//boven
		if(Main::map.isEmpty(x,y-1,tankSize)) {
			moveTo(x,y-1);
			return true;
		}
		if(Main::map.isEmpty(x+1,y-1,tankSize)) {
			moveTo(x+1,y-1);
			return true;
		}
		if(Main::map.isEmpty(x-1,y-1,tankSize)) {
			moveTo(x-1,y-1);
			return true;
		}
	} else if (direction == 2) {			//rechts
		if(Main::map.isEmpty(x+1,y,tankSize)) {
			moveTo(x+1,y);
			return true;	
		}
		if(Main::map.isEmpty(x+1,y-1,tankSize)) {
			moveTo(x+1,y-1);
			return true;
		}
	} else if (direction == 3) {			//beneden
		if(Main::map.isEmpty(x,y+1,tankSize)) {
			moveTo(x,y+1);
			return true;
		}
		if(Main::map.isEmpty(x+1,y+1,tankSize)) {
			moveTo(x+1,y+1);
			return true;
		}
		if(Main::map.isEmpty(x-1,y+1,tankSize)) {
			moveTo(x-1,y+1);
			return true;
		}
	} else if (direction == 4) {			//links
			if(Main::map.isEmpty(x-1,y,tankSize)) {
				moveTo(x-1,y);
				return true;
			}
			if(Main::map.isEmpty(x-1,y-1,tankSize)) {
					moveTo(x-1,y-1);
					return true;
			}

	} else if (direction == 5) {			
		if(Main::map.isEmpty(x,y+1,tankSize)) {
			moveTo(x,y+1);
			return true;
		}

	} else {
		
	}
	return false;
}

void Player::moveTo(int x, int y, bool send) {
	if(send) {
		Communication::send(y);
		Communication::send(x);
		Communication::send(10);
		Communication::endCommand();
	}
	clear();
	this->x = x;
	this->y = y;
	draw();
}

void Player::sendAim() {
	Communication::send(this->aimDy);
	Communication::send(this->aimDx);
	Communication::send(11);
	Communication::endCommand();
}

void Player::shoot() {
	Weapon(this->x*blocksize+blocksize-aimDx, this->y*blocksize+blocksize-aimDy,1,aimDx,aimDy);
}


//tan(o/a) = o/a