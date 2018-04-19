//---headers

#include "Screen.h"


//---constructor

Screen::Screen() {

	numbers_[0] = 0b01110111;
	numbers_[1] = 0b01000001;
	numbers_[2] = 0b00111011;
	numbers_[3] = 0b01101010;
	numbers_[4] = 0b01001100;
	numbers_[5] = 0b01101111;
	numbers_[6] = 0b01111111;
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
	
	unsigned char image[1700]; //160*80/8
	paint_ = new Paint(image,160,80);
	
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
			Serial.println("third loop");
			if(j%2 == 0) { //vertical line
				
				Serial.println("drawv");
				// paint_->DrawFilledRectangle((i%3 == 0 ? 70 : 0),(i <= 2 ? 0 : 70),THICKNESS,80,0);
				paint_->DrawVerticalLine((j%3 == 0 ? 70 : 0),(j <= 2 ? 0 : 70),THICKNESS,COLORED);
				Serial.println("drawh end");
		
			} else { //horizontal line
				
				Serial.println("drawh");
				// paint_->DrawFilledRectangle(0,40*(i-1),80,THICKNESS,0);
				paint_->DrawHorizontalLine(0,40*(j-1),THICKNESS,COLORED);
				Serial.println("drawh end");
		
			}
			
		}
	
	}
	
}

void
Screen::display(const int score) {

	const char hundreeds = int(score/100);
	const char decades = int(score/10);
	const char units = int(score%10);
	
	epd_->ClearFrame();
	
	Serial.println("drawHundreeds");
	drawNumber(hundreeds);
	epd_->SetPartialWindow(paint_->GetImage(), 0, 0, paint_->GetWidth(), paint_->GetHeight());
	
	Serial.println("drawDecades");
	drawNumber(decades);
	epd_->SetPartialWindow(paint_->GetImage(), 120, 0, paint_->GetWidth(), paint_->GetHeight());

	Serial.println("drawUnits");
	drawNumber(units);
	epd_->SetPartialWindow(paint_->GetImage(), 200, 0, paint_->GetWidth(), paint_->GetHeight());
	
	Serial.println("display");
	epd_->DisplayFrame();
	
}
