/*
 * kbsmenu.ino
 *
 * Created: 12/3/2018 2:50:24 PM
 * Author: kapte
 */ 

#include "Arduino.h"
#include "Button.h"
#include "SettingsPanel.h"
#include "MenuPanel.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup(){
	init();
	tft.begin();
	tft.setRotation(1);
	Button::begin();
	Serial.begin(9600);
}

void drawTitle(uint16_t x, uint16_t color, String naam){
		tft.setCursor(x, 10);
		tft.setTextColor(color);
		tft.setTextSize(5);
		tft.println(naam);
}

void drawLable(uint16_t x, uint16_t y,uint16_t color, String naam){
	tft.setCursor(x, y);
	tft.setTextColor(color);
	tft.setTextSize(2);
	tft.println(naam);
}

void drawButton(uint16_t x,uint16_t y, uint16_t color, uint16_t color2, String naam){
	
	tft.fillRect(x, y, 170, 30, color2);
	tft.setCursor(x+4, y+4);
	tft.setTextColor(color);
	tft.setTextSize(3);
	tft.println(naam);
}


void drawMenu(){
	tft.fillScreen(ILI9341_BLACK);
	tft.setRotation(1);
	drawTitle(40, 0xFFFF, "Wurpmies");
	//drawButton(60, 60, 0x0000, 0x8010, "New game");
	//drawButton(60, 100,0xFFFF, 0x8010, "Join game");
	//drawButton(60, 140,0x0000, 0xFFFF, "Settings");
	Button* start = new Button(75, 60, 170, 30, "New game", ILI9341_BLUE);
	Button* join = new Button(75, 100, 170, 30, "Join game", ILI9341_BLUE);
	Button* settings = new Button(75, 140, 170, 30, "Settings", ILI9341_BLUE);
	start->draw(tft);
	join->draw(tft);
	settings->draw(tft);
	while(1){
		if(settings->clicked()){
			drawSettings();
		}
	}
}

void drawSettings(){
	tft.fillScreen(ILI9341_BLACK);
	tft.setRotation(1);
	drawTitle(40, 0xFFFF, "Settings");
	drawLable(20, 60, 0xFFFF, "- Send frequency?");
	Button* optie1 = new Button(30, 80, 90, 30, "38 KHz", ILI9341_GREEN);
	Button* optie2 = new Button(130, 80, 90, 30, "56 KHz", ILI9341_RED);
	Button* back = new Button(210, 200, 70, 30, "Back", ILI9341_BLUE);
	optie1->draw(tft);
	optie2->draw(tft);
	back->draw(tft);
	
	while(1){
		if(back->clicked()){
			delete optie1, optie2, back;
			return;
		}
		if(optie1->clicked()){
			optie1->color = ILI9341_GREEN;
			optie2->color = ILI9341_RED;
			optie1->draw(tft);
			optie2->draw(tft);
		}
		if(optie2->clicked()){
			optie2->color = ILI9341_GREEN;
			optie1->color = ILI9341_RED;
			optie1->draw(tft);
			optie2->draw(tft);
		}
	}
	
	
}

main(){
	setup();
	MenuPanel* menu = new MenuPanel();
	menu->draw(tft);
	menu->update(tft);
	
	
}
