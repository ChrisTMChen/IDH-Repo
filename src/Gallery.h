#pragma once

#include "ofMain.h"


class Gallery
{
public:
	Gallery();
	~Gallery();

	void setup(int fontsize);
	void load_film_logos();


	void strip_setup(int 	gallery_selector);
	void strip_setup();

	void load();
	void drawStrip(int x, int y, int image_height, int total_width);
	void drawSpeed(int _speed);
	void labels(vector<bool> loaded, int x, int y);
	void filmLogos(vector<bool> loaded, int x, int y, int width, int height);
	
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

	ofTrueTypeFont font;

	vector<ofImage> film_logos;
};



