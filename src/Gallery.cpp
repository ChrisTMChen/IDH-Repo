#include "Gallery.h"



Gallery::Gallery()
{
}


Gallery::~Gallery()
{
}


void Gallery::setup() {

	//some path, may be absolute or relative to bin/data
	path = "gallery0/";

	loaded = false;

}

void Gallery::load() {
	if (loaded == false) {
		ofDirectory dir(path);
		//only show png files
		dir.allowExt("jpg");
		//populate the directory object
		dir.listDir();
		for (int i = 0; i < dir.size(); i++) {
			image_vec[i].loadImage(dir.getPath(i));
			cout << ofToString(dir.getPath(i)) << endl;
		}
		loaded = true;
	}
}

void Gallery::draw(int x, int y, int image_width, int image_height) {
	for (int i = 0; i < image_vec.size(); i++) {
		image_vec[i].draw(x + i * image_width, y, image_width, image_height);
	}
}