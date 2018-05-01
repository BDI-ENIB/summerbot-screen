#ifndef SCREEN_H
#define SCREEN_H

//---define

#define THICKNESS 10
#define COLORED     0
#define UNCOLORED   1


//---headers

#include <SPI.h>
#include "src/epd/epd4in2.h"
#include "src/epd/epdpaint.h"


//---Screen class

class Screen {
	
public :

	Screen();
	void init();
	void setScore(const int score);
	void clearScreen() {
		epd_->ClearFrame();
		epd_->DisplayFrame();
	}
	void initFrame();
	bool isBusy() {
		return epd_->isBusy();
	}
	void update();

private :

	void drawNumber(const int id);

	Epd *epd_;
	Paint *paint_;
	char numbers_[10];
	int table_[7][4];
	
};

#endif