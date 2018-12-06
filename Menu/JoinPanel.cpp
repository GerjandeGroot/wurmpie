/* 
* JoinPanel.cpp
*
* Created: 5-12-2018 15:45:53
* Author: kapte
*/


#include "JoinPanel.h"

// default constructor
JoinPanel::JoinPanel()
{
	this->cancel = new Button(75, 200, 170, 30, "Cancel", ILI9341_BLUE);
} //JoinPanel

// default destructor
JoinPanel::~JoinPanel()
{
	delete this->cancel;
} //~JoinPanel

void JoinPanel::draw(Adafruit_ILI9341 tft){
	tft.fillScreen(ILI9341_BLACK);
	drawTitle(tft, 40, 0xFFFF, "Join game");
	drawLable(tft, 20, 100, 0xFFFF, "Searching for master");
	cancel->draw(tft);
	
}

void JoinPanel::update(Adafruit_ILI9341 tft){
	while(1){
		if(this->cancel->clicked()){
			Serial.println("cancel");
			return;
		}
	}
}

void JoinPanel::drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam){
	tft.setCursor(x, 10);
	tft.setTextColor(color);
	tft.setTextSize(5);
	tft.println(naam);
}

void JoinPanel::drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam){
	tft.setCursor(x, y);
	tft.setTextColor(color);
	tft.setTextSize(2);
	tft.println(naam);
}