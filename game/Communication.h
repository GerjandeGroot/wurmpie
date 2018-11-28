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

#define serialSpeed 9600
#define irFrequency 56
#define bufferSize 4

class Communication
{
//variables
public:
	static bool serial;
	static uint16_t buffer[bufferSize];
	static uint8_t parameters;
	static bool acknowledge;
protected:
private:

//functions
public:
	static void clearBuffer();
	static bool waitAcknowledge(uint16_t timeout);
	static void begin();
	static void send(uint16_t data);
	static void start();
	static bool handshake();
	static bool addParameter(uint16_t data);
protected:
private:
}; //Communication

#endif //__COMMUNICATION_H__
