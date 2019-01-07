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
	
	if(serial) {	
	} else {
		uint8_t frequency = EEPROM.read(freqAdres);
		IRLib::begin(frequency);
	}
} 

bool Communication::handshake() {
	return Communication::send(1);
}

bool Communication::send(uint16_t data) {
	if(serial) {
		UDR0 = data;
		while(!(UCSR0A &= 1 << TXC0));
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
	if(Communication::buffer[0] == 255 && !serial) {
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
	
}

void Communication::USART_Init()
{
	cli();
	//setting baud rate
	UBRR0H = (uint8_t) (serialSpeed >> 8);
	UBRR0L = (uint8_t) serialSpeed;
	
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	//1 stop bit 8 data bit
	UCSR0C = (3<<UCSZ00);
	sei();
}

ISR(USART_RX_vect)
{
	Communication::addParameter(UDR0);
}
