/*
 * worms.ino
 *
 * Created: 11/28/2018 9:17:16 AM
 * Author: gerja
 */ 

#include "Arduino.h"
#include "Player.h"
#include "Communication.h"

#include <Wire.h>

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <avr/delay.h>

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
Player* player1;
Player* player2;

  int JoyDirection = 0;
  int start = 1;
 uint8_t playerX ;
 uint8_t playerY ;



int main(void) {

	sei();
	player1 = new Player();
	player2 = new Player();
	Communication::begin();
      tft.begin();
      tft.setRotation(1);
       tft.fillScreen(ILI9341_BLACK);
      nunchuck_setpowerpins();
      nunchuck_init();
         tft.fillCircle(playerX, playerY, 4, ILI9341_BLUE);
	Serial.println("starting up");
	
	while(1) {
		game();
	}
}

void game() {
	while(1) {
		//update player nunchuck etc


    nunchuck_get_data();
    nunchuck_print_data();
if(JoyDirection == 0){

}
else if(JoyDirection == 1){
  player1->y++;
  player1->sendLocation();
} else if(JoyDirection == 2){
  player1->y--;
  player1->sendLocation();
} else if(JoyDirection == 3){
  player1->x--;
  player1->sendLocation();
} else if(JoyDirection == 4){
  player1->x++;
  player1->sendLocation();
} 


//    nunchuck_get_data();
//    nunchuck_print_data();
//if(JoyDirection == 0){
//
//                  
//               
//}
//else if(JoyDirection == 1){ //UP
// playerY++;
// 
//
//} else if(JoyDirection == 2){ // DOWN
//   playerY--;
//
//} else if(JoyDirection == 3){ //LEFT
// playerX--;
//} else if(JoyDirection == 4){ //RIGHT
//   playerX++;
//
//} 
//   tft.fillCircle(playerX, playerY, 4, ILI9341_BLUE);
//   Serial.println(playerX);
//
// Serial.println(playerY);
  
		if(Communication::buffer[0] == 255) {
			Communication::clearBuffer(1);
			if(Communication::buffer[0] == 1) {
				Serial.println("other arduino joined");
				Communication::clearBuffer(4);
			}
			if(Communication::buffer[0] == 10) {
//       // player2->clearr(tft); 
//        tft.fillCircle(player2->x, player2->y, 4, ILI9341_BLACK); 
//				player2->moveTo(Communication::buffer[1], Communication::buffer[2]);
// tft.fillCircle(player2->x, player2->y, 4, ILI9341_RED); 

                  
                
				Communication::clearBuffer(3);
        
			}
			//Communication::next();
		}

		_delay_ms(10);
		          
 // tft.fillCircle(playerX, playerY, 4, ILI9341_BLACK);
	}
}





//

// Nunchuck functions

//

static uint8_t nunchuck_buf[6]; // array to store nunchuck data,


// Uses port C (analog in) pins as power & ground for Nunchuck

static void nunchuck_setpowerpins()

{
#define pwrpin PC3
#define gndpin PC2
DDRC |= _BV(pwrpin) | _BV(gndpin);
PORTC &=~ _BV(gndpin);
PORTC |= _BV(pwrpin);
_delay_ms(100);  // wait for things to stabilize
}

// initialize the I2C system, join the I2C bus,
// and tell the nunchuck we're talking to it

void nunchuck_init(){
Wire.begin();  // join i2c bus as master
Wire.beginTransmission(0x52); // transmit to device 0x52
Wire.write(0x40);  // sends memory address
Wire.write(0x00);  // sends sent a zero.
Wire.endTransmission(); // stop transmitting
}


// Send a request for data to the nunchuck
// was "send_zero()"
void nunchuck_send_request(){
Wire.beginTransmission(0x52); // transmit to device 0x52
Wire.write(0x00);  // sends one byte
Wire.endTransmission(); // stop transmitting
}

// Receive data back from the nunchuck,
// returns 1 on successful read. returns 0 on failure
int nunchuck_get_data(){
int cnt=0;
Wire.requestFrom (0x52, 6); // request data from nunchuck
while (Wire.available ()) {
// receive byte as an integer
nunchuck_buf[cnt] = nunchuk_decode_byte(Wire.read());
cnt++;
}

nunchuck_send_request(); // send request for next data payload
// If we recieved the 6 bytes, then go print them
if (cnt >= 5) {
return 1; // success
}
return 0; //failure
}

void nunchuck_print_data(){
static int i=0;
int joy_x_axis = nunchuck_buf[0];
int joy_y_axis = nunchuck_buf[1];

if(joy_y_axis > 200){
   JoyDirection = 1;
}
if(joy_y_axis < 100){
  JoyDirection = 2;
 }
if(joy_x_axis < 100){
  JoyDirection = 3;
}
if(joy_x_axis > 200){
   JoyDirection = 4;
}
if(joy_y_axis > 100 && joy_y_axis < 200 && joy_x_axis > 100 && joy_x_axis < 200){
    JoyDirection = 0;
}

}


// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char nunchuk_decode_byte (char x){
x = (x ^ 0x17) + 0x17;
return x;
}


// returns value of x-axis joystick
int nunchuck_joyx(){
return nunchuck_buf[0];
}

// returns value of y-axis joystick
int nunchuck_joyy(){
return nunchuck_buf[1];
}

 
