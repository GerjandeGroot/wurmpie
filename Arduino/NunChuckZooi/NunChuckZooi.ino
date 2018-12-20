
#include <Wire.h>

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <avr/delay.h>

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
  

int JoyDirection = 0;
int start = 1;

int main(void){
      init();
     Serial.begin(9600);
      nunchuck_setpowerpins();
      nunchuck_init();
   
      tft.begin();
      tft.setRotation(1);
      testText();
      _delay_ms(1000); 
      tft.setCursor(100, 100);
      tft.fillScreen(ILI9341_BLACK);
      nunchuck_get_data();
      nunchuck_print_data();
      moveDot(); 

  
} 

unsigned long moveDot() {
  unsigned long start;

int x = 10;
int y = 20;
  int myPointUp = 0;
  int myPointLeft= 0;
  int myPointRight= 0;
  int myPointDown = 0;

 while(start == 1){
 

          while(JoyDirection == 0){
            tft.fillCircle(x, y, 4, ILI9341_RED);
            nunchuck_get_data();
            nunchuck_print_data();
          }
       
          while(JoyDirection == 1){

                  for(int i = myPointUp; i <36; i++){
                  tft.fillCircle(x, y, 4, ILI9341_RED);
                  _delay_ms(50);  
                  tft.fillCircle(x, y, 4, ILI9341_BLACK);
                  y= y - 6;
                  
                  sendCoorData(x, y);
                  
                  nunchuck_get_data();
                  nunchuck_print_data();
                    if(i == 35){
                       y= 240;
                       tft.fillCircle(x, y, 4, ILI9341_RED);
                       myPointUp = 0;
                    }
                    if(JoyDirection == 0){
                    if(i == 35){
                        myPointUp =  i;
                        i = 35;
                      } else {
                      myPointUp =  i +1;   
                      i = 35;
                      }
                    }
               }
              while(JoyDirection == 0){
                tft.fillCircle(x, y, 4, ILI9341_RED);
                nunchuck_get_data();
                nunchuck_print_data();
              }
          }
          
          while(JoyDirection == 2){

                  for(int i = myPointDown ; i < 41; i++){
                  tft.fillCircle(x, y, 4, ILI9341_RED);
                  _delay_ms(50); 
                  tft.fillCircle(x, y, 4, ILI9341_BLACK);
                  y = y + 6;

                  sendCoorData(x, y);
                  
                  nunchuck_get_data();
                  nunchuck_print_data();
                    if(i == 40){
                       y = 20;
                       tft.fillCircle(x, y, 4, ILI9341_RED);
                       myPointDown = 0;
                    }
                    if(JoyDirection == 0){
                    if(i == 40){
                        myPointDown =  i;
                        i = 40;
                      } else {
                      myPointDown =  i +1;   
                      i = 40;
                      }
                    }
               }
              while(JoyDirection == 0){
                tft.fillCircle(x, y, 4, ILI9341_RED);
                nunchuck_get_data();
                nunchuck_print_data();
              }
          }

           while(JoyDirection == 3){

                  for(int i = myPointLeft ; i < 51; i++){
                  tft.fillCircle(x, y, 4, ILI9341_RED);
                  _delay_ms(50); 
                  tft.fillCircle(x, y, 4, ILI9341_BLACK);
                  x = x - 6;
                  
                  sendCoorData(x, y);
                  
                  nunchuck_get_data();
                  nunchuck_print_data();
                    if(i == 50){
                       x = 310;
                       tft.fillCircle(x, y, 4, ILI9341_RED);
                       myPointLeft = 0;
                    }
                    if(JoyDirection == 0){
                    if(i == 50){
                        myPointLeft =  i;
                        i = 50;
                      } else {
                      myPointLeft =  i +1; 
                      i = 50;
                      }
                    }
             }
              while(JoyDirection == 0){
                tft.fillCircle(x, y, 4, ILI9341_RED);
                nunchuck_get_data();
                nunchuck_print_data();
              }
          }

            while(JoyDirection == 4){

                  for(int i = myPointRight ; i < 51; i++){
                  tft.fillCircle(x, y, 4, ILI9341_RED);
                  _delay_ms(50); 
                  tft.fillCircle(x, y, 4, ILI9341_BLACK);
                  
                  x = x + 6;

                  sendCoorData(x, y);
             
                  nunchuck_get_data();
                  nunchuck_print_data();
                    if(i == 50){
                         x = 10;
                         tft.fillCircle(x, y, 4, ILI9341_RED);
                         myPointRight = 0;
                    }
                    if(JoyDirection == 0){
                      if(i == 50){
                        myPointRight =  i;
                        i = 50;
                      } else {
                      myPointRight =  i +1;  
                      i = 50;
                      }
                    }
                  }
              while(JoyDirection == 0){
                tft.fillCircle(x, y, 4, ILI9341_RED);
                nunchuck_get_data();
                nunchuck_print_data();
              }
          }
      nunchuck_get_data();
      nunchuck_print_data();
    }
      return 0;
}

void sendCoorData(int x, int y){
  uint16_t newX = x /4;
  uint16_t newY = y /4;
   Serial.println(newX);
   Serial.println(newY);
   Serial.println(10);
   Serial.println(255);
  return 0;
}  

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(123456);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("WIBOOOOO");
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("is testing around");
  tft.setTextSize(1);
  tft.println("Getting my own creation.......");
}

//

// Nunchuck functions

//

static uint8_t nunchuck_buf[6]; // array to store nunchuck data,
static void nunchuck_setpowerpins(){
#define pwrpin PC3
#define gndpin PC2
DDRC |= _BV(pwrpin) | _BV(gndpin);
PORTC &=~ _BV(gndpin);
PORTC |= _BV(pwrpin);
delay(100); // wait for things to stabilize
}

void nunchuck_init(){
Wire.begin();  // join i2c bus as master
Wire.beginTransmission(0x52); // transmit to device 0x52
Wire.write(0x40);  // sends memory address
Wire.write(0x00);  // sends sent a zero.
Wire.endTransmission(); // stop transmitting
}

void nunchuck_send_request(){
Wire.beginTransmission(0x52); // transmit to device 0x52
Wire.write(0x00);  // sends one byte
Wire.endTransmission(); // stop transmitting
}

int nunchuck_get_data(){
int cnt = 0;
Wire.requestFrom (0x52, 6); 

while (Wire.available ()){
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
static int i = 0;
int joy_x_axis = nunchuck_buf[0];
int joy_y_axis = nunchuck_buf[1];
int accel_x_axis = nunchuck_buf[2]; // * 2 * 2;
int accel_y_axis = nunchuck_buf[3]; // * 2 * 2;
int accel_z_axis = nunchuck_buf[4]; // * 2 * 2;
int z_button = 0;
int c_button = 0;

if ((nunchuck_buf[5] >> 0) & 1)
z_button = 1;
if ((nunchuck_buf[5] >> 1) & 1)
c_button = 1;
if ((nunchuck_buf[5] >> 2) & 1)
accel_x_axis += 2;
if ((nunchuck_buf[5] >> 3) & 1)
accel_x_axis += 1;
if ((nunchuck_buf[5] >> 4) & 1)
accel_y_axis += 2;
if ((nunchuck_buf[5] >> 5) & 1)
accel_y_axis += 1;
if ((nunchuck_buf[5] >> 6) & 1)
accel_z_axis += 2;
if ((nunchuck_buf[5] >> 7) & 1)
accel_z_axis += 1;

if(joy_y_axis > 200 && joy_x_axis < 200){
  JoyDirection = 1;
}
if(joy_y_axis < 100 && joy_y_axis < 100){
  JoyDirection = 2;
//    sender = '2';
//    Serial.write(sender);
}
if(joy_x_axis < 100 && joy_y_axis > 100){
  JoyDirection = 3;
}
if(joy_x_axis > 200 && joy_y_axis < 200){
  JoyDirection = 4;
}

if(joy_y_axis > 100 && joy_y_axis < 200 && joy_x_axis > 100 && joy_x_axis < 200){
  JoyDirection = 0;
}

if(c_button == 1){
  cButton = 1;
}
if(c_button == 0){
  cButton = 0;
}
}


char nunchuk_decode_byte (char x){
x = (x ^ 0x17) + 0x17;
return x;
}

// returns zbutton state: 1=pressed, 0=notpressed
int nunchuck_zbutton(){
return ((nunchuck_buf[5] >> 0) & 1) ? 0 : 1; // voodoo
}
// returns zbutton state: 1=pressed, 0=notpressed
int nunchuck_cbutton(){
return ((nunchuck_buf[5] >> 1) & 1) ? 0 : 1; // voodoo
}
// returns value of x-axis joystick
int nunchuck_joyx(){
return nunchuck_buf[0];
}
// returns value of y-axis joystick
int nunchuck_joyy(){
return nunchuck_buf[1];
}
// returns value of x-axis accelerometer
int nunchuck_accelx(){
return nunchuck_buf[2]; // FIXME: this leaves out 2-bits of the data
}
// returns value of y-axis accelerometer
int nunchuck_accely(){
return nunchuck_buf[3]; // FIXME: this leaves out 2-bits of the data
}
// returns value of z-axis accelerometer
int nunchuck_accelz(){
return nunchuck_buf[4]; // FIXME: this leaves out 2-bits of the data
}
 
