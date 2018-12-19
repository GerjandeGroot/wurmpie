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

static Button Main::menuWeapon = Button(220, 0, 100, 20, "Default", ILI9341_BLUE);

//default constructor
Main::Main()
{
	sei();
	Serial.begin(9600);
	Serial.println(1);
	
	tft.begin();
	tft.setRotation(3);
	Communication::begin();
	
	
	
	Button::begin();
	
	menu();
	update();
	
} //Main

//default destructor
Main::~Main()
{
} //~Main

void Main::update() {
	Nunchuck nunchuck;
	draw();
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
			if(menuWeapon.clicked()) {
				Menu().weaponSelectionPanel(&player1);
				draw();
			}
			player1.aimDx = (nunchuck.x-133)/-4;
			player1.aimDy = (nunchuck.y-137)/4;
			player1.clear();
			player1.draw();
			player1.sendAim();
			if(nunchuck.z) {
				Communication::send(12);
				Communication::endCommand();
				player1.shoot();
				beurt = 4;
			}
		} else if (beurt == 4) {
			if(!player1.moveToDirection(3) && !map.updateMap()) {
				beurt = 5;
				player1.fuel = 10;
				Communication::send(4);
				Communication::endCommand();
				drawTurn("enemy turn");
			}
		} else if (beurt == 5) {
			map.updateMap();
		}
		map.updateMap();
		parseData();
	}
}

void Main::parseData() {
	Communication::update();
	if(Communication::buffer[0] == 255) {
		Communication::removeParameter();
		if(Communication::buffer[0] == 10) {
			player2.clear();
			player2.x = Communication::buffer[1];
			player2.y = Communication::buffer[2];
			player2.draw();
			Communication::clearBuffer(3);
			Communication::next();
		}
		if(Communication::buffer[0] == 11) {
			player2.clear();
			player2.aimDx = Communication::buffer[1];
			player2.aimDy = Communication::buffer[2];
			player2.draw();
			Communication::clearBuffer(3);
			Communication::next();
		}
		if(Communication::buffer[0] == 12) {
			Communication::next();
			player2.shoot();
			Communication::clearBuffer(1);
		}
		if(Communication::buffer[0] == 4) {
			beurt = 1;
			Communication::clearBuffer(1);
			Communication::next();
			drawTurn("your turn");
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
			player1.x = Communication::buffer[2];
			player1.y = Communication::buffer[3];
			Communication::clearBuffer(4);
			Communication::next();
			break;
		}
	}
	while (1) {
		Communication::update();
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 10) {
			player2.x = Communication::buffer[2];
			player2.y = Communication::buffer[3];
			Communication::clearBuffer(4);
			Communication::next();
			break;
		}
	}
	beurt = 5;
}
void Main::beginMaster() {
	Communication::send(map.seed);
	Communication::send(3);
	Communication::endCommand();
	
	player2.moveTo(30,0);
	
	player1.moveTo(10,0);
	
	beurt = 1;
}

void Main::draw(){
	map.drawMap();
	player1.draw();
	player2.draw();
	menuWeapon.draw();
}

void Main::drawTurn(String tekst){
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(25, 100);
	tft.setTextSize(4);
	tft.setTextColor(ILI9341_WHITE);
	tft.println(tekst);
	_delay_ms(1000);
	draw();
}