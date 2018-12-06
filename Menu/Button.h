/* 
* Button.h
*
* Created: 4-12-2018 10:24:10
* Author: gerja
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Arduino.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_STMPE610.h>

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
protected:
private:
	uint16_t x;
	uint16_t y;
	uint16_t xSize;
	uint16_t ySize;
	String text;

	bool selected;

//functions
public:
	Button(uint16_t, uint16_t, uint16_t, uint16_t, String, uint16_t);
	~Button();
	void draw(Adafruit_ILI9341 tft);
	bool clicked();
	static begin();
protected:
private:
	Button( const Button &c );
	Button& operator=( const Button &c );

}; //Button

#endif //__BUTTON_H__
