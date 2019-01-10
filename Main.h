/* 
* Main.h
*
* Created: 6-12-2018 13:31:51
* Author: gerja
*/


#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Custom_ILI9341.h"
#include "Button.h"
#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "Nunchuck.h"
#include "Weapon.h"
#include "Powerup.h"

#define verticalDifference 15
#define averageDifference 30

#define TFT_CS 10
#define TFT_DC 9

class Player;

class Main
{
//variables
public:
	static Adafruit_ILI9341 tft;
	static Map map;
	static uint8_t beurt;
	static Player player1;
	static Player player2;
	static Button menuWeapon;
protected:
private:

//functions
public:
	Main();
	~Main();
	void update();
	void menu();
	static int freeRam();
	void serialTest();
	static void beginMaster();
	static void beginSlave();
	void parseData();
	static void draw();
	static void drawTurn(String tekst);
	static void selectDrop();
	void master();
	void dropWeapon(uint8_t type);
protected:
private:

}; //Main

#endif //__MAIN_H__
