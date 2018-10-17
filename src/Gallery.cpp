#include "Gallery.h"



Gallery::Gallery()
{
}


Gallery::~Gallery()
{
	exit();
}


void Gallery::setup() {	
	loaded = false;

	//if setup() load all galleries

		for (int i = 0; i <= 2; i++) {
			string name;
			gallery_name.push_back(name);
			gallery_name[i] = "gallery" + ofToString(i) + "/";
		}

		draw_min = 0;
		draw_max = 3;
		speed = 0;
		total_width = 0;
}

void Gallery::setup(int gallery_selector) {

	//if setup(int) load specific gallery

	loaded = false;

	path = "gallery" + ofToString(gallery_selector) + "/";
	gallery_name = { path };

	draw_min = 0;
	draw_max = 3;
	speed = 0;
	total_width = 0;
}

void Gallery::drawSpeed(int _speed) {
	
	speed = ofGetElapsedTimeMillis() / 10 *_speed;

}

void Gallery::load() {
	if (loaded == false) {
		
		//--- look in folders and make string vector of paths

		for (int i = 0; i < gallery_name.size(); i++) {
			ofDirectory dir(gallery_name[i]);
			//only show jpg files
			//dir.allowExt("jpg");
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
	}
}

void Gallery::draw(int x, int y, int image_width, int image_height) {
	cout << ofToString(image_vec.size()) << endl;
	for (int i = 0; i < image_vec.size(); i++) {
		ofSetColor(255);
		image_vec[i].draw(x + (i * image_width), y, image_width, image_height);
	}
}

void Gallery::drawStrip(int x, int y, int image_height, int total_width) {

	for (int i = 0; i < image_vec.size(); i++) {

		float	image_scale = image_height / image_vec[i].getHeight();
		int x_pos;
		//if (i > 0) {
		//	float last_scale = image_height / image_vec[i - 1].getHeight();
		//	x_pos = x + (i-1)*image_vec[i - 1].getWidth()*last_scale;
		//}
		//else { x_pos = 0; }
		
		x_pos = x + i * image_vec[i].getWidth()*image_scale;
		int image_width = image_vec[i].getWidth()*image_scale;
		if (x_pos - speed <= total_width && x_pos - speed + image_width - speed > 0) {
			image_vec[i].draw(x_pos - speed, y, image_width, image_height);
		}
	}
}


void Gallery::exit() {

	image_vec.clear();
	image_paths.clear();
	gallery_name.clear();

	loaded = false;

}