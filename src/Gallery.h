#pragma once

#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class Gallery
{
public:
	Gallery();
	~Gallery();

	void setup(int fontsize, int width, int height);
	void load_film_logos();


	void strip_setup(int gallery_selector);
	void strip_setup();

	void load();
	void drawStrip(int x, int y, int total_width, int image_height);
	void drawSpeed(float _speed);
	void labels(vector<bool> loaded, int x, int y);
	void filmLogos(vector<bool> loaded, int x, int y, int width, int height);
	
	void exit();
	void reset_funct();
	int h;
	int m;

	string path;

	vector<string> gallery_name;
	vector<ofImage> image_vec;
	vector<string> image_paths;
	vector<string> author_paths;

	bool loaded;
	int reset;
	int draw_min, draw_max, draw_position, total_width;
	float speed;

	ofBuffer buffer;

	ofTrueTypeFont font;

    ofxThreadedImageLoader *loader;
	vector<ofImage> film_logos;
};



