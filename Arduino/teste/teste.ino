



const int Sensor_Kraan = A1;

//trein

//kraan
int afstand_kraan    = 0;                                           // huidige locatie
int detectie_kraan_1 = 0;                                           // op ref sensor
int detectie_kraan_2 = 0;                                           // afstand al verhoogd
int eindpunt_kraan1  = 0;                                           // gekozen eindpunt
int klaar_kraan      = 0;
boolean go = false;
boolean setter = false;
int changer = 0;



void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 while (!Serial);
}
void loop() {


    char state = (char) Serial.read();
    if ( state == 'A') {
      eindpunt_trein1 = 1;
      eindpunt_kraan1 = 1;
      go = true;
      setter = true;
    } else if (state == 'B') {
      eindpunt_trein1 = 1;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
    } else if (state == 'C') {
      eindpunt_trein1 = 1;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
    } else if (state == 'D') {
      eindpunt_trein1 = 1;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
    } else if (state == 'E') {
      eindpunt_trein1 = 1;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
    } else if (state == 'F') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 1;
      go = true;
    } else if (state == 'G') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 2;
      go = true;
      setter = false;
    } else if (state == 'H') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 3;
      go = true;
      setter = false;
    } else if (state == 'I') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 4;
      go = true;
      setter = false;
    } else if (state == 'J') {
      eindpunt_trein1 = 2;
      eindpunt_kraan1 = 5;
      go = true;
      setter = false;
    } else if (state == 'K') {
      eindpunt_kraan1 = 3;
      eindpunt_kraan1 = 1;
      go = true;
      setter = false;
    } else if (state == 'L') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 2;
      go = true;
      setter = true;
    } else if (state == 'M') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 3;
      go = true;
      setter = true;
    } else if (state == 'N') {
      eindpunt_kraan1 = 3;
      eindpunt_kraan1 = 4;
      go = true;
      setter = true;
    } else if (state == 'O') {
      eindpunt_trein1 = 3;
      eindpunt_kraan1 = 5;
      go = true;
      setter = true;
    } else if (state == 'P') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 1;
      go = true;
      setter = false;
    } else if (state == 'Q') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 2;
      go = true;
      setter = false;
    } else if (state == 'R') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 3;
      go = true;
      setter = false;
    } else if (state == 'S') {
      eindpunt_kraan1 = 4;
      eindpunt_kraan1 = 4;
      go = true;
      setter = false;
    } else if (state == 'T') {
      eindpunt_trein1 = 4;
      eindpunt_kraan1 = 5;
      go = true;
      setter = false;
    } else if (state == 'U') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 1;
      go = true;
      setter = false;
    } else if (state == 'V') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 2;
      go = true;
      setter = false;
    } else if (state == 'W') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 3;
      go = true;
      setter = false;
    } else if (state == 'X') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 4;
      go = true;
      setter = false;
    } else if (state == 'Y') {
      eindpunt_trein1 = 5;
      eindpunt_kraan1 = 5;
      go = true;
      setter = false;
    } else if (state == '0') {
      klaar_kraan = 4;
      go = true;
      setter = false;
    } else if (state == '1') {
      klaar_kraan = 4;
      go = true;
      setter = false;
    } else if (state == '2') {
      klaar_trein = 4;
      go = true;
      setter = false;
    }

if(go == true){
    if(eindpunt_trein1 == 1 && eindpunt_kraan1 == 1){
      Serial.println("check1");
      go = false;
    } else if (eindpunt_trein1 == 1 && eindpunt_kraan1 == 2){
      Serial.println("check2");
      go = false;
    } else if (eindpunt_trein1 == 1 && eindpunt_kraan1 == 3){
      Serial.println("check3");
       go = false;
    } else if (eindpunt_trein1 == 1 && eindpunt_kraan1 == 4){
      Serial.println("check4");
       go = false;
    } else if (eindpunt_trein1 == 1 && eindpunt_kraan1 == 5){
      Serial.println("check5");
       go = false;
    }
}
  }


  
