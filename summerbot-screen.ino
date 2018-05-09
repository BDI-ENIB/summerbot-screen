//---headers

#include "Screen.h"
#include "IconsId.h"

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
	screen->setScore(123,false);
	// write the icon in the screen buffer
<<<<<<< HEAD
	screen->drawIcon(ARMED,false);
	
	// display the buffer
	Serial.println("refresh");
	screen->refresh();
	
=======
	screen->drawIcon(0);

	// display the buffer
	Serial.println("refresh");
	screen->update();

>>>>>>> 6e20b175267fca6649ad0c59d949ab3f73935b0d
	//wati for the screen to refresh (4sec ~)
	while(screen->isBusy()) {
		delay(100);
	}

	Serial.println("set_up_new_image");
	delay(100);
	// write the score in the screen buffer
	screen->setScore(42,false);
	// clear the icon in the screen buffer
	screen->clearIcon(ARMED,false);
	// write the icon in the screen buffer
<<<<<<< HEAD
	screen->drawIcon(ATI,false);
	
	// display the buffer
	Serial.println("refresh");
	screen->refresh();
	
=======
	screen->drawIcon(4);

	// display the buffer
	Serial.println("refresh");
	screen->update();

>>>>>>> 6e20b175267fca6649ad0c59d949ab3f73935b0d
	Serial.println("end");

}

void loop() {

	Serial.println("nothing");
	delay(1000);

}
