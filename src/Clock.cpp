#include "Clock.h"



Clock::Clock()
{
	
}


Clock::~Clock()
{
}

void Clock::setup(int fontsize) {
	font.load("fonts/Roboto/Roboto-Regular.ttf", fontsize, true, true, true);
}


void Clock::getTime() {
	h = ofGetHours();
	m = ofGetMinutes();
}

void Clock::display(int x, int y) {
	
	getTime();
	font.drawString(ofToString(h) + ":" + ofToString(m, 2), x, y);

}
