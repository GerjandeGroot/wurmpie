#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
Adafruit_DCMotor *myOtherOtherMotor = AFMS.getMotor(3);
const int Sensor_Trein = A0; // Sensor output voltage
const int Sensor_Kraan = A1;
boolean go = false;
boolean setter = false;
boolean load = false;
int changer = 0;
String huidig;
int commando = 0;
boolean start = false;

//trein
int afstand_trein    = 0;                                           // huidige locatie
int detectie_trein_1 = 0;                                           // op ref sensor
int detectie_trein_2 = 0;                                           // afstand al verhoogd
int eindpunt_trein1  = 0;                                           // gekozen eindpunt
int klaar_trein      = 0;                                           // pakketje opgehaald
//kraan
int afstand_kraan    = 0;                                           // huidige locatie
int detectie_kraan_1 = 0;                                           // op ref sensor
int detectie_kraan_2 = 0;                                           // afstand al verhoogd
int eindpunt_kraan1  = 0;                                           // gekozen eindpunt
int klaar_kraan      = 0;



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pinMode(Sensor_Trein, INPUT);
  pinMode(Sensor_Kraan, INPUT);
  AFMS.begin();  // create with the default frequency 1.6KHz


  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(155);
  myMotor->run(FORWARD);
  myMotor->run(BACKWARD);
  myMotor->run(RELEASE);
  myOtherMotor->setSpeed(255);
  myOtherMotor->run(FORWARD);
  myOtherMotor->run(BACKWARD);
  myOtherMotor->run(RELEASE);
  myOtherOtherMotor->setSpeed(255);
  myOtherOtherMotor->run(FORWARD);
  myOtherOtherMotor->run(BACKWARD);
  myOtherOtherMotor->run(RELEASE);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);



  while (!Serial);
}

void loop() {

  if (Serial.available()) {
    char state = (char) Serial.read();
    if ( state == 'A') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 1;
      go = true;
      setter = true;
      huidig = "A";
      klaar_trein = 1;
    } else if (state == 'B') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
      huidig = "B";
      klaar_trein      = 1;
    } else if (state == 'C') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
      huidig = "C";
      klaar_trein = 1;
    } else if (state == 'D') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
      huidig = "D";
      klaar_trein = 1;
    } else if (state == 'E') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
      klaar_trein = 1;
      huidig = "E";
    } else if (state == 'F') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 1;
      go = true;
      setter = true;
      huidig = "F";
      klaar_trein = 1;
    } else if (state == 'G') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
      huidig = "G";
      klaar_trein = 1;
    } else if (state == 'H') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
      huidig = "H";
      klaar_trein = 1;
    } else if (state == 'I') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
      huidig = "I";
      klaar_trein = 1;
    } else if (state == 'J') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
      huidig = "J";
      klaar_trein = 1;
    } else if (state == 'K') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 1;
      go = true;
      setter = true;
      huidig = "K";
      klaar_trein = 1;
    } else if (state == 'L') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
      huidig = "L";
      klaar_trein = 1;
    } else if (state == 'M') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
      huidig = "M";
      klaar_trein = 1;
    } else if (state == 'N') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
      huidig = "N";
      klaar_trein = 1;
    } else if (state == 'O') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
      huidig = "O";
      klaar_trein = 1;
    } else if (state == 'P') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 1;
      go = true;
      setter = true;
      huidig = "P";
      klaar_trein = 1;
    } else if (state == 'Q') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
      huidig = "Q";
      klaar_trein = 1;
    } else if (state == 'R') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
      huidig = "R";
      klaar_trein = 1;
    } else if (state == 'S') {
      eindpunt_kraan1 = 5;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
      huidig = "S";
      klaar_trein = 1;
    } else if (state == 'T') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
      huidig = "T";
      klaar_trein = 1;
    } else if (state == 'U') {
      eindpunt_trein1 = 6;
      eindpunt_kraan1 = 1;
      go = true;
      setter = true;
      huidig = "U";
      klaar_trein = 1;
    } else if (state == 'V') {
      eindpunt_trein1 = 6;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
      huidig = "V";
      klaar_trein = 1;
    } else if (state == 'W') {
      eindpunt_trein1 = 6;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
      huidig = "W";
      klaar_trein = 1;
    } else if (state == 'X') {
      eindpunt_trein1 = 6;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
      huidig = "X";
      klaar_trein = 1;
    } else if (state == 'Y') {
      eindpunt_trein1 = 6;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
      huidig = "Y";
      klaar_trein = 1;
    } else if (state == '0') {

      go = true;
      setter = true;
      start = true;
      huidig = "0";
    } else if (state == '1') {
      klaar_kraan = 4;
      go = true;
      setter = false;
      huidig = "1";
    } else if (state == '2') {
      klaar_trein = 4;
      go = true;
      setter = false;
    } else if (state == '3') {
      klaar_trein = 1;
      eindpunt_trein1 = 1;
      eindpunt_kraan1 = 4;
      go = true;
      setter = false;
      load = true;
      huidig = "Z";
    }
  }
  // Read in the ADC and convert it to a voltage:
  int ref_sensor_trein  = analogRead(Sensor_Trein);
  int ref_sensor_kraan  = analogRead(Sensor_Kraan);


  //vooruit trein
  if (go == true) {
    if (start == true) {
      digitalWrite(7, HIGH);
      commando++;
      Serial.println(commando);
      Serial.println(huidig);
      delay(1000);
      digitalWrite(7, LOW);
      klaar_trein = 0;
      setter = false;
      go = false;
      start = false;
    }
    //    if (eindpunt_trein1 >= afstand_trein && klaar_trein == 0) {
    //      if (ref_sensor_trein  < 200 && detectie_trein_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
    //        detectie_trein_1++;
    //      }
    //      if (detectie_trein_1 == 1 && detectie_trein_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
    //        afstand_trein ++;
    //        detectie_trein_2++;
    //      }
    //      if (ref_sensor_trein  > 200 && detectie_trein_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
    //        detectie_trein_1 = 0;
    //        detectie_trein_2 = 0;
    //      }
    //
    //
    //      if (eindpunt_trein1 == afstand_trein) {
    //        myOtherMotor->run(RELEASE);                                     // stoppen bij eindpunt
    //        klaar_trein = 1;
    //      }
    //      else {
    //        myOtherMotor->run(BACKWARD);                                    // heen rijden
    //      }
    //    }
    //Omhoog kraan
    if (eindpunt_kraan1 >= afstand_kraan && klaar_trein == 1) {
      if (ref_sensor_kraan > 100 && detectie_kraan_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
        detectie_kraan_1++;
      }
      if (detectie_kraan_1 == 1 && detectie_kraan_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
        afstand_kraan ++;
        detectie_kraan_2++;
      }
      if (ref_sensor_kraan < 100 && detectie_kraan_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
        detectie_kraan_1 = 0;
        detectie_kraan_2 = 0;
      }
      if (eindpunt_kraan1 == afstand_kraan) {
        myMotor->run(RELEASE);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        if (setter == true) {
          digitalWrite(2, HIGH);
          myOtherOtherMotor->run(BACKWARD);
          delay(700);
          myOtherOtherMotor->run(RELEASE);
          delay(500);
          myMotor->run(FORWARD);
          delay(600);
          myMotor->run(RELEASE);
          delay(250);
          myOtherOtherMotor->run(FORWARD);
          delay(700);
          myOtherOtherMotor->run(RELEASE);
          delay(500);
          myMotor->run(BACKWARD);
          delay(300);
          myMotor->run(RELEASE);
          delay(500);
          setter = 0;
          delay(100);

          commando++;
          Serial.println(commando);
          Serial.println(huidig);
          klaar_trein = 0;
          setter = false;
          go = false;

        } else if (load == true) {
          digitalWrite(3, HIGH);
          myOtherOtherMotor->run(BACKWARD);
          delay(900);
          myOtherOtherMotor->run(RELEASE);
          delay(500);
          myMotor->run(BACKWARD);
          delay(2000);
          myMotor->run(RELEASE);
          delay(250);
          myOtherOtherMotor->run(FORWARD);
          delay(250);
          myOtherOtherMotor->run(RELEASE);
          delay(1000);
          myOtherOtherMotor->run(FORWARD);
          delay(250);
          myOtherOtherMotor->run(RELEASE);
          delay(1000);
          myOtherOtherMotor->run(FORWARD);
          delay(350);
          myOtherOtherMotor->run(RELEASE);
          delay(1000);
          myMotor->run(BACKWARD);
          delay(3000);
          myMotor->run(RELEASE);
          delay(250);
          commando++;
          digitalWrite(3, HIGH);
          Serial.println(commando);
          Serial.println(huidig);
          delay(1000);
          klaar_trein = 0;
          eindpunt_trein1 = 0;
          afstand_trein = 0;
          afstand_kraan = 0;
          load = false;
          go = false;


        }
      }
      else {
        myMotor->run(FORWARD);  // omhoog                                      // omhoog
        digitalWrite(4, HIGH);
      }

    }

    //  achteruit trein
    //    else if (eindpunt_trein1 <= afstand_trein &&  klaar_trein == 0) {
    //      if (ref_sensor_trein < 600 && detectie_trein_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
    //        detectie_trein_1++;
    //      }
    //      if (detectie_trein_1 == 1 && detectie_trein_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
    //        afstand_trein --;
    //        detectie_trein_2++;
    //      }
    //      if (ref_sensor_trein > 600 && detectie_trein_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
    //        detectie_trein_1 = 0;
    //        detectie_trein_2 = 0;
    //      }
    //      if (afstand_trein == eindpunt_trein1) {
    //        myOtherMotor->run(RELEASE);
    //        klaar_trein = 1;
    //      }
    //      else {
    //        myOtherMotor->run(FORWARD);
    //      }
    //    }
    //  }

    //Omlaag kraan
    if (eindpunt_kraan1 <= afstand_kraan && klaar_trein == 1) {
      if (ref_sensor_kraan > 100 && detectie_kraan_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
        detectie_kraan_1++;
      }
      if (detectie_kraan_1 == 1 && detectie_kraan_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
        afstand_kraan --;
        detectie_kraan_2++;
      }
      if (ref_sensor_kraan < 100 && detectie_kraan_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
        detectie_kraan_1 = 0;
        detectie_kraan_2 = 0;
      }
      if (eindpunt_kraan1 == afstand_kraan) {
        myMotor->run(RELEASE);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        if (setter == true) {
          digitalWrite(2, HIGH);
          myOtherOtherMotor->run(BACKWARD);
          delay(700);
          myOtherOtherMotor->run(RELEASE);
          delay(500);
          myMotor->run(FORWARD);
          delay(600);
          myMotor->run(RELEASE);
          delay(250);
          myOtherOtherMotor->run(FORWARD);
          delay(700);
          myOtherOtherMotor->run(RELEASE);
          delay(500);
          myMotor->run(BACKWARD);
          delay(300);
          myMotor->run(RELEASE);
          delay(500);
          setter = 0;
          delay(100);

          commando++;
          Serial.println(commando);
          Serial.println(huidig);
          klaar_trein = 0;
          setter = false;
          go = false;

        } else if (load == true) {
          digitalWrite(3, HIGH);
          myOtherOtherMotor->run(BACKWARD);
          delay(900);
          myOtherOtherMotor->run(RELEASE);
          delay(500);
          myMotor->run(BACKWARD);
          delay(2000);
          myMotor->run(RELEASE);
          delay(250);
          myOtherOtherMotor->run(FORWARD);
          delay(250);
          myOtherOtherMotor->run(RELEASE);
          delay(1000);
          myOtherOtherMotor->run(FORWARD);
          delay(250);
          myOtherOtherMotor->run(RELEASE);
          delay(1000);
          myOtherOtherMotor->run(FORWARD);
          delay(350);
          myOtherOtherMotor->run(RELEASE);
          delay(1000);
          myMotor->run(BACKWARD);
          delay(3000);
          myMotor->run(RELEASE);
          delay(250);
          commando++;

          Serial.println(commando);
          Serial.println(huidig);

          klaar_trein = 0;
          eindpunt_trein1 = 0;
          afstand_trein = 0;
          afstand_kraan = 0;
          load = false;
          go = false;

        }
      }
      else {
        myMotor->run(BACKWARD);  // omhoog                                      // omhoog
        digitalWrite(4, HIGH);
      }

    }

    // achteruit trein terug naar start
    if (klaar_trein == 4 ) {
      if (ref_sensor_trein < 600 && detectie_trein_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
        detectie_trein_1++;
      }
      if (detectie_trein_1 == 1 && detectie_trein_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
        afstand_trein --;
        detectie_trein_2++;
      }
      if (ref_sensor_trein > 600 && detectie_trein_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
        detectie_trein_1 = 0;
        detectie_trein_2 = 0;
      }
      if (afstand_trein == 1) {
        myOtherMotor->run(RELEASE);
        go = false;
        klaar_trein = 0;
        eindpunt_trein1 = 0;

      }
      else {
        myOtherMotor->run(FORWARD);

      }
    }


    if (klaar_kraan == 4 ) {
      if (eindpunt_kraan1 <= afstand_kraan && klaar_kraan == 4) {
        if (ref_sensor_kraan > 100 && detectie_kraan_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
          detectie_kraan_1++;
        }
        if (detectie_kraan_1 == 1 && detectie_kraan_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
          afstand_kraan --;
          detectie_kraan_2++;
        }
        if (ref_sensor_kraan < 100 && detectie_kraan_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
          detectie_kraan_1 = 0;
          detectie_kraan_2 = 0;
        }
        if (afstand_trein == 4) {
          myMotor->run(RELEASE);
          go = false;
          klaar_kraan = 0;
          eindpunt_kraan1 = 0;
          commando++;
          Serial.println(commando);
          Serial.println(huidig);

        }


      } else if (eindpunt_kraan1 >= afstand_kraan && klaar_kraan == 4) {
        if (eindpunt_kraan1 <= afstand_kraan && klaar_kraan == 4) {
          if (ref_sensor_kraan > 100 && detectie_kraan_1 == 0) {                    // begin wit vlak && eerste keer wit detecteren
            detectie_kraan_1++;
          }
          if (detectie_kraan_1 == 1 && detectie_kraan_2 == 0) {                   // op het witte vlak afstand ÉÉN keer verhogen
            afstand_kraan --;
            detectie_kraan_2++;
          }
          if (ref_sensor_kraan < 100 && detectie_kraan_1 == 1) {                    // eind wit vlak gedetecteerd & vlaggetjes terug op 0
            detectie_kraan_1 = 0;
            detectie_kraan_2 = 0;
          }
          if (afstand_trein == 4) {
            myMotor->run(RELEASE);
            go = false;
            klaar_kraan = 0;
            eindpunt_kraan1 = 0;

          }
          else {
            myMotor->run(FORWARD);

          }
        }
      }
    }
  }
}








