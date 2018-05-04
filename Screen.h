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
#include "Icons.h"


//---Screen class

class Screen {
	
public :

	// constructor
	Screen();
	
	// functions
	void init();
	void setScore(const int score);
	void drawIcon(const int iconId);
	void clearIcon(const int iconId);
	void showInitFrame();
	void update();

	// inline functions
	void clearScreen() {
		epd_->ClearFrame();
		epd_->DisplayFrame();
	}
	bool isBusy() {
		return epd_->isBusy();
	}

private :

	// internal function
	void drawNumber(const int id);

	// variables
	Epd *epd_;
	Paint *numberBuffer_;
	char numbers_[10];
	char icons_[9][128];
	int table_[7][4];
	
};


#endif