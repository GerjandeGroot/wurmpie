/* 
* Communication.cpp
*
* Created: 28-11-2018 10:56:14
* Author: gerja
*/


#include "Communication.h"

static bool Communication::serial;
volatile static uint16_t Communication::buffer[bufSize];
volatile static bool Communication::acknowledge = false;
volatile static bool Communication::_available = false;

void Communication::begin() {
	//Setup serial
	serial = !EEPROM.read(sendMethodAdres);
	
	if(false) {
		Serial.begin(serialSpeed);	
	} else {
		Serial.begin(9600);
		uint8_t frequency = EEPROM.read(freqAdres);
		IRLib::begin(frequency);
	}
	_delay_ms(100);
} 

bool Communication::handshake() {
	//Send handshake on serial
	
	//handshake on ir
	Serial.println("sending handshake");
	return Communication::send(1);
}

bool Communication::send(uint16_t data) {
	if(serial) {
		Serial.write(data);
		return true;
	} else {
		return IRLib::sendWait(data);

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
	for(int i = bufSize-1; i >= 0; i--) {
		Communication::buffer[i+1] = Communication::buffer[i];
	}
	Communication::buffer[0] = parameter;
	return	true;
}

void Communication::removeParameter() {
	if(Communication::buffer[0] == 255) {
		IRLib::sendAcknowledge(true);
	}
	for(int i = 0; i < bufSize-1; i++) {
		Communication::buffer[i] = Communication::buffer[i+1];
	}
	Communication::buffer[bufSize-1] = 0;
}

void Communication::clearBuffer(int amount) {
	for(int i = 0; i < amount; i++) {
		Communication::removeParameter();
	}
}

bool Communication::endCommand() {
	acknowledge = false;
	Communication::send(255);
	
	for(int i = 0; i < 99999999; i++) {
		update();
		if(buffer[0] == 254) {
			removeParameter();
			return true;
		}
		_delay_ms(1);
	}
	return false;
}

bool Communication::available() {
	return Communication::_available;
}
void Communication::next() {
	Communication::send(254);
	Communication::_available = false;
}

void Communication::update() {
	while(Serial.available()) addParameter(Serial.read());
}

ISR(USART_RXC_vect)
{
	//ReceivedByte;
	//ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	//UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}
