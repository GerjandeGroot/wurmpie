/* 
* SettingsPanel.h
*
* Created: 4-12-2018 13:51:44
* Author: kapte
*/


#ifndef __SETTINGSPANEL_H__
#define __SETTINGSPANEL_H__

#include "Arduino.h"
#include "Button.h"
#include <Adafruit_ILI9341.h>

class SettingsPanel
{
//variables
public:
protected:
private:
Button* optie1;
Button* optie2;
Button* back;


//functions
public:
	SettingsPanel();
	~SettingsPanel();
	void draw(Adafruit_ILI9341 tft);
	void update(Adafruit_ILI9341 tft);
	void drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam);
	void drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam);
protected:
private:
	

}; //SettingsPanel

#endif //__SETTINGSPANEL_H__
