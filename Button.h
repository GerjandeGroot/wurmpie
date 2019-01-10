/* 
* Button.h
*
* Created: 4-12-2018 10:24:10
* Author: gerja
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Arduino.h"
#include "Custom_ILI9341.h"
#include "Custom_STMPE610.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define STMPE_CS 8

class Button
{
//variables
public:
	static Adafruit_STMPE610 ts;
	uint16_t color;
	String text;
protected:
private:
	uint16_t x;
	uint16_t y;
	uint16_t xSize;
	uint16_t ySize;
	static TS_Point touch;

//functions
public:
	Button(uint16_t, uint16_t, uint16_t, uint16_t, String, uint16_t);
	~Button();
	void draw();
	bool clicked();
	static begin();
	static update();
protected:
private:

}; //Button

#include "Main.h"
#endif //__BUTTON_H__
