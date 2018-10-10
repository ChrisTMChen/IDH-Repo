#pragma once

#include "ofMain.h"


class Clock
{
public:
	Clock();
	~Clock();

	void getTime();
	void display(ofTrueTypeFont _font, int _x, int _y);

	int h;
	int m;

};



