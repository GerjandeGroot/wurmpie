/* 
* Communication.cpp
*
* Created: 28-11-2018 10:56:14
* Author: gerja
*/


#include "Communication.h"

static bool Communication::serial;
volatile static uint16_t Communication::buffer[bufferSize];
volatile static bool Communication::acknowledge = false;
volatile static bool Communication::_available = false;

void Communication::begin() {
	//Setup serial
	Serial.begin(serialSpeed);
	
	//todo setup 9 bit
	
	
	IRLib::begin(irFrequency);
	_delay_ms(100);
}

bool Communication::handshake() {
	//Send handshake on serial
	
	//handshake on ir
	Serial.println("sending handshake");
	return Communication::send(1);
}

bool Communication::send(uint16_t data) {
	acknowledge = false;
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
	if(Communication::buffer[0] == 255) return false;
// 	if (parameter == 255) {
// 		Serial.print("new command");
// 		Communication::_available = true;
// 		return false;
// 	}
	for(int i = bufferSize-1; i >= 0; i--) {
		Communication::buffer[i+1] = Communication::buffer[i];
	}
	Communication::buffer[0] = parameter;
	return Communication::buffer[0] != 255;
}

void Communication::removeParameter() {
	if(Communication::buffer[0] == 255) {
		IRLib::sendAcknowledge(true);
	}
	for(int i = 0; i < bufferSize-1; i++) {
		Communication::buffer[i] = Communication::buffer[i+1];
	}
	Communication::buffer[bufferSize-1] = 0;
}

void Communication::clearBuffer(int amount) {
	for(int i = 0; i < amount; i++) {
		Communication::removeParameter();
	}
}

bool Communication::endCommand() {
	Communication::send(255);
}

bool Communication::available() {
	return Communication::_available;
}
void Communication::next() {
	Communication::_available = false;
	IRLib::sendAcknowledge(true);
	Serial.println("end command");
}

ISR(USART_RXC_vect)
{
	//ReceivedByte;
	//ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	//UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}
