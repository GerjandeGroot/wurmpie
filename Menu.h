/* 
* Menu.h
*
* Created: 7-12-2018 09:56:13
* Author: gerja
*/


#ifndef __MENU_H__
#define __MENU_H__

#include "Arduino.h"
#include "Button.h"
#include "EEPROM.h"
#include "Player.h"
#include "Custom_ILI9341.h"

#define freqAdres 0x0
#define sendMethodAdres 0x1

class Menu
{
//variables
public:
protected:
private:

//functions
public:
	Menu();
	~Menu();
	void setPanel(uint8_t panel);
	uint8_t mainPanel();
	uint8_t settingsPanel();
	uint8_t joinPanel();
	uint8_t newGamePanel();
	uint8_t mapSelectionPanel();
	uint8_t newGameLobbyPanel();
	void drawTitle(uint16_t x, uint16_t color, String naam);
	void drawLable(uint16_t x, uint16_t y,uint16_t color, String naam);
	uint8_t weaponSelectionPanel(Player *player);
protected:
private:

}; //Menu

#endif //__MENU_H__
