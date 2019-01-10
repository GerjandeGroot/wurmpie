/* 
* Powerup.cpp
*
* Created: 19-12-2018 11:10:52
* Author: kapte
*/


#include "Powerup.h"

static Powerup* Powerup::powerups[10];
static uint8_t Powerup::powerupAmount = 0;

// default constructor
Powerup::Powerup(uint8_t xpos)
{
	this->xpos = xpos;
	ypos = 0;
	powerups[powerupAmount] = this;
	powerupAmount++;
} //Powerup

// default destructor
Powerup::~Powerup()
{
} //~Powerup

void Powerup::draw(){
	Main::tft.fillRect(xpos, ypos+verticalOffset, blocksize, blocksize, ILI9341_PINK);
	
}

void Powerup::clear(){
	Main::tft.fillRect(xpos, ypos+verticalOffset, blocksize, blocksize, Main::map.backgroundColor);
}

void Powerup::drop(){
	while(Main::map.isEmpty((xpos/blocksize), (ypos)/blocksize+1, 1)){
		moveTo(ypos+1);
		_delay_ms(10);
	}
}

void Powerup::moveTo(uint8_t ypos){
	clear();
	this->ypos = ypos;
	draw();
}
bool Powerup::send(){
	Communication::send(xpos);
	Communication::send(14);
	return Communication::endCommand();
}

void Powerup::collision(Player *player){
	uint8_t leftCoor = abs(player->x /* - blocksize*/);
	uint8_t rightCoor = abs(player->x /* + blocksize*/);
	
	//Loop array powerup
	for(int i = 0; i < Powerup::powerupAmount; i++){
		if(leftCoor == Powerup::powerups[i] || rightCoor == Powerup::powerups[i]){//xpos
			uint8_t randomNumber = random(8);
			player->addWeapon(randomNumber);
		}
	}
}
