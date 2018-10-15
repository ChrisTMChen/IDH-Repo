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

	//load all galleries

		for (int i = 0; i <= 2; i++) {
			string name;
			gallery_name.push_back(name);
			gallery_name[i] = "gallery" + ofToString(i) + "/";
		}

}

void Gallery::setup(int gallery_selector) {

	//load specific gallery

	loaded = false;

	path = "gallery" + ofToString(gallery_selector) + "/";
	gallery_name = { path };

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
	}
}

void Gallery::draw(int x, int y, int image_width, int image_height) {
	ofSetColor(255);
	for (int i = 0; i < image_vec.size(); i++) {
		image_vec[i].draw(x + (i * image_width), y, image_width, image_height);
	}
}

void Gallery::exit() {

	image_vec.clear();
	image_paths.clear();
	gallery_name.clear();

	loaded = false;

}
