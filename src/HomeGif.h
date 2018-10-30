#pragma once
#include "ofMain.h"

class HomeGif
{
public:

	HomeGif();
	~HomeGif();

	void setup();
	void start_timer();
	void timer();
	void draw(int x_pos, int y_pos, int draw_width, int draw_height);
	void exit();


	float frameTime, frameReset;
	float gifTime, gifReset;

	float frameLength;

	int numImgs;
	int currentImg;
	
	vector<ofImage> imgs;

};

