/*
* Main.cpp
*
* Created: 6-12-2018 13:31:51
* Author: gerja
*/


#include "Main.h"

static Adafruit_ILI9341 Main::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
static Map Main::map = Map();

// default constructor
Main::Main()
{
	init();
	
	tft.begin();
	tft.setRotation(1);
	
	Serial.begin(9600);
	Serial.println("hello");
	
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
	player1.moveTo(10,0);
	player2.moveTo(30,0);
	map.createRandomMap();
	draw();
	beurt = 1;
	while(1){
		if(menuWeapon.clicked()){
			Menu().weaponSelectionPanel();
			draw();
		}
		nunchuck.update();
		if(beurt == 1){
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
				
				beurt = 5;
				draw();
				player1.fuel = 10;
			}
			
			
		} else if(beurt = 5){
			beurt = 1;
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

void Main::draw(){
	drawTurn();
	map.drawMap();
	player1.draw();
	player2.draw();
	menuWeapon.draw();
	beurt = 1;
}

void Main::drawTurn(){
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(25, 100);
	tft.setTextSize(5);
	tft.setTextColor(ILI9341_WHITE);
	if(beurt = 1){
		tft.println("Your turn");
	}
	_delay_ms(1000);
}

