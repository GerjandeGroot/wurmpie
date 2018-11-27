/* 
* IRLib.cpp
*
* Created: 27-11-2018 11:02:04
* Author: gerja
*/


#include "IRLib.h"

volatile static uint8_t IRLib::received = 0;
volatile static long IRLib::signalStart = 0;
volatile static uint8_t IRLib::count = 0;
volatile static uint8_t IRLib::receiving = 0;
volatile static uint8_t IRLib::bit = 0;
volatile static bool IRLib::_available = false;


ISR(INT0_vect){
	if(!(PIND & 1 << 2)) {
			IRLib::signalStart = micros();
	} else {
		long time = micros() - IRLib::signalStart;
		if(time > 20000 && time < 35000) { //1 voor 400 milli
			IRLib::receiving |= 1 << IRLib::bit;
			IRLib::bit++;
			IRLib::count++;
			} else if (time > 10000 && time < 20000) { // 200 voor 5
			IRLib::bit++;
			} else if (time > 35000 && time < 45000) { //start bit 600
			IRLib::bit = 0;
			IRLib::receiving = 0;
			IRLib::count = 0;
			} else if (time > 45000 && time < 60000) { //stop bit 800
			IRLib::_available = true;
			IRLib::received = IRLib::receiving;
			IRLib::receiving == 0;
			if(IRLib::bit != 9) {
				Serial.println("lenght");
			}
			if(IRLib::count & 1) {
				Serial.println("parity");
			}
			} else {
			Serial.print("error ");
			Serial.println(time);
		}
	}
}

void IRLib::begin(int frequency) {
	//setup interrupt on pin 2
	EICRA |= 1 << ISC00; //interrupt on change
	EIMSK |= 1 << INT0; //enable interrupt
	
	//setup micros()
	//TCCR0A |= 1 << WGM01 | 1 << WGM00;
	//TCCR0B |= 1 << CS01 || 1 << CS00;
	//TIMSK0 |= 1 << TOIE0;
	
	
	//setup signal
	TCCR0A |= 1 << WGM01;
	TCCR0B |= 1 << CS01;
	Serial.println(2000.0 / frequency / 2.0);
	OCR0A = 2000.0 / frequency / 2.0;
	DDRD = 1 << PORTB6;
}

static IRLib::read() {
	IRLib::_available = false;
	return IRLib::received;
}

bool IRLib::available() {
	return IRLib::_available;
}

