/*
* Main.cpp
*
* Created: 6-12-2018 13:31:51
* Author: gerja
*/


#include "Main.h"

static Adafruit_ILI9341 Main::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
static Map Main::map = Map();
static Player Main::player1 = Player(ILI9341_BLUE);
static Player Main::player2 = Player(ILI9341_RED);
static uint8_t Main::beurt = 0;

static Button Main::menuWeapon = Button(220, 0, 100, 16, "Default", ILI9341_BLUE);

//default constructor
Main::Main()
{
	sei();					//enable interrupts
	Communication::USART_Init();
	DDRD |= 1 << PIND3;		//set pin 3 as output (brightness)
	
	//setup adc
	ADMUX |= 1 << ADLAR;	//high low position selection
	ADMUX |= 1 << REFS0;	//reference voltage selection
	ADCSRA |= 0b111;		//prescaler on 128
	ADCSRA |= (1<<ADEN);	//enable adc
	
	//setup timer 1
	//update brightness & multiplexing
	TCCR1B |= 1 << CS11;	//prescaler on 8
	TIMSK1 |= 1 << TOIE1;	//enable overflow interrupt
	
	//setup timer 2
	//brightness pwm & micros
	TCCR2A |= 1 << COM2A1;	//set non inverting 
	TCCR2A |= 1 << WGM20;	//set mode fast pwm
	TCCR2A |= 1 << WGM21;	//set mode fast pwm
	TCCR2B |= 1 << CS22;	//prescaler on 64
	TIMSK2 |= 1 << TOIE2;	//enable overflow interrupt
	
	Communication::begin();
	
	Button::begin();
	
	while(true) {
		menu();
		update();
	}
	
} //Main

//default destructor
Main::~Main()
{
} //~Main
//function of the game (is explained in technisch ontwerp)
void Main::update() {
	Nunchuck nunchuck;
	draw();
	if(beurt == 1)
		player1.fuelBar();
		
	while(player1.moveToDirection(3, false) | player2.moveToDirection(3, false)){
		_delay_ms(80);
		if(player1.health == 0) {
			Menu().endPanel("YOU LOSE");
			return;
		}
		if(player2.health == 0) {
			Menu().endPanel("YOU WIN");
			return;
		}
	}
	while(1){
		nunchuck.update();
		if(beurt == 1){
			player2.draw();
			if(nunchuck.c || !(player1.fuel > 0)){
				beurt = 2;
			} else if(nunchuck.x > 100 && nunchuck.x < 200 && nunchuck.y > 100 && nunchuck.y < 200){
				player1.moveToDirection(3);
			} else {
				bool moved = false;
				if(nunchuck.x > 150){					//rechts
					moved = player1.moveToDirection(2);
				}
				if(nunchuck.x < 110){					//links
					moved = player1.moveToDirection(4);
				}
				if(nunchuck.y < 110){					//beneden
					moved = player1.moveToDirection(3);
				}
				if(nunchuck.y > 170){					//jetpack
					moved = player1.moveToDirection(1);
				}else{
					moved = player1.moveToDirection(5);
				}
				if(moved) {
					player2.draw();					
				}
				player1.fuel--;

				player1.updateFuelBar();

			}
		} else if (beurt == 2) {
			if(!player1.moveToDirection(3))
			beurt = 3;
			menuWeapon.draw();
		} else if (beurt == 3) {
			Button::update();
			if(menuWeapon.clicked()) {
				Menu().weaponSelectionPanel(&player1);
				draw();
			}
			player1.aimDx = (nunchuck.x-133)/-4;
			player1.aimDy = (nunchuck.y-137)/4;
			player1.clear();
			player1.draw();
			player1.sendAim();
			player2.draw();
			if(nunchuck.z) {
				Communication::send(12);
				Communication::endCommand();
				player1.shoot();
				beurt = 4;
			}
		} else if (beurt == 4) {
			if(!player1.moveToDirection(3) && !map.updateMap()) {
				beurt = 5;
				player1.fuel = 10;
				Communication::send(4);
				Communication::endCommand();
				drawTurn(F("enemy turn"));
			}
		} else if (beurt == 5) {
			map.updateMap();
		}	
		
		map.updateMap();
		parseData();
		
		if(player1.health == 0) {
			Menu().endPanel("YOU LOSE");
			return;
		}
		if(player2.health == 0) {
			Menu().endPanel("YOU WIN");
			return;
		}
	}
}
//function which reads incoming commands and linked parameters
void Main::parseData() {
	if(Communication::buffer[0] == 255) {
		Communication::removeParameter();
		if(Communication::buffer[0] == 10) {
			player2.moveTo(Communication::buffer[1], Communication::buffer[2], false);
			player1.draw();
			Communication::clearBuffer(3);
			Communication::next();
		}
		if(Communication::buffer[0] == 11) {
			player2.clear();
			player2.aimDx = Communication::buffer[1];
			player2.aimDy = Communication::buffer[2];
			player2.draw();
			player1.draw();
			Communication::clearBuffer(3);
			Communication::next();
		}
		if(Communication::buffer[0] == 12) {
			Communication::next();
			player2.shoot();
			Communication::clearBuffer(1);
		}
		if(Communication::buffer[0] == 4) {
			player1.addWeapon();
			player2.weapon[0] = 1;
			beurt = 1;
			Communication::clearBuffer(1);
			Communication::next();
			drawTurn(F("your turn"));
			player1.fuelBar();
		}
		if(Communication::buffer[0] == 13) {
			player2.weapon[0] = Communication::buffer[1];
			Communication::clearBuffer(2);
			Communication::next();
		}
	}
}
//starts menu
void Main::menu() {
	Menu menu = Menu();
	menu.setPanel(1);
}

//function to start the game in slave mode
void Main::beginSlave() {
	tft.fillScreen(ILI9341_BLUE);
	player1 = Player(ILI9341_BLUE);
	player2 = Player(ILI9341_RED);	
	
	while (1) {
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 3) {
			map.createRandomMap(Communication::buffer[2]);
			Communication::clearBuffer(3);
			Communication::next();
			break;
		}
	}
	
	selectDrop();
	
	while (1) {
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 10) {
			player2.x = Communication::buffer[2];
			player2.y = Communication::buffer[3];
			Communication::clearBuffer(4);
			Communication::next();
			break;
		}
	}
	
	player1.sendLocation(player1.x,player1.y);
	
	beurt = 5;
}
//function to start the game in master mode
void Main::beginMaster() {
	player1 = Player(ILI9341_BLUE);
	player2 = Player(ILI9341_RED);
	
	Communication::send(map.seed);
	Communication::send(3);
	Communication::endCommand();
	
	selectDrop();
	
	player1.sendLocation(player1.x,player1.y);
	
	while (1) {
		if(Communication::buffer[0] == 255 && Communication::buffer[1] == 10) {
			player2.x = Communication::buffer[2];
			player2.y = Communication::buffer[3];
			Communication::clearBuffer(4);
			Communication::next();
			break;
		}
	}
	
	beurt = 1;
}
//function to select a spot on the map where the player wants to drop
void Main::selectDrop() {
	tft.fillScreen(ILI9341_BLACK);
	
	map.drawMap();
	tft.setCursor(10,0);
	tft.setTextSize(2);
	tft.setTextColor(ILI9341_WHITE);
	tft.println(F("Select your drop location"));
	
	
	Nunchuck nunchuck;							//read nunchuck data
	player1.moveTo(20,1,false);
	while(true) {
		nunchuck.update();
		if(nunchuck.x > 170){					//rechts
			player1.moveToDirection(2,false);
		}
		if(nunchuck.x < 110){					//links
			player1.moveToDirection(4,false);
		}
		if(nunchuck.z) {
			tft.fillScreen(ILI9341_BLACK);
			tft.setCursor(6, 100);
			tft.setTextSize(3);
			tft.setTextColor(ILI9341_WHITE);
			tft.println(F("Waiting for enemy"));
			return;
		}
		_delay_ms(50);
	}
}
//function to draw all objects which stay on the map
void Main::draw(){
	map.drawMap();
	player1.draw();
	player2.draw();
}
//draw a screen which tells who's turn it is
void Main::drawTurn(String tekst){
	uint8_t beginPixel = (320 - (tekst.length()*24))/2;
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(beginPixel, 100);
	tft.setTextSize(4);
	tft.setTextColor(ILI9341_WHITE);
	tft.println(tekst);
	_delay_ms(1000);
	draw();
}

ISR(TIMER1_OVF_vect) {
	sei();
	analogWrite(3,ADCH);
	ADCSRA |= (1<<ADSC);  
}


