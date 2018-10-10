#include "Clock.h"



Clock::Clock()
{
}


Clock::~Clock()
{
}


void Clock::getTime() {
	h = ofGetHours();
	m = ofGetMinutes();
}

void Clock::display(ofTrueTypeFont _font, int _x, int _y) {

	int x = _x;
	int y = _y;

	_font.drawString(ofToString(h) + ":" + ofToString(m, 2), x, y);

}