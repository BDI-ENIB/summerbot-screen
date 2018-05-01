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
	
	unsigned char image[3300]; // > 120*200/8
	paint_ = new Paint(image,120,200);
	
	initFrame();
	
}

void 
Screen::drawNumber(const int number) {
	
	// Serial.print("number : ");
	// Serial.println(number);
	// Serial.println(paint_->GetHeight());
	paint_->Clear(UNCOLORED);
	
	for(volatile int j=0; j<7; j++) { //volatile otherwise it shit itself

		if(numbers_[number] & 1<<j) {
			
			const int tx = table_[j][0];
			const int ty = table_[j][1];
			const int dtx = table_[j][2];
			const int dty = table_[j][3];
			
			if(j%2 == 0) { //vertical lines
				// Serial.println(j);
				for(volatile int k = 0; k < dtx; k++) { //same thing as earlyer
					paint_->DrawVerticalLine(tx+k,ty,dty,COLORED);
				}
			} 
			else { //horizontal lines
				// Serial.println(j);
				for(volatile int k = 0; k < dty; k++) { //same thing as earlyer
					paint_->DrawHorizontalLine(tx,ty+k,dtx,COLORED);
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
	epd_->SetPartialWindow(paint_->GetImage(), 16, 40, paint_->GetWidth(), paint_->GetHeight());
	
	// Serial.println("drawDecades");
	drawNumber(decades);
	epd_->SetPartialWindow(paint_->GetImage(), 144, 40, paint_->GetWidth(), paint_->GetHeight());

	// Serial.println("drawUnits");
	drawNumber(units);
	epd_->SetPartialWindow(paint_->GetImage(), 272, 40, paint_->GetWidth(), paint_->GetHeight());
	
}

void
Screen::initFrame() {
	
	epd_->ClearFrame();
	
	for(volatile int j=0; j<40; j++) {
		paint_->DrawHorizontalLine(j,0,400,COLORED);
	}
	
	setScore(0);
	update();
	
}

void
Screen::update() {

	if(isBusy()) { return; } //screen is not ready
	
	epd_->DisplayFrame();

}