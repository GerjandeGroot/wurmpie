/*
* Main.cpp
*
* Created: 6-12-2018 13:31:51
* Author: gerja
*/


#include "Main.h"

static Adafruit_ILI9341 Main::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
static Map Main::map = Map();
static Player Main::player1 = Player(ILI9341_BLUE);
static Player Main::player2 = Player(ILI9341_RED);
static uint8_t Main::beurt = 0;

// default constructor
Main::Main()
{
	init();
	
	tft.begin();
	tft.setRotation(1);
	
	Communication::begin();
		
	Button::begin();
	
	beurt = 0;
	
	menu();
	update();
	
} //Main

// default destructor
Main::~Main()
{
} //~Main

void Main::update() {
	Nunchuck nunchuck;
	map.drawMap();
	while(1){
		
		nunchuck.update();
		if(beurt == 1){
			player2.draw();
			if(nunchuck.c || !(player1.fuel > 0)){
					beurt = 2;			
			} else if(nunchuck.x > 100 && nunchuck.x < 200 && nunchuck.y > 100 && nunchuck.y < 200){
					player1.moveToDirection(3);
			} else {
				if(nunchuck.x > 150){					//rechts
					player1.moveToDirection(2);
				}
				if(nunchuck.x < 110){					//links
					player1.moveToDirection(4);
				}
				if(nunchuck.y < 110){					//beneden
					player1.moveToDirection(3);
				}
				if(nunchuck.y > 170){					//jetpack
					player1.moveToDirection(1);

				}else{
					player1.moveToDirection(5);
				}
				player1.fuel--;
			}
			
		} else if (beurt == 2) {
			if(!player1.moveToDirection(3))
				beurt = 3;
		} else if (beurt == 3) {
			player1.aimDx = (nunchuck.x-133)/-4;
			player1.aimDy = (nunchuck.y-137)/4;
			player1.clear();
			player1.draw();
			if(nunchuck.z) {
				player1.shoot();
				beurt = 4;
			}
		} else if (beurt == 4) {
			if(!player1.moveToDirection(3) && !map.updateMap()) {
				beurt = 1;
				player1.fuel = 10;
			}
			
		}
		if(beurt == 3) {
			_delay_ms(10);
		} else {
			_delay_ms(100);	
		}
	}
}

void Main::menu() {
	Menu menu = Menu();
	menu.setPanel(1);
}

int Main::freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

bool Main::sendHandshake() {	
	Communication::send(1);
	return Communication::endCommand();
}

bool Main::waitForHandshake() {
	Communication::update();
	if(Communication::buffer[0] == 255 && Communication::buffer[1] == 1) {
		Communication::clearBuffer(2);
		Communication::next();
		return true;
	}
	return false;
}

void Main::beginSlave() {
	
	while (1) {
		Communication::update();
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 3) {
			map.createRandomMap(Communication::buffer[2]);
			Communication::clearBuffer(3);
			Communication::next();
			break;
		}
	}
	while (1) {
		Communication::update();
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 10) {
			player1.moveTo(Communication::buffer[2], Communication::buffer[3]);
			Communication::clearBuffer(4);
			Communication::next();
			break;
		}
	}
	while (1) {
		Communication::update();
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 10) {
			player2.moveTo(Communication::buffer[2], Communication::buffer[3]);
			Communication::clearBuffer(4);
			Communication::next();
			return;
		}
	}
	beurt = 6;	
}
void Main::beginMaster() {
	Communication::send(map.seed);
	Communication::send(3);
	Communication::endCommand();
	
	player2.moveTo(30,0);
	player2.sendLocation();
	
	player1.moveTo(10,0);
	player1.sendLocation();
	
	beurt = 1;
}
