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
#include "Player.h"
#include "Map.h"
#include "Nunchuck.h"
#include "Weapon.h"

#define verticalDifference 15
#define averageDifference 30

#define TFT_CS 10
#define TFT_DC 9

class Main
{
//variables
public:
	static Adafruit_ILI9341 tft;
	static Map map;
	uint8_t beurt;
	Player player1 = Player(ILI9341_BLUE);
	Player player2 = Player(ILI9341_RED);
	Button menuWeapon = Button(280, 0, 40, 20, "W", ILI9341_BLUE);
protected:
private:

//functions
public:
	Main();
	~Main();
	void update();
	void menu();
	static int freeRam();
	void draw();
	void drawTurn();
protected:
private:

}; //Main

#endif //__MAIN_H__
