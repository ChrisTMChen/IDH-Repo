#include "Gallery.h"



Gallery::Gallery()
{
}


Gallery::~Gallery()
{
	exit();
}

void Gallery::load_film_logos() {

	ofDirectory dir("film_logos/");
	dir.listDir();
	for (int i = 0; i < dir.size(); i++) {
		ofImage img;
		img.load(dir.getPath(i));
		film_logos.push_back(img);
	}
	dir.close();

}

void Gallery::setup(int fontsize) {
	
	load_film_logos();
	
	draw_min = 0;
	draw_max = 3;
	speed = 0;
	total_width = 0;

	font.load("fonts/Roboto/Roboto-Regular.ttf", fontsize, true, true, true);
}

void Gallery::strip_setup() {

	//load all galleries
	loaded = false;
	for (int i = 0; i <= 2; i++) {
		string name;
		gallery_name.push_back(name);
		gallery_name[i] = "gallery" + ofToString(i) + "/";
	}

}

void Gallery::strip_setup(int gallery_selector) {

	//load specific gallery
	loaded = false;
	path = "gallery" + ofToString(gallery_selector) + "/";
	gallery_name = { path };

}

void Gallery::reset_funct() {

	reset = ofGetElapsedTimeMillis();

}

void Gallery::drawSpeed(int _speed) {
	
	speed = (ofGetElapsedTimeMillis() - reset) / 10 *_speed;

}

void Gallery::load() {
	if (loaded == false) {
		
		//--- look in folders and make string vector of paths

		for (int i = 0; i < gallery_name.size(); i++) {
			ofDirectory dir(gallery_name[i]);
			//only show jpg files
			dir.allowExt("jpg");
			//populate the directory object
			dir.listDir();
			for (int j = 0; j < dir.size(); j++) {
				ofImage img;
				image_vec.push_back(img);
				image_paths.push_back(ofToString(dir.getPath(j)));
			}
			dir.close();
		}

		//--- load images from string vector then randomise order


		for (int i = 0; i < image_vec.size(); i++) {
			image_vec[i].load(image_paths[i]);
		}
		
		ofRandomize(image_vec);

		loaded = true;

		reset_funct();
	}
}

void Gallery::drawStrip(int x, int y, int image_height, int total_width) {

	for (int i = 0; i < image_vec.size(); i++) {

		float	image_scale = image_height / image_vec[i].getHeight();
		int x_pos;		
		x_pos = x + i * image_vec[i].getWidth()*image_scale;
		int image_width = image_vec[i].getWidth()*image_scale;
		if (x_pos - speed <= total_width && x_pos - speed + image_width - speed > 0) {
			image_vec[i].draw(x_pos - speed, y, image_width, image_height);
		}
		image_vec[i].draw(x_pos - speed, y, image_width, image_height);
	
		if (i == image_vec.size() - 1) {
			if (x_pos + image_width - speed < total_width) {
				reset_funct();
			}
		}
		
	}
}

void Gallery::labels(vector<bool> loaded, int x, int y) {

	vector<bool> _loaded = loaded;
	for (int i = 0; i < _loaded.size(); i++) {
		if (loaded[i] == true) {
			font.drawString("Gallery: " + ofToString(i), x, y);
		}
	}
}

void Gallery::filmLogos(vector<bool> loaded, int x, int y, int width, int height) {

	vector<bool> _loaded = loaded;
	for (int i = 1; i < _loaded.size(); i++) {
		if (loaded[i] == true) {
			film_logos[i-1].draw(x, y, width, height);
		}
	}

}

void Gallery::exit() {

	image_vec.clear();
	image_paths.clear();
	gallery_name.clear();

	loaded = false;

}
