/* 
* SettingsPanel.cpp
*
* Created: 4-12-2018 13:51:44
* Author: kapte
*/


#include "SettingsPanel.h"

// default constructor
SettingsPanel::SettingsPanel()
{
	this->optie1 = new Button(30, 80, 90, 30, "38 KHz", ILI9341_GREEN);
	this->optie2 = new Button(130, 80, 90, 30, "56 KHz", ILI9341_RED);
	this->back = new Button(210, 200, 70, 30, "Back", ILI9341_BLUE);
} //SettingsPanel

// default destructor
SettingsPanel::~SettingsPanel()
{
	delete this->optie1, this->optie2, this->back;
} //~SettingsPanel

void SettingsPanel::draw(Adafruit_ILI9341 tft){
	tft.fillScreen(ILI9341_BLACK);
	drawTitle(tft, 40, 0xFFFF, "Settings");
	drawLable(tft, 20, 60, 0xFFFF, "- Send frequency?");
	optie1->draw(tft);
	optie2->draw(tft);
	back->draw(tft);
}

void SettingsPanel::update(Adafruit_ILI9341 tft){
	while(1){
		if(this->back->clicked()){
			Serial.println("back");
			return;
		}
		if(this->optie1->clicked()){
			Serial.println("optie1");
			this->optie1->color = ILI9341_GREEN;
			this->optie2->color = ILI9341_RED;
			this->optie1->draw(tft);
			this->optie2->draw(tft);
		}
		if(this->optie2->clicked()){
			Serial.println("optie2");
			this->optie2->color = ILI9341_GREEN;
			this->optie1->color = ILI9341_RED;
			this->optie1->draw(tft);
			this->optie2->draw(tft);
		}
	}
}

void SettingsPanel::drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam){
	tft.setCursor(x, 10);
	tft.setTextColor(color);
	tft.setTextSize(5);
	tft.println(naam);
}

void SettingsPanel::drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam){
	tft.setCursor(x, y);
	tft.setTextColor(color);
	tft.setTextSize(2);
	tft.println(naam);
}