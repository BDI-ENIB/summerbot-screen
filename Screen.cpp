//---headers

#include "Screen.h"


//---constructor

Screen::Screen():
	table_{ {20-THICKNESS,20-THICKNESS,80+2*THICKNESS,2*THICKNESS},
			{20-THICKNESS,20-THICKNESS,2*THICKNESS,80+THICKNESS},
			{20-THICKNESS,100,2*THICKNESS,80+THICKNESS},
			{20-THICKNESS,180-THICKNESS,80+2*THICKNESS,2*THICKNESS},
			{100-THICKNESS,100,2*THICKNESS,80+THICKNESS},
			{100-THICKNESS,20-THICKNESS,2*THICKNESS,80+THICKNESS},
			{20-THICKNESS,100-THICKNESS,80+2*THICKNESS,2*THICKNESS} }
	{

	//number data base
	numbers_[0] = 0b00111111;
	numbers_[1] = 0b00110000;
	numbers_[2] = 0b01101101;
	numbers_[3] = 0b01111001;
	numbers_[4] = 0b01110010;
	numbers_[5] = 0b01011011;
	numbers_[6] = 0b01011111;
	numbers_[7] = 0b00110001;
	numbers_[8] = 0b01111111;
	numbers_[9] = 0b01111011;

	epd_ = new Epd;
	if (epd_->Init() != 0) {
		Serial.print("e-Paper init failed");
	}
	Serial.println("post");

	unsigned char internalNumberBuffer[3300]; // > 120*200/8
	numberBuffer_ = new Paint(internalNumberBuffer,120,200);

}

void
Screen::drawNumber(const int number) {

	// Serial.print("number : ");
	// Serial.println(number);
	// Serial.println(numberBuffer_->GetHeight());
	numberBuffer_->Clear(UNCOLORED);

	for(volatile int j=0; j<7; j++) { //volatile otherwise it shit itself

		if(numbers_[number] & 1<<j) {

			const int tx = table_[j][0];
			const int ty = table_[j][1];
			const int dtx = table_[j][2];
			const int dty = table_[j][3];

			if(j%2 == 0) { //vertical lines
				// Serial.println(j);
				for(volatile int k = 0; k < dtx; k++) { //same thing as earlyer
					numberBuffer_->DrawVerticalLine(tx+k,ty,dty,COLORED);
				}
			}
			else { //horizontal lines
				// Serial.println(j);
				for(volatile int k = 0; k < dty; k++) { //same thing as earlyer
					numberBuffer_->DrawHorizontalLine(tx,ty+k,dtx,COLORED);
				}
			}

		}

	}

}

void
Screen::setScore(const int score) {

	if(score > 999) { return; } //score is too high

	const char hundreeds = int(score/100);
	const char decades = int((score-hundreeds*100)/10);
	const char units = int(score%10);

	// Serial.println("drawHundreeds");
	drawNumber(hundreeds);
	epd_->SetPartialWindow(numberBuffer_->GetImage(), 16, 40,
												 numberBuffer_->GetWidth(), numberBuffer_->GetHeight());

	// Serial.println("drawDecades");
	drawNumber(decades);
	epd_->SetPartialWindow(numberBuffer_->GetImage(), 144, 40,
												 numberBuffer_->GetWidth(), numberBuffer_->GetHeight());

	// Serial.println("drawUnits");
	drawNumber(units);
	epd_->SetPartialWindow(numberBuffer_->GetImage(), 272, 40,
												 numberBuffer_->GetWidth(), numberBuffer_->GetHeight());

}

void
Screen::drawIcon(const int iconId) {

	if(iconId < 0 || iconId > 8) { //id does not correspond to any icon
		return;
	}
	
	epd_->SetPartialWindow(iconsTable[iconId],(3+iconId*5)*8,264,32,32);

}

void
Screen::clearIcon(const int iconId) {

	if(iconId < 0 || iconId > 8) { //id does not correspond to any icon
		return;
	}

	epd_->fillPartialWindow((3+iconId*5)*8,264,32,32,UNCOLORED);
	
}

void
Screen::showInitFrame() {

	unsigned char internalTmpBuffer[300]; // > 400*20/8
	Paint *tmpBuffer = new Paint(internalTmpBuffer,400,20);
	tmpBuffer->Clear(COLORED);
	
	tmpBuffer->DrawStringAt(0,0,"Enigma",&Font16,UNCOLORED);
	epd_->SetPartialWindow(tmpBuffer->GetImage(), 0, 0,
												 tmpBuffer->GetWidth(), tmpBuffer->GetHeight());

	// first buffer
	epd_->ClearFrame();

	epd_->fillPartialWindow(0,0,400,20,COLORED); //top of the screen
	epd_->fillPartialWindow(0,260,400,1,COLORED); //bottom of the screen

	setScore(0);
	// update();
	
}

void
Screen::update() {

	if(isBusy()) { return; } //screen is not ready

	epd_->DisplayFrame();

}
