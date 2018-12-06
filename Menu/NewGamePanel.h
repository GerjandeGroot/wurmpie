/* 
* NewGamePanel.h
*
* Created: 5-12-2018 15:20:07
* Author: kapte
*/


#ifndef __NEWGAMEPANEL_H__
#define __NEWGAMEPANEL_H__

#include "Arduino.h"
#include "Button.h"
#include <Adafruit_ILI9341.h>

class NewGamePanel
{
//variables
public:
protected:
private:
Button* random_map;
Button* existing_map;
Button* back;

//functions
public:
	NewGamePanel();
	~NewGamePanel();
	void draw(Adafruit_ILI9341 tft);
	void update(Adafruit_ILI9341 tft);
	void drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam);
	void drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam);
protected:
private:


}; //NewGamePanel

#endif //__NEWGAMEPANEL_H__
