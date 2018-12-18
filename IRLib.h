/* 
* IRLib.h
*
* Created: 27-11-2018 11:02:04
* Author: gerja
*/

#include "Arduino.h"
#include "Communication.h"

#ifndef __IRLIB_H__
#define __IRLIB_H__

#define disableSignal TCCR0A |= 1 << COM0A0
#define enableSignal TCCR0A &= ~(1 << COM0A0)

#define spacer 300 //300
#define startBit 600  //600
#define stopBit 800	//800
#define highBit 400	//400
#define lowBit 200	//200
#define acknowledgeBit 1000 //10000
#define nonAcknowledgeBit 1200 //12000
#define posMargin 100	//100
#define negMargin 75	//50

#define ready 0
#define sending 4
#define waitingForAcknowledge 1
#define sendSucces 2
#define error 3

class IRLib
{
//variables
public:
volatile static uint32_t timer;
volatile static uint8_t count;
volatile static uint8_t receiving;
volatile static uint8_t bit;
volatile static uint8_t status;
volatile static uint32_t beginTime; 
protected:
private:

//functions
public:
	static void begin(int frequency);
	static bool send(uint16_t data);
	static uint32_t custom_micros();
	static void sendAcknowledge(bool succes);
	static void waitAcknowledge();
	static bool sendWait(uint16_t data);
	static void sendPulse(uint16_t time);
	static void custom_delay(uint32_t time);
protected:
private:
}; //IRLib

#endif //__IRLIB_H__
