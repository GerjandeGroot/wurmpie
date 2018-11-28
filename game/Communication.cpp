/* 
* Communication.cpp
*
* Created: 28-11-2018 10:56:14
* Author: gerja
*/


#include "Communication.h"

static bool Communication::serial;
static uint16_t Communication::buffer[bufferSize];
static uint8_t Communication::parameters = 0;
static bool Communication::acknowledge = false;

void Communication::begin() {
	//Setup serial
	Serial.begin(serialSpeed);
	
	//todo setup 9 bit
	
	
	IRLib::begin(irFrequency);
}

bool Communication::handshake() {
	//Send handshake on serial
	Serial.write(1);
	
	for(int i = 0; i < 1000; i++) {
		if(parameters == 1 && buffer[0] == 2) {
			Communication::serial = true;
			Communication::clearBuffer();
			return true;
		}
		_delay_ms(1);
	}
	
	IRLib::send(1);
	
	for(int i = 0; i < 1000; i++) {
		if(parameters == 1 && buffer[0] == 2) {
			Communication::clearBuffer();
			return true;
		}
		_delay_ms(1);
	}
	
	return false;
}

void Communication::send(uint16_t data) {
	acknowledge = false;
	if(serial) {
		Serial.write(data);
	} else {
		IRLib::send(data);
	}
}

bool Communication::waitAcknowledge(uint16_t timeout) {
	for(int i = 0; i < timeout; i++) {
		if(Communication::acknowledge)
			return true;
		_delay_ms(1);
	}
	return false;
}

bool Communication::addParameter(uint16_t parameter) {
	if(Communication::parameters == bufferSize) return false;
	Communication::buffer[parameters] = parameter;
	Communication::parameters++;
	return true;
}

void Communication::clearBuffer() {
	Communication::parameters = 0;
}

ISR(USART_RXC_vect)
{
	//ReceivedByte;
	//ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	//UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}
