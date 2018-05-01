//---headers

#include "Screen.h"

Screen *screen;
int score;

void setup() {
	
	Serial.begin(19200);
	delay(100); //for serial
	
	Serial.println("start");
	delay(100);
	screen = new Screen;
	score = 0;
	
	Serial.println("clear");
	delay(100);
	screen->initFrame();

	Serial.println("display");
	delay(100);
	screen->setScore(score);
	screen->update();
	
	Serial.println("end");
	
}

void loop() {
	
	score ++;
	Serial.println("start");
	double startTime = millis();
	screen->setScore(score);
	screen->update();
	Serial.println(millis()-startTime);
	Serial.println("end");
	delay(500);
	
}