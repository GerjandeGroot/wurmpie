/* 
* MenuPanel.cpp
*
* Created: 5-12-2018 12:04:31
* Author: kapte
*/


#include "MenuPanel.h"

// default constructor
MenuPanel::MenuPanel()
{
		this->new_game = new Button(75, 60, 170, 30, "New game", ILI9341_BLUE);
		this->join = new Button(75, 100, 170, 30, "Join game", ILI9341_BLUE);
		this->settings = new Button(75, 140, 170, 30, "Settings", ILI9341_BLUE);
		this->settingsPanel = new SettingsPanel();
		this->newGamePanel = new NewGamePanel();
		this->joinPanel = new JoinPanel();
} //MenuPanel

// default destructor
MenuPanel::~MenuPanel()
{
	delete this->new_game, this->join, this->settings, this->settingsPanel;
} //~MenuPanel

void MenuPanel::draw(Adafruit_ILI9341 tft){
	tft.fillScreen(ILI9341_BLACK);
	drawTitle(tft, 40, 0xFFFF, "Wurmpies");
	new_game->draw(tft);
	join->draw(tft);
	settings->draw(tft);
}

void MenuPanel::update(Adafruit_ILI9341 tft){
	while(1){
		if(this->new_game->clicked()){
			Serial.println("New game");
			newGamePanel->draw(tft);
			newGamePanel->update(tft);
			this->draw(tft);
		}
		if(this->join->clicked()){
			Serial.println("Join game");
			joinPanel->draw(tft);
			joinPanel->update(tft);
			this->draw(tft);
		}
		if(this->settings->clicked()){
			Serial.println("Settings");
			settingsPanel->draw(tft);
			settingsPanel->update(tft);
			this->draw(tft);
		}
	}
}

void MenuPanel::drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam){
	tft.setCursor(x, 10);
	tft.setTextColor(color);
	tft.setTextSize(5);
	tft.println(naam);
}

void MenuPanel::drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam){
	tft.setCursor(x, y);
	tft.setTextColor(color);
	tft.setTextSize(2);
	tft.println(naam);
}