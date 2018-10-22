#pragma once

#include "ofMain.h"


class Clock
{
public:
	Clock();
	~Clock();
	
	void setup(int fontsize);
	void getTime();
	void display(int _x, int _y);

	int h;
	int m;
	
	ofTrueTypeFont font;

};



