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
//function for switching between menu panels
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
				panel = mapSelectionPanel();
				break;
			case 5:
				panel = newGameLobbyPanel();
				break;
		}
	}
}
//function for drawing a standard title
void Menu::drawTitle(uint16_t x, uint16_t color, String naam){
	Main::tft.setCursor(x, 10);
	Main::tft.setTextColor(color);
	Main::tft.setTextSize(5);
	Main::tft.println(naam);
}
//function for drawing a standard lable
void Menu::drawLable(uint16_t x, uint16_t y,uint16_t color, String naam){
	Main::tft.setCursor(x, y);
	Main::tft.setTextColor(color);
	Main::tft.setTextSize(2);
	Main::tft.println(naam);
}
//function for main menu panel
uint8_t Menu::mainPanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "Wurmpies");
	
	Button new_game(75, 60, 170, 30, "New game", ILI9341_BLUE);
	Button join(75, 100, 170, 30, "Join game", ILI9341_BLUE);
	Button settings(75, 140, 170, 30, "Settings", ILI9341_BLUE);
	
	while(1){
		Button::update();
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
//function for settings panel
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
		Button::update();
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
//function for join game panel
uint8_t Menu::joinPanel() {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(25, 0xFFFF, "Join game"); //25 voor midden (9 characters)
	drawLable(20, 100, 0xFFFF, "Searching for host");
	
	Button cancel(75, 200, 170, 30, "Cancel", ILI9341_BLUE);
	
	while(1){
		Button::update();
		if(Communication::sendHandshake()) {
			Main::beginSlave();
			return 0;
		}
		if(cancel.clicked()){
			return 1;
		}
	}
}
//function for map selection panel
uint8_t Menu::mapSelectionPanel(){
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(10, 0xFFFF, "Select map");	//10 voor midden (10 characters)
	Button btnPrev(5, 115, 30, 30, "<", ILI9341_BLUE);
	Button btnNext(285, 115, 30, 30, ">", ILI9341_BLUE);
	Button back(0, 210, 60, 30, "Back", ILI9341_BLUE);
	Button next(260, 210, 60, 30, "Next", ILI9341_BLUE);
	
	uint8_t seed = EEPROM.read(3);
	seed++;
	EEPROM.write(3,seed);
	Main::map.createRandomMap(seed);
	Main::map.drawMapSmall(60, 55, 5);
	
	while(1){
		Button::update();
		if(btnPrev.clicked()){
			seed = EEPROM.read(3);
			seed--;
			EEPROM.write(3,seed);
			Main::map.createRandomMap(seed);
			Main::map.drawMapSmall(60, 55, 5);
		}
		if(btnNext.clicked()){
			seed = EEPROM.read(3);
			seed++;
			EEPROM.write(3,seed);
			Main::map.createRandomMap(seed);
			Main::map.drawMapSmall(60, 55, 5);
		}
		if(back.clicked()){
			return 1;
		}
		if(next.clicked()){
			return 5
			;
		}
	}
}
//function for new game waiting panel
uint8_t Menu::newGameLobbyPanel(){
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, "New Game"); //40 voor midden (8 characters)
	drawLable(20, 100, 0xFFFF, "Searching for opponent");

	Button cancel(75, 200, 170, 30, "Cancel", ILI9341_BLUE);

	while(1){
		Button::update();
		if(Communication::waitForHandshake()) {
			Main::beginMaster();
			return 0;
		}
		if(cancel.clicked()){
			return 4;
		}
	}
}
//function for end panel message will contain your turn or enemy turn
uint8_t Menu::endPanel(String msg) {
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(40, 0xFFFF, msg); //40 voor midden (8 characters)
	
	Button menu(260, 210, 60, 30, "Menu", ILI9341_BLUE);
	
	while(1){
		Button::update();
		if(menu.clicked()){
			return 0;
		}
	}
}
//function for weapon selection panel, this menu is in game
uint8_t Menu::weaponSelectionPanel(Player *player){
	Main::tft.fillScreen(ILI9341_BLACK);
	drawTitle(60, 0xFFFF, F("Weapons"));
	Button* buttons[5];
	uint8_t aantalButtons = 0;
	for(int i = 0; i < 5; i++){
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
		}
		uint8_t weaponName = player->weapon[i];
		if(weaponName == 0){
			break;
		}
		buttons[i] = new Button(x, y, 100, 50, Weapon::getName(weaponName), ILI9341_BLUE);
		aantalButtons++;
	}
	while(1){
		Button::update();
		for(int i = 0; i < aantalButtons; i++){
			if(buttons[i]->clicked()){
				player->selectedWeapon = i;
				Communication::send(Main::player1.weapon[i]);
				Communication::send(13);
				Communication::endCommand();
				Main::menuWeapon.text = Weapon::getName(player->weapon[player->selectedWeapon]);
				for(int i = 0; i < aantalButtons; i++){
					delete buttons[i];
				}
				return;
			}
		}
	}
}