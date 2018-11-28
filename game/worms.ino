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
	Serial.print("debugging");
	Communication::handshake();	
	while(1) {
		if(Communication::parameters >= 1 && Communication::buffer[0] == 1) {
			Communication::clearBuffer();
			Communication::send(2);
			Serial.println("hallo there");
			break;
		}
		if(Communication::parameters >= 1 && Communication::buffer[0] == 2) {
			Communication::clearBuffer();
			Serial.println("hallo there to");
			break;
		}
	}
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
		player1->sendLocation();
		
		//check for updates from other arduino
		
		if(Communication::parameters >= 3 && Communication::buffer[0] == 10) {
			player2->moveTo(1,1);
			Communication::clearBuffer();
		}
		if(Communication::parameters >= 1 && Communication::buffer[0] == 1) {
			Communication::clearBuffer();
			Communication::send(2);
			Serial.println("hallo there");
		}
		//Serial.println(Communication::parameters);
		
		//draw changes from other arduino
	}
}