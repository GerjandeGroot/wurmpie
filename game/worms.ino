/*
 * worms.ino
 *
 * Created: 11/28/2018 9:17:16 AM
 * Author: gerja
 */ 

#include "Arduino.h"
#include "Player.h"
#include "Communication.h"

Player* player1;
Player* player2;

main() {
	sei();
	player1 = new Player();
	player2 = new Player();
	Communication::begin();
	Serial.println("starting up");
	
	while(1) {
		game();
	}
}

void game() {
	while(1) {
		//update player nunchuck etc
		player1->x++;
		player1->y++;
		
		//send actions to other arduino
		//Serial.println("sending location");
		//player1->sendLocation();
		
		//check for updates from other arduino
		//Serial.println("------------");
		//Serial.println(Communication::buffer[0]);
		//Serial.println(Communication::buffer[1]);
		//Serial.println(Communication::buffer[2]);
		if(Communication::buffer[0] == 255) {
			Communication::clearBuffer(1);
			if(Communication::buffer[0] == 1) {
				Serial.println("other arduino joined");
				Communication::clearBuffer(4);
			}
			if(Communication::buffer[0] == 10) {
				player2->moveTo(1,1);
				Communication::clearBuffer(3);
			}
			//Communication::next();
		}
		_delay_ms(10);
		//draw changes from other arduino
	}
}