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
} //Menu

// default destructor
Menu::~Menu()
{
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
			case 5:
				panel = mapSelectionPanel();
				break;
			case 6:
				panel = newGameLobbyPanel();
				break;
		}
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
	Button back(260, 210, 60, 30, "Back", ILI9341_BLUE);
	
	
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
			EEPROM.update(freqAdres, 38);
			optie1.color = ILI9341_GREEN;
			optie2.color = ILI9341_RED;
			optie1.draw();
			optie2.draw();
		}
		if(optie2.clicked()){
			EEPROM.update(freqAdres, 56);
			optie2.color = ILI9341_GREEN;
			optie1.color = ILI9341_RED;
			optie1.draw();
			optie2.draw();
		}
		if(optie3.clicked()){
			
			EEPROM.update(sendMethodAdres, 0);
			optie3.color = ILI9341_GREEN;
			optie4.color = ILI9341_RED;
			optie3.draw();
			optie4.draw();
		}
		if(optie4.clicked()){
			
			EEPROM.update(sendMethodAdres, 1);
			optie4.color = ILI9341_GREEN;
			optie3.color = ILI9341_RED;
			optie3.draw();
			optie4.draw();
		}
	}
}

uint8_t Menu::joinPanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(25, 0xFFFF, "Join game"); //25 voor midden (9 characters)
	drawLable(20, 100, 0xFFFF, "Searching for master");
	
	Button cancel(75, 200, 170, 30, "Cancel", ILI9341_BLUE);
	
	while(1){
		if(Main::sendHandshake()) {
			Main::beginSlave();
			return 0;
		}
		if(cancel.clicked()){
			return 1;
		}
	}
}

uint8_t Menu::newGamePanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "New game"); //40 voor midden (8 characters)
	
	Button random_map(75, 60, 170, 30, "Random map", ILI9341_BLUE);
	Button existing_map(75, 100, 170, 30, "Existing map", ILI9341_BLUE);
	Button back(260, 210, 60, 30, "Back", ILI9341_BLUE);
	
	while(1){
		if(random_map.clicked()){
			uint8_t seed = EEPROM.read(3);
			seed++;
			EEPROM.write(3,seed);
			Main::map.createRandomMap(seed);
			return 6;
		}
		if(existing_map.clicked()){
			return 5;
		}
		if(back.clicked()){
			return 1;
		}
	}
}

uint8_t Menu::mapSelectionPanel(){
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(10, 0xFFFF, "Select map");	//10 voor midden (10 characters)
	Button btnPrev(5, 115, 30, 30, "<", ILI9341_BLUE);
	Main::map.drawMapSmall(60, 55, 5);
	Button btnNext(285, 115, 30, 30, ">", ILI9341_BLUE);
	Button back(260, 210, 60, 30, "Back", ILI9341_BLUE);
	
	while(1){
		if(btnPrev.clicked()){
		}
		if(btnNext.clicked()){
		}
		if(back.clicked()){
			return 4;
		}
	}
}

uint8_t Menu::newGameLobbyPanel(){
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "New Game"); //40 voor midden (8 characters)
	drawLable(20, 100, 0xFFFF, "Searching for other player");

	Button cancel(75, 200, 170, 30, "Cancel", ILI9341_BLUE);

	while(1){
		if(Main::waitForHandshake()) {
			Main::beginMaster();
			return 0;
		}
		if(cancel.clicked()){
			return 4;
		}
	}
}

uint8_t Menu::weaponSelectionPanel(Player *player){
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(60, 0xFFFF, F("Weapons"));
	Button* buttons[9];
	uint8_t aantalButtons = 0;
	for(int i = 0; i < 9; i++){
		uint16_t x,y;
		
		switch(i){
			case 0:
			x = 5;
			y = 70;
			break;
			case 1:
			x = 110;
			y = 70;
			break;
			case 2:
			x = 215;
			y = 70;
			break;
			case 3:
			x = 5;
			y = 130;
			break;
			case 4:
			x = 110;
			y = 130;
			break;
			case 5:
			x = 215;
			y = 130;
			break;
			case 6:
			x = 5;
			y = 190;
			break;
			case 7:
			x = 110;
			y = 190;
			break;
			case 8:
			x = 215;
			y = 190;
			break;
		}
		uint8_t weaponName = player->weapon[i];
		if(weaponName == 0){
			break;
		}
		buttons[i] = new Button(x, y, 100, 50, Weapon::getName(weaponName), ILI9341_BLUE);
		aantalButtons++;
	}
	while(1){
		for(int i = 0; i < aantalButtons; i++){
			if(buttons[i]->clicked()){
				player->selectedWeapon = i;
				Main::menuWeapon.text = Weapon::getName(player->weapon[player->selectedWeapon]);
				for(int i = 0; i < aantalButtons; i++){
					delete buttons[i];
				}
				return;
			}
		}
	}
}