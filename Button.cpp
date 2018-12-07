/* 
* Button.cpp
*
* Created: 4-12-2018 10:24:09
* Author: gerja
*/


#include "Button.h"

static Adafruit_STMPE610 Button::ts = Adafruit_STMPE610(STMPE_CS);

Button::begin() {
	if (!ts.begin()) {
		Serial.println("Unable to start touchscreen.");
	}
	else {
		Serial.println("Touchscreen started.");
	}
}

// default constructor
Button::Button(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, String text, uint16_t color)
{
	this->x = x;
	this->y = y;
	this->xSize = xSize;
	this->ySize = ySize;
	this->text = text;
	this->color = color;
	draw();
} //Button

void Button::draw() {
	Main::tft.fillRect(this->x,this->y,this->xSize,this->ySize,this->color);
	Main::tft.setTextColor(0xFFFFFF);
	Main::tft.setTextSize(2);
	uint8_t textXSize = this->text.length()*2*6;
	uint8_t textYSize =	2*7;
	Main::tft.setCursor(this->x+((this->xSize-textXSize)/2),this->y+((this->ySize-textYSize)/2));
	Main::tft.print(this->text);
}

bool Button::clicked() {
	if (!ts.bufferEmpty()) {
		TS_Point p = ts.getPoint();
		// Scale using the calibration #'s
		// and rotate coordinate system
		p.x = map(p.x, TS_MINY, TS_MAXY, 0, 240);
		p.y = map(p.y, TS_MINX, TS_MAXX, 0, 320);
		int y = 240 - p.x;
		int x = p.y;

		if((x > this->x) && (x < (this->x + this->xSize))) {
			if ((y > this->y) && (y <= (this->y + this->ySize))) {
				return true;
			}
		}
	}
	return false;
}

// default destructor
Button::~Button()
{
} //~Button
