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
	Nunchuck nunchuck;
	Player player1(ILI9341_BLUE);
	Player player2(ILI9341_RED);
	card.createRandomMap();
	card.drawMap();
	
	while(1){
		
		nunchuck.update();
			
			if(nunchuck.x > 100 && nunchuck.x < 200 && nunchuck.y > 100 && nunchuck.y < 200 || !(player1.fuel > 0)){
				player1.moveToDirection(card, 3);
			} else {
				if(nunchuck.x > 150){					//rechts
					player1.moveToDirection(card, 2);
				}
				if(nunchuck.x < 110){					//links
					player1.moveToDirection(card, 4);
				}
				if(nunchuck.y < 110){					//beneden
					player1.moveToDirection(card, 3);
				}
				if(nunchuck.y > 170){					//jetpack
					player1.moveToDirection(card, 1);

				}else{
					player1.moveToDirection(card, 5);
				}
				player1.fuel--;
				Serial.println(player1.fuel);
			}
			_delay_ms(100);

		//player1.moveTo(nunchuck.x, nunchuck.y);

		//card.explosion(random(40),random(30),5);
		//while(card.updateMap()){};
			
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