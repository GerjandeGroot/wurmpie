/* 
* Communication.h
*
* Created: 28-11-2018 10:56:14
* Author: gerja
*/


#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include "Arduino.h"
#include "IRLib.h"
#include "Menu.h"

#define serialSpeed 103
#define bufSize 4

class Communication
{
//variables
public:
	static bool serial;
	volatile static uint16_t buffer[bufSize];
	volatile static bool acknowledge;
	volatile static bool _available;
protected:
private:

//functions
public:
	static void USART_Init();
	static void clearBuffer(int amount);
	static bool waitAcknowledge(uint16_t timeout);
	static void begin();
	static bool send(uint16_t data);
	static void start();
	static bool handshake();
	static bool addParameter(uint16_t data);
	static bool endCommand();
	static void removeParameter();
	static bool available();
	static void next();
	static void update();
protected:
private:
}; //Communication

#endif //__COMMUNICATION_H__
