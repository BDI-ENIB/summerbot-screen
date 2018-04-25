//---headers

#include "Screen.h"

Screen *screen;

void setup() {
	
	Serial.begin(9600);
	delay(100); //for serial
	
	Serial.println("start");
	delay(100);
	screen = new Screen;
	
	Serial.println("clear");
	delay(100);
	screen->clearScreen();

	Serial.println("display");
	delay(100);
	screen->displayScore(380);
	
	Serial.println("end");
	
}

void loop() {
	
	delay(1000);
	
}