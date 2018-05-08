//---headers

#include "Screen.h"

Screen *screen;

void setup() {

	Serial.begin(9600);
	delay(100); //for serial

	Serial.println("start");
	delay(100);
	screen = new Screen;

	Serial.println("showInitFrame");
	delay(100);
	// show the base frame and set the background
	screen->showInitFrame();
	Serial.println(2);
	delay(100);

	Serial.println("set up image");
	delay(100);
	// write the score in the screen buffer
	screen->setScore(123);
	// write the icon in the screen buffer
	screen->drawIcon(0);

	// display the buffer
	Serial.println("refresh");
	screen->update();

	//wati for the screen to refresh (4sec ~)
	while(screen->isBusy()) {
		delay(100);
	}

	Serial.println("set_up_new_image");
	delay(100);
	// write the score in the screen buffer
	screen->setScore(42);
	// clear the icon in the screen buffer
	screen->clearIcon(0);
	// write the icon in the screen buffer
	screen->drawIcon(4);

	// display the buffer
	Serial.println("refresh");
	screen->update();

	Serial.println("end");

}

void loop() {

	Serial.println("nothing");
	delay(1000);

}
