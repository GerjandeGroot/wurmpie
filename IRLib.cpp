/* 
* IRLib.cpp
*
* Created: 27-11-2018 11:02:04
* Author: gerja
*/


#include "IRLib.h"

volatile static uint32_t IRLib::timer = 0;
volatile static uint8_t IRLib::count = 0;
volatile static uint8_t IRLib::receiving = 0;
volatile static uint8_t IRLib::bit = 0;
volatile static uint8_t IRLib::status = 0;

volatile static uint32_t IRLib::beginTime = 0;

ISR(INT0_vect){
	if(PIND & 1 << 2) {
			IRLib::beginTime = IRLib::custom_micros();
	} else {
		uint32_t endTime = IRLib::custom_micros();
		uint32_t time = endTime - IRLib::beginTime;
		sei();
				
		if(time > highBit - negMargin && time < highBit + posMargin) { //1 voor 400 milli
			IRLib::receiving |= 1 << IRLib::bit;
			IRLib::bit++;
			IRLib::count++;
		} else if (time > lowBit - negMargin && time < lowBit + posMargin) { // 200 voor 5
			IRLib::bit++;
		} else if (time > startBit - negMargin && time < startBit + posMargin) { //start bit 600
			IRLib::bit = 0;
			IRLib::receiving = 0;
			IRLib::count = 0;
		} else if (time > acknowledgeBit - negMargin && time < acknowledgeBit + posMargin) { //acknowledge
			IRLib::status = sendSucces;
		} else if (time > nonAcknowledgeBit - negMargin && time < nonAcknowledgeBit + posMargin) { //non-acknowledge
			IRLib::status = error;
		} else if (time > stopBit - negMargin && time < stopBit + posMargin) { //stop bit 800
			if(IRLib::bit != 9) {
				IRLib::sendAcknowledge(false);
				return;
			}
			if(IRLib::count & 1) {
				IRLib::sendAcknowledge(false);
				return;
			}
			if(Communication::addParameter(IRLib::receiving)) {
				IRLib::sendAcknowledge(true);
			}
		}
	}
}

ISR(TIMER2_OVF_vect) {
	IRLib::timer++;
}

uint32_t IRLib::custom_micros() {
	uint32_t m;
	uint8_t t;
	cli();
	m = IRLib::timer;
	t = TCNT2;
	if ((TIFR2 & _BV(TOV2)) && (t < 255))
		m++;
	sei();
	return ((m << 8) + t) * (64 / 16);
}

void IRLib::begin(int frequency) {
	//setup interrupt on pin 2
	EICRA |= 1 << ISC00; //interrupt on change
	EIMSK |= 1 << INT0; //enable interrupt	
	
	//setup signal
	DDRD = 1 << PORTB6;
	TCCR0A |= 1 << WGM01;
	TCCR0B |= 1 << CS01;
	OCR0A = 2000.0 / frequency / 2.0;
	disableSignal;
}

static void IRLib::custom_delay(uint32_t time) {
	uint32_t start = custom_micros();
	while(custom_micros() - start < time) {
	}
}

static void IRLib::sendPulse(uint16_t time) {
	enableSignal;
	custom_delay(time);
	disableSignal;
	custom_delay(spacer);
}

static bool IRLib::send(uint16_t data) {
	cli();
	uint8_t count = 0;
	sendPulse(startBit);
	for(int i = 0; i < 8; i++){
		if(data & 1 << i){
			sendPulse(highBit);
			count++;
		}else{
			sendPulse(lowBit);
		}
	}
	if(count & 1){
		sendPulse(highBit);
		}else{
		sendPulse(lowBit);
	}
	sendPulse(stopBit);
	sei();
}


static bool IRLib::sendWait(uint16_t data) {
	for(int i = 0; i < 10000000; i++) {
		IRLib::status = sending;
		IRLib::send(data);
		status = waitingForAcknowledge;
		IRLib::waitAcknowledge();
		if(IRLib::status == sendSucces) return true;
	}
	return false;
}

void IRLib::sendAcknowledge(bool succes) {
	 if(succes) {
		 sendPulse(acknowledgeBit);
	 } else {
		 sendPulse(nonAcknowledgeBit);
	 }
}

void IRLib::waitAcknowledge() {
	for(int i = 0; i < 1000; i++) {
		if(IRLib::status != waitingForAcknowledge) {
			return;
		}
		_delay_ms(1);
	}
}
