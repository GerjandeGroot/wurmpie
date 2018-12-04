/* 
* Button.cpp
*
* Created: 4-12-2018 10:24:09
* Author: gerja
*/


#include "Button.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define STMPE_CS 8
static Adafruit_STMPE610 Button::ts = Adafruit_STMPE610(STMPE_CS);

// default constructor
Button::Button(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, String text, uint16_t color)
{
	this->x = x;
	this->y = y;
	this->xSize = xSize;
	this->ySize = ySize;
	this->text = text;
	this->color = color;
} //Button

void Button::draw(Adafruit_ILI9341 tft) {
	tft.fillRect(this->x,this->y,this->xSize,this->ySize,this->color);
	tft.setTextColor(0xFFFFFF);
	tft.setTextSize(2);
	uint8_t textXSize = this->text.length()*2*6;
	uint8_t textYSize =	2*7;
	tft.setCursor(this->x+((this->xSize-textXSize)/2),this->y+((this->ySize-textYSize)/2));
	tft.print(this->text);
}

// default destructor
Button::~Button()
{
} //~Button
