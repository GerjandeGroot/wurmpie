/* 
* JoinPanel.h
*
* Created: 5-12-2018 15:45:54
* Author: kapte
*/


#ifndef __JOINPANEL_H__
#define __JOINPANEL_H__

#include "Arduino.h"
#include "Button.h"
#include <Adafruit_ILI9341.h>

class JoinPanel
{
//variables
public:
protected:
private:
Button* cancel;

//functions
public:
	JoinPanel();
	~JoinPanel();
	void draw(Adafruit_ILI9341 tft);
	void update(Adafruit_ILI9341 tft);
	void drawTitle(Adafruit_ILI9341 tft, uint16_t x, uint16_t color, String naam);
	void drawLable(Adafruit_ILI9341 tft, uint16_t x, uint16_t y,uint16_t color, String naam);
protected:
private:


}; //JoinPanel

#endif //__JOINPANEL_H__
