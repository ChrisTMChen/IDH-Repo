#pragma once

#include "ofMain.h"


class Gallery
{
public:
	Gallery();
	~Gallery();

	void setup(int 	gallery_selector);
	void setup();

	void load();
	void draw(int x, int y, int image_width, int image_height);
	void drawStrip(int x, int y, int image_height, int total_width);
	void drawSpeed(int _speed);
	void exit();
	void reset_funct();
	int h;
	int m;
//	int x_pos;
//	int image_scale;
	//int newimage_scale;
//	int image_scale;

	string path;

	vector<string> gallery_name;
	vector<ofImage> image_vec;
	vector<string> image_paths;

	ofFbo Slide_Fbo;
	
	bool loaded;
	int reset;
	int draw_min, draw_max, draw_position, total_width;
	float speed;
};



