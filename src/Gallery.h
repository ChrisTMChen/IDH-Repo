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
	void exit();

	int h;
	int m;

	string path;

	vector<string> gallery_name;
	vector<ofImage> image_vec;
	vector<string> image_paths;
	
	bool loaded;

};



