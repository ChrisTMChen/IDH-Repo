#include "HomeGif.h"



HomeGif::HomeGif()
{
}


HomeGif::~HomeGif()
{
}

void HomeGif::setup() {
	
	frameTime = 0;
	frameReset = 0;
	frameLength = 1000;
	currentImg = 0;

	numImgs = 4;

	for (int i = 0; i <= numImgs; i++) {
		ofImage img;
		string path = "GIFframes/GIF_Frame_";
		
		imgs.push_back(img);
		imgs[i].load(path + ofToString(i) + ".png");
	}

}

void HomeGif::start_timer() {
	frameTime = frameReset = ofGetElapsedTimeMillis();
}

void HomeGif::timer() {
	
	frameTime = ofGetElapsedTimeMillis();

	if (frameTime - frameReset >= frameLength) {
		if (currentImg != numImgs) {
			currentImg = currentImg + 1;
		}
		else currentImg = 0;

		start_timer();
	}
}

void HomeGif::draw(int x_pos, int y_pos, int draw_width, int draw_height) {

	timer();	
	imgs[currentImg].draw(x_pos, y_pos, draw_width, draw_height);

}

void HomeGif::exit() {
	imgs.clear();
}