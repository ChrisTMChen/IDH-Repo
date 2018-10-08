#pragma once

#include "ofMain.h"


class Gallery
{
public:
	Gallery();
	~Gallery();

	void setup();
	void load();
	void draw(int x, int y, int image_width, int image_height);

	int h;
	int m;

	string path;
	//ofDirectory directory;
	vector<ofFile> file_vec;
	vector<ofImage> image_vec;
	bool loaded;
};



