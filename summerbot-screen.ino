//---headers

#include "Screen.h"

Screen *screen;

void setup() {
	
	Serial.begin(9600);
	delay(5000); //for serial
	
	Serial.println("start");
	delay(5000);
	screen = new Screen;
	
	Serial.println("clear");
	delay(5000);
	screen->clearScreen();

	Serial.println("display");
	delay(5000);
	screen->display(123);
	
	Serial.println("end");
	
}

void loop() {
	
	delay(1000);
	
}