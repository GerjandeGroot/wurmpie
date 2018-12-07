/* 
* Main.cpp
*
* Created: 6-12-2018 13:31:51
* Author: gerja
*/


#include "Main.h"

static Adafruit_ILI9341 Main::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// default constructor
Main::Main()
{
	init();
	
	tft.begin();
	tft.setRotation(1);
	
	Serial.begin(9600);
	Serial.println("hello");
	
	Button::begin();
	
	menu();
	update();
		
} //Main

// default destructor
Main::~Main()
{
} //~Main

void Main::update() {
	
 	Map card;
	while(1){
		card.createRandomMap();
		card.drawMap();
		card.explosion(random(40),random(30),5);
		while(card.updateMap()){};
	};
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