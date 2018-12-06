/* 
* NewGamePanel.cpp
*
* Created: 5-12-2018 15:20:07
* Author: kapte
*/


#include "NewGamePanel.h"

// default constructor
NewGamePanel::NewGamePanel()
{
	this->random_map = new Button(75, 60, 170, 30, "Random map", ILI9341_BLUE);
	this->existing_map = new Button(75, 100, 170, 30, "Existing map", ILI9341_BLUE);
	this->back = new Button(210, 200, 70, 30, "Back", ILI9341_BLUE);
} //NewGamePanel

// default destructor
NewGamePanel::~NewGamePanel()
{
	delete this->random_map, this->existing_map, this->back;
} //~NewGamePanel

void NewGamePanel::draw(Adafruit_ILI9341 tft){
	tft.fillScreen(ILI9341_BLACK);
	drawTitle(tft, 40, 0xFFFF, "New game");
	random_map->draw(tft);
	existing_map->draw(tft);
	back->draw(tft);
}

void NewGamePanel::update(Adafruit_ILI9341 tft){
	while(1){
		if(this->random_map->clicked()){
			Serial.println("random map");
		}
		if(this->existing_map->clicked()){
			Serial.println("existing map");
		}
		if(this->back->clicked()){
			Serial.println("back");
			return;
		}
	}
}

void NewGamePanel::drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam){
	tft.setCursor(x, 10);
	tft.setTextColor(color);
	tft.setTextSize(5);
	tft.println(naam);
}

void NewGamePanel::drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam){
	tft.setCursor(x, y);
	tft.setTextColor(color);
	tft.setTextSize(2);
	tft.println(naam);
}