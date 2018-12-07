/* 
* Menu.cpp
*
* Created: 7-12-2018 09:56:13
* Author: gerja
*/


#include "Menu.h"

// default constructor
Menu::Menu()
{
	Serial.println("Menu created");
} //Menu

// default destructor
Menu::~Menu()
{
	Serial.println("Menu destroyed");
} //~Menu

void Menu::setPanel(uint8_t panel) {
	while(panel > 0) {
		switch(panel) {
			case 1:
				panel = mainPanel();
				break;
			case 2:
				panel = settingsPanel();
				break;
			case 3:
				panel = joinPanel();
				break;
			case 4:
				panel = newGamePanel();
				break;
		}
		Button::ts.writeRegister8(STMPE_INT_STA, 0xFF);
	}
}

void Menu::drawTitle(uint16_t x, uint16_t color, String naam){
	Main::tft.setCursor(x, 10);
	Main::tft.setTextColor(color);
	Main::tft.setTextSize(5);
	Main::tft.println(naam);
}

void Menu::drawLable(uint16_t x, uint16_t y,uint16_t color, String naam){
	Main::tft.setCursor(x, y);
	Main::tft.setTextColor(color);
	Main::tft.setTextSize(2);
	Main::tft.println(naam);
}

uint8_t Menu::mainPanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "Wurmpies");
	
	Button new_game(75, 60, 170, 30, "New game", ILI9341_BLUE);
	Button join(75, 100, 170, 30, "Join game", ILI9341_BLUE);
	Button settings(75, 140, 170, 30, "Settings", ILI9341_BLUE);
	
	while(1){
		if(new_game.clicked()){
			return 4;
		}
		if(join.clicked()){
			return 3;
		}
		if(settings.clicked()){
			return 2;
		}
	}
}

uint8_t Menu::settingsPanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "Settings");
	drawLable(20, 60, 0xFFFF, "- Send frequency?");
	drawLable(20, 120, 0xFFFF, "- Send method?");
	
	Button optie1(30, 80, 90, 30, "38 KHz", ILI9341_BLUE);
	Button optie2(130, 80, 90, 30, "56 KHz", ILI9341_BLUE);
	Button optie3(30, 140, 90, 30, "Serial", ILI9341_BLUE);
	Button optie4(130, 140, 90, 30, "IR", ILI9341_BLUE);
	Button back(210, 200, 70, 30, "Back", ILI9341_BLUE);
	
	
	if(EEPROM.read(freqAdres) == 38){
		optie1.color = ILI9341_GREEN;
		optie2.color = ILI9341_RED;
		} else if(EEPROM.read(freqAdres) == 56){
		optie2.color = ILI9341_GREEN;
		optie1.color = ILI9341_RED;
	}
	
	if(EEPROM.read(sendMethodAdres) == 0){
		optie3.color = ILI9341_GREEN;
		optie4.color = ILI9341_RED;
		} else if(EEPROM.read(sendMethodAdres) == 1){
		optie4.color = ILI9341_GREEN;
		optie3.color = ILI9341_RED;
	}
	
	optie1.draw();
	optie2.draw();
	optie3.draw();
	optie4.draw();
	
	while(1){
		if(back.clicked()){
			return 1;
		}
		
		if(optie1.clicked()){
			EEPROM.write(freqAdres, 38);
			optie1.color = ILI9341_GREEN;
			optie2.color = ILI9341_RED;
			optie1.draw();
			optie2.draw();
		}
		if(optie2.clicked()){
			EEPROM.write(freqAdres, 56);
			optie2.color = ILI9341_GREEN;
			optie1.color = ILI9341_RED;
			optie1.draw();
			optie2.draw();
		}
		if(optie3.clicked()){
			
			EEPROM.write(sendMethodAdres, 0);
			optie3.color = ILI9341_GREEN;
			optie4.color = ILI9341_RED;
			optie3.draw();
			optie4.draw();
		}
		if(optie4.clicked()){
			
			EEPROM.write(sendMethodAdres, 1);
			optie4.color = ILI9341_GREEN;
			optie3.color = ILI9341_RED;
			optie3.draw();
			optie4.draw();
		}
	}
}

uint8_t Menu::joinPanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "Join game");
	drawLable(20, 100, 0xFFFF, "Searching for master");
	
	Button cancel(75, 200, 170, 30, "Cancel", ILI9341_BLUE);
	
	while(1){
		if(cancel.clicked()){
			return 1;
		}
	}
}

uint8_t Menu::newGamePanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "New game");
	
	Button random_map(75, 60, 170, 30, "Random map", ILI9341_BLUE);
	Button existing_map(75, 100, 170, 30, "Existing map", 0x8410);
	Button back(210, 200, 70, 30, "Back", ILI9341_BLUE);
	
	while(1){
		if(random_map.clicked()){
			return 0;
		}
		if(existing_map.clicked()){
		}
		if(back.clicked()){
			return 0;
		}
	}
}