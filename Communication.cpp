/* 
* Communication.cpp
*
* Created: 28-11-2018 10:56:14
* Author: gerja
*/


#include "Communication.h"


static bool Communication::serial;							//determines if serial or IR is used
volatile static uint16_t Communication::buffer[bufSize];	//buffer where command and parameters are stored

//start communication
void Communication::begin() {
	//read option serial or IR from EEPROM
	serial = !EEPROM.read(sendMethodAdres);
	
	if(serial) {	
		//start serial
	} else {
		//start IR
		//read frequency from EEPROM
		uint8_t frequency = EEPROM.read(freqAdres);
		IRLib::begin(frequency);
	}
} 

//send a handshake
bool Communication::sendHandshake() {
	Communication::send(1);
	return Communication::endCommand();
}

//waits for a handshake
bool Communication::waitForHandshake() {
	//Communication::update();
	if(Communication::buffer[0] == 255 && Communication::buffer[1] == 1) {
		Communication::next();
		Communication::clearBuffer(2);
		return true;
	}
	return false;
}

//sends a command or a parameter
bool Communication::send(uint16_t data) {
	if(serial) {
		UDR0 = data;
		while(!(UCSR0A &= 1 << TXC0));
		return true;
	} else {
		return IRLib::sendWait(data);
	}
}

//adds a parameter to the buffer
bool Communication::addParameter(uint16_t parameter) {
	for(int i = bufSize-1; i >= 0; i--) {
		Communication::buffer[i+1] = Communication::buffer[i];
	}
	Communication::buffer[0] = parameter;
	return	true;
}

//removes a parameter from the buffer
void Communication::removeParameter() {
	if(Communication::buffer[0] == 255 && !serial) {
		IRLib::sendAcknowledge(true);
	}
	for(int i = 0; i < bufSize-1; i++) {
		Communication::buffer[i] = Communication::buffer[i+1];
	}
	Communication::buffer[bufSize-1] = 0;
}

//removes multiple parameters from the buffer
void Communication::clearBuffer(int amount) {
	for(int i = 0; i < amount; i++) {
		Communication::removeParameter();
	}
}

//send a end command byte (255) and wait for a acknowledgment byte (254)
bool Communication::endCommand() {
//	acknowledge = false;
	Communication::send(255);
	for(int i = 0; i < 99999999; i++) {
//		update();
		if(buffer[0] == 254) {
			removeParameter();
			return true;
		}
		_delay_ms(1);
	}
	return false;
}

//sends a acknowledge
void Communication::next() {
	Communication::send(254);
}

//initialize USART 
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

//interrupt vector for receiving a byte from USART
ISR(USART_RX_vect)
{
	Communication::addParameter(UDR0);
}
