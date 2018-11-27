/* 
* IRLib.h
*
* Created: 27-11-2018 11:02:04
* Author: gerja
*/

#include "Arduino.h"

#ifndef __IRLIB_H__
#define __IRLIB_H__

#define spacer 300
#define startBit 600
#define stopBit 800
#define highBit 400
#define lowBit 200

class IRLib
{
//variables
public:
volatile static uint8_t received;
volatile static long signalStart;
volatile static uint8_t count;
volatile static uint8_t receiving;
volatile static uint8_t bit;
volatile static bool _available;
protected:
private:

//functions
public:
	static read();
	static bool available();
	static void begin(int frequency);
protected:
private:
}; //IRLib

#endif //__IRLIB_H__
