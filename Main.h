/* 
* Main.h
*
* Created: 6-12-2018 13:31:51
* Author: gerja
*/


#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "Button.h"
#include "Menu.h"
#include "Map.h"

#define verticalDifference 15
#define averageDifference 30

#define TFT_CS 10
#define TFT_DC 9

class Main
{
//variables
public:
	static Adafruit_ILI9341 tft;
protected:
private:

//functions
public:
	Main();
	~Main();
	void update();
	void menu();
	static int freeRam();
protected:
private:

}; //Main

#endif //__MAIN_H__
