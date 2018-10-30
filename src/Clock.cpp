#include "Clock.h"



Clock::Clock()
{
}


Clock::~Clock()
{
}

void Clock::setup(int fontsize) {
    font.load("fonts/FuturaPTDemi.otf", fontsize, true, true, true);
}


void Clock::getTime() {
	h = ofGetHours();
	m = ofGetMinutes();
}

void Clock::display(int x, int y) {
	
	getTime();
	font.drawString(ofToString(h, 2, '0') + ":" + ofToString(m, 2, '0'), x, y);

}
