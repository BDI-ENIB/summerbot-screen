//---headers

#include "Screen.h"


//---constructor

Screen::Screen() {

	numbers_[0] = 0b01110111;
	numbers_[1] = 0b01000001;
	numbers_[2] = 0b00111011;
	numbers_[3] = 0b01101011;
	numbers_[4] = 0b01001101;
	numbers_[5] = 0b01101110;
	numbers_[6] = 0b01111110;
	numbers_[7] = 0b01000011;
	numbers_[8] = 0b01111111;
	numbers_[9] = 0b01101111;

	epd_ = new Epd;
	if (epd_->Init() != 0) {
		Serial.print("e-Paper init failed");
	}
	Serial.println("post");
	epd_->ClearFrame();
	epd_->DisplayFrame();
	
	unsigned char image[2000]; // > 160*80/8
	paint_ = new Paint(image,80,160+THICKNESS);
	
}

void 
Screen::drawNumber(const int number) {
	
	Serial.print("number : ");
	Serial.println(number);
	Serial.println(paint_->GetHeight());
	paint_->Clear(UNCOLORED);

	for(volatile unsigned int j=0; j<7; j+=1) {
			
		Serial.print("j : ");
		Serial.println(j);
		Serial.println(numbers_[number] & 1<<j);
		if(numbers_[number] & 1<<j) {
			if(j%2 == 0) { //vertical line
				
				const int xPos = (j%3 == 0 ? 80-THICKNESS : 0);
				const int yPos = (j <= 2 ? 0 : 80);
				
				for(volatile unsigned int k = 0; k <= THICKNESS; k++) {
					// Serial.println(k);
					paint_->DrawVerticalLine(xPos+k,yPos,80,COLORED);
				}
				Serial.println("drawh end");
		
			} else { //horizontal line
				
				const int yPos = (40)*(j-1);

				for(volatile unsigned int k = 0; k <= THICKNESS; k++) {
					paint_->DrawHorizontalLine(0,yPos+k,80,COLORED);
				}
				Serial.println("drawh end");
		
			}
			
		}
	
	}
	
}

void
Screen::displayScore(const int score) {

	if(score > 999) { return; } //score is too high

	const char hundreeds = int(score/100);
	const char decades = int((score-hundreeds*100)/10);
	const char units = int(score%10);
	
	// epd_->ClearFrame();
	
	Serial.println("drawHundreeds");
	drawNumber(hundreeds);
	epd_->SetPartialWindow(paint_->GetImage(), 40, 40, paint_->GetWidth(), paint_->GetHeight());
	
	Serial.println("drawDecades");
	drawNumber(decades);
	epd_->SetPartialWindow(paint_->GetImage(), 160, 40, paint_->GetWidth(), paint_->GetHeight());

	Serial.println("drawUnits");
	drawNumber(units);
	epd_->SetPartialWindow(paint_->GetImage(), 300, 40, paint_->GetWidth(), paint_->GetHeight());
	
	Serial.println("display");
	epd_->DisplayFrame();
	
}