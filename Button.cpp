/* 
* Button.cpp
*
* Created: 4-12-2018 10:24:09
* Author: gerja
*/


#include "Button.h"

static Adafruit_STMPE610 Button::ts = Adafruit_STMPE610(STMPE_CS);	//ts object
static TS_Point Button::touch = TS_Point(0,0,0);					//last touched point

//init button 
Button::begin() {
	if (!ts.begin()) { //start touchscreen
	}
}

//constructor 
Button::Button(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, String text, uint16_t color)
{
	//store parameters for button
	this->x = x;
	this->y = y;
	this->xSize = xSize;
	this->ySize = ySize;
	this->text = text;
	this->color = color;
	//draw the button
 	draw();
} //Button

//draws the button
void Button::draw() {
	Main::tft.fillRect(this->x,this->y,this->xSize,this->ySize,this->color);
 	Main::tft.setTextColor(0xFFFFFF);
 	Main::tft.setTextSize(2);
 	uint8_t textXSize = this->text.length()*2*6;
 	uint8_t textYSize =	2*7;
 	Main::tft.setCursor(this->x+((this->xSize-textXSize)/2),this->y+((this->ySize-textYSize)/2));
 	Main::tft.print(this->text);
}

//determines if button is clicked
bool Button::clicked() {
	// rotate coordinate system
	int y = 240 - touch.x;
	int x = touch.y;
	
	//check if last touch position is on this button
	if((x > this->x) && (x < (this->x + this->xSize))) {
		if ((y > this->y) && (y <= (this->y + this->ySize))) {
			//empty the buffer and resume when user releases button
			while(ts.touched()) {
				ts.getPoint();	
			}
			touch = TS_Point(0,0,0);
			return true;
		}
	}
	return false;
}

//updates last touch point
Button::update() {
	//check if user touched the screen
	if(!ts.bufferEmpty()) {
		//if user touched screen get next point and store it in last touched point
		touch = ts.getPoint();
		// Scale using the calibration #'s
		touch.x = map(touch.x, TS_MINY, TS_MAXY, 240, 0);
		touch.y = map(touch.y, TS_MINX, TS_MAXX, 320, 0);
	} else {
		//if user didn't touch the screen store set coordinates to 0,0
		touch = TS_Point(0,0,0);
	}
}

// default destructor
Button::~Button()
{
} //~Button
