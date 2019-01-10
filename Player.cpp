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
	weapon[9] = 1;
	selectedWeapon = 0;
	stunned = false;
} //Player

// default destructor
Player::~Player()
{
} //~Player*
void Player::draw() {
	Main::tft.fillRoundRect(this->x*blocksize, this->y*blocksize+blocksize+verticalOffset, blocksize*2,blocksize, blocksize/4,this->color);
	Main::tft.fillCircle(this->x*blocksize+blocksize, this->y*blocksize+blocksize+verticalOffset, blocksize/2, this->color);
 	Main::tft.drawLine(this->x*blocksize+blocksize, this->y*blocksize+blocksize+verticalOffset, this->x*blocksize+blocksize-aimDx, this->y*blocksize+blocksize+verticalOffset-aimDy, this->color);
	Main::tft.setCursor(x*blocksize, y*blocksize+verticalOffset-8);
	Main::tft.setTextColor(ILI9341_RED);
	Main::tft.setTextSize(1);
	Main::tft.println(health);
}
	

void Player::clear() {
	Main::map.drawPart(x-3,y-3,8);
}

bool Player::moveToDirection(uint8_t direction, bool send) {
	if(direction == 0) {
		if(y > 0 && Main::map.getBlock(x,y-2) == 0,Main::map.getBlock(x+1,y-2) == 0) {
			y--;
			return true;
		}
	} else if (direction == 1) {			//boven
		if(Main::map.isEmpty(x,y-1,tankSize)) {
			moveTo(x,y-1,send);
			return true;
		}
		if(Main::map.isEmpty(x+1,y-1,tankSize)) {
			moveTo(x+1,y-1,send);
			return true;
		}
		if(Main::map.isEmpty(x-1,y-1,tankSize)) {
			moveTo(x-1,y-1,send);
			return true;
		}
	} else if (direction == 2 && x < horizontalSize-2) {			//rechts
		if(Main::map.isEmpty(x+1,y,tankSize)) {
			moveTo(x+1,y,send);
			return true;	
		}
		if(Main::map.isEmpty(x+1,y-1,tankSize)) {
			moveTo(x+1,y-1,send);
			return true;
		}
	} else if (direction == 3) {			//beneden
		if(Main::map.isEmpty(x,y+1,tankSize)) {
			moveTo(x,y+1,send);
			return true;
		}
		if(Main::map.isEmpty(x+1,y+1,tankSize)) {
			moveTo(x+1,y+1,send);
			return true;
		}
		if(Main::map.isEmpty(x-1,y+1,tankSize)) {
			moveTo(x-1,y+1,send);
			return true;
		}
	} else if (direction == 4 && x > 1) {			//links
			if(Main::map.isEmpty(x-1,y,tankSize)) {
				moveTo(x-1,y,send);
				return true;
			}
			if(Main::map.isEmpty(x-1,y-1,tankSize)) {
					moveTo(x-1,y-1,send);
					return true;
			}

	} else if (direction == 5) {			
		if(Main::map.isEmpty(x,y+1,tankSize)) {
			moveTo(x,y+1,send);
			return true;
		}

	} else {
		
	}
	return false;
}

void Player::moveTo(int x, int y, bool send) {
	if(y > verticalSize){
		health = 0;
	}
	if(send) {
		sendLocation(x,y);
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
	Weapon(this->x*blocksize+blocksize-aimDx, this->y*blocksize+blocksize-aimDy,weapon[selectedWeapon],aimDx,aimDy);
}

bool Player::sendLocation(uint8_t x, uint8_t y) {
	Communication::send(y);
	Communication::send(x);
	Communication::send(10);
	Communication::endCommand();
}

void Player::addWeapon(uint8_t x){
	for(int i = 0; i<9; i++){
		if(weapon[i] == 0){
			Player::weapon[i] = x;
			return;
		}	
	}	
}


void Player::removeWeapon(uint8_t x){
	for (int i = x; i < 8; i++)	{
		weapon[i] = weapon[i+1];
	}
	weapon[9] = 0;
	selectedWeapon = 0;
}




void Player::fuelBar(){
	Main::tft.fillRect(0,0, 100, 16, ILI9341_GREEN);	
}

void Player::updateFuelBar(){
	if(fuel == 7){
		Main::tft.fillRect(0,0, fuel*10, 16, ILI9341_ORANGE);
	} else if(fuel == 3){
		Main::tft.fillRect(0,0, fuel*10, 16, ILI9341_RED);
	}
	Main::tft.fillRect(0 + fuel*10, 0, 10, 16, ILI9341_BLACK);
	
}


