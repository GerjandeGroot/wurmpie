/* 
* MenuPanel.h
*
* Created: 5-12-2018 12:04:31
* Author: kapte
*/


#ifndef __MENUPANEL_H__
#define __MENUPANEL_H__

#include "Arduino.h"
#include "Button.h"
#include "SettingsPanel.h"
#include "NewGamePanel.h"
#include "JoinPanel.h"
#include <Adafruit_ILI9341.h>

class MenuPanel
{
//variables
public:
protected:
private:
Button* new_game;
Button* join;
Button* settings;
SettingsPanel* settingsPanel;
NewGamePanel* newGamePanel;
JoinPanel* joinPanel;

//functions
public:
	MenuPanel();
	~MenuPanel();
	void draw(Adafruit_ILI9341 tft);
	void update(Adafruit_ILI9341 tft);
	void drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam);
	void drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam);
protected:
private:
	
	
}; //MenuPanel

#endif //__MENUPANEL_H__
