/* 
* Nunchuck.cpp
*
* Created: 10-12-2018 14:16:13
* Author: kapte
*/


#include "Nunchuck.h"

// default constructor
Nunchuck::Nunchuck()
{
	//Setting power pins for nunchuck
	DDRC |= _BV(pwrpin) | _BV(gndpin);
	PORTC &=~ _BV(gndpin);
	PORTC |= _BV(pwrpin);
	_delay_ms(100);  // wait for things to stabilize
	
	Wire.begin();  // join i2c bus as master
	Wire.beginTransmission(0x52); // transmit to device 0x52
	Wire.write(0x40);  // sends memory address
	Wire.write(0x00);  // sends sent a zero.
	Wire.endTransmission(); // stop transmitting
} //Nunchuck

// default destructor
Nunchuck::~Nunchuck()
{
} //~Nunchuck

// Send a request for data to the nunchuck
// was "send_zero()"
void Nunchuck::nunchuck_send_request(){
	Wire.beginTransmission(0x52); // transmit to device 0x52
	Wire.write(0x00);  // sends one byte
	Wire.endTransmission(); // stop transmitting
}

void Nunchuck::update(){
	nunchuck_get_data();
	x = nunchuck_buf[0];
	y = nunchuck_buf[1];
	c = ((nunchuck_buf[5] >> 1) & 1) ? 0 : 1;
	z = ((nunchuck_buf[5] >> 0) & 1) ? 0 : 1;
}

// Receive data back from the nunchuck,
// returns 1 on successful read. returns 0 on failure
int Nunchuck::nunchuck_get_data(){
	int cnt=0;
	Wire.requestFrom (0x52, 6); // request data from nunchuck
	while (Wire.available ()) {
		// receive byte as an integer
		nunchuck_buf[cnt] = nunchuk_decode_byte(Wire.read());
		cnt++;
	}

	Nunchuck::nunchuck_send_request(); // send request for next data payload
	// If we recieved the 6 bytes, then go print them
	if (cnt >= 5) {
		return 1; // success
	}
	return 0; //failure
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char Nunchuck::nunchuk_decode_byte (char x){
	x = (x ^ 0x17) + 0x17;
	return x;
}