/* 
* IRLib.cpp
*
* Created: 27-11-2018 11:02:04
* Author: gerja
*/


#include "IRLib.h"

volatile static uint32_t IRLib::timer = 0;		//overflow count of timer 2
volatile static uint8_t IRLib::count = 0;		//amount of 1 data bits required for parity check
volatile static uint8_t IRLib::receiving = 0;	//byte in which data is being received ins
volatile static uint8_t IRLib::bit = 0;			//current bit that is being received
volatile static uint8_t IRLib::status = 0;		//the status of the ir libary

volatile static uint32_t IRLib::beginTime = 0;	//time when logical signal on pin 2 became true

ISR(INT0_vect){
	if(PIND & 1 << 2) {
		IRLib::beginTime = IRLib::custom_micros();	//record time
	} else {
		uint32_t endTime = IRLib::custom_micros();	//record end time
		uint32_t time = endTime - IRLib::beginTime;	//calculate duration of pulse
		sei();	//enable global interrupt so that other interrupt can happen
				
		if(time > highBit - negMargin && time < highBit + posMargin) { //data/parity 1 bit
			IRLib::receiving |= 1 << IRLib::bit;
			IRLib::bit++;
			IRLib::count++;
		} else if (time > lowBit - negMargin && time < lowBit + posMargin) { //data/parity 0 bit
			IRLib::bit++;
		} else if (time > startBit - negMargin && time < startBit + posMargin) { //start bit
			IRLib::bit = 0;
			IRLib::receiving = 0;
			IRLib::count = 0;
		} else if (time > acknowledgeBit - negMargin && time < acknowledgeBit + posMargin) { //acknowledge bit
			IRLib::status = sendSucces;
		} else if (time > nonAcknowledgeBit - negMargin && time < nonAcknowledgeBit + posMargin) { //non-acknowledge bit
			IRLib::status = error;
		} else if (time > stopBit - negMargin && time < stopBit + posMargin) { //stop bit
			
			//lenght of byte check: data(8) + parity bit = 9
			if(IRLib::bit != 9) {
				IRLib::sendAcknowledge(false); //byte length error, send non-acknowledge
				return;
			}
			
			//parity check: parity has to be even
			if(IRLib::count & 1) {
				IRLib::sendAcknowledge(false);	//purity error, send non-acknowledge
				return;
			}
			
			//try to add parameter to buffer
			if(Communication::addParameter(IRLib::receiving)) {
				IRLib::sendAcknowledge(true); //if add is successful send positive acknowledge 
			}
		}
	}
}

//timer 2 (used for measuring time of a pulse) overflow vector
ISR(TIMER2_OVF_vect) {
	IRLib::timer++;	//add 1 to overflow count
}

//calculates time since startup or roll-over of timer variable
uint32_t IRLib::custom_micros() {
	uint32_t m;
	uint8_t t;
	cli();	//disable global interrupt bacause copy of timer needs to happen fast after timer variabl copy
	m = IRLib::timer;	//copy timer variable
	t = TCNT2;			//copy timer 2 value
	if ((TIFR2 & _BV(TOV2)) && (t < 255))	//check if a interrupt would have happend
		m++;
	sei();
	return ((m << 8) + t) * (64 / 16);
}
//function to begin on a specific frequency
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
//fuction to create a delay
static void IRLib::custom_delay(uint32_t time) {
	uint32_t start = custom_micros();
	while(custom_micros() - start < time) {
	}
}
//creating a pulse
static void IRLib::sendPulse(uint16_t time) {
	enableSignal;
	custom_delay(time);
	disableSignal;
	custom_delay(spacer);
}
//sending a pulse
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

//send an acknowledge and wait for acknowledge
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
//send acknowlegde to other arduino
void IRLib::sendAcknowledge(bool succes) {
	 if(succes) {
		 sendPulse(acknowledgeBit);
	 } else {
		 sendPulse(nonAcknowledgeBit);
	 }
}
//waiting for acknowledge from other arduino
void IRLib::waitAcknowledge() {
	for(int i = 0; i < 1000; i++) {
		if(IRLib::status != waitingForAcknowledge) {
			return;
		}
		_delay_ms(1);
	}
}
