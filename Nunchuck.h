/* 
* Nunchuck.h
*
* Created: 10-12-2018 14:16:13
* Author: kapte
*/


#ifndef __NUNCHUCK_H__
#define __NUNCHUCK_H__
#define pwrpin PC3
#define gndpin PC2

#include "Arduino.h"
#include "Player.h"
#include "Communication.h"

#include <Wire.h>

#include "SPI.h"

class Nunchuck
{
//variables
public:
	int x;
	int y;
	bool c;
	bool z;
	uint8_t nunchuck_buf[6];
protected:
private:

//functions
public:
	Nunchuck();
	~Nunchuck();
	void update();
	
protected:
private:
void nunchuck_send_request();
int nunchuck_get_data();
char nunchuk_decode_byte (char x);


}; //Nunchuck

#endif //__NUNCHUCK_H__
