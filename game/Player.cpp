/* 
* Player.cpp
*
* Created: 28-11-2018 09:20:05
* Author: gerja
*/


#include "Player.h"

// default constructor
Player::Player()
{
} //Player

// default destructor
Player::~Player()
{
} //~Player

void Player::draw(Adafruit_ILI9341 tft) {
	tft.fillCircle(this->x, this->y, tankSize, this->color);
}

void Player::clear(Adafruit_ILI9341 tft) {
	tft.fillCircle(this->x, this->y, tankSize, 1);
}

void Player::moveTo(int x, int y) {
	Serial.print("player moved to: ");
	Serial.print(Communication::buffer[1]);
	Serial.print("\t");
	Serial.println(Communication::buffer[2]);
}

void Player::sendLocation() {
	Communication::send(10);
	Communication::send(this->x);
	Communication::send(this->y);
}