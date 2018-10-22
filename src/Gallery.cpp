#include "Gallery.h"



Gallery::Gallery()
{
    loader = new ofxThreadedImageLoader();
}


Gallery::~Gallery()
{
	exit();
}

void Gallery::load_film_logos() {

	ofDirectory dir("film_logos/");
	dir.listDir();
    dir.sort();
    for (unsigned int i = 0; i < dir.size(); i++) {
		ofImage img;
		img.load(dir.getPath(i));
		film_logos.push_back(img);
	}
	dir.close();

}

void Gallery::setup(int fontsize, int width, int height) {
	
	load_film_logos();
	
	draw_min = 0;
	draw_max = 3;
	speed = 0;
	total_width = 0;

    font.load("fonts/FuturaPTBook.otf", fontsize, true, true, true);

}

void Gallery::strip_setup() {

	//load all galleries
    ofDirectory dir("galleries/");
    dir.listDir();
	loaded = false;
    for (unsigned int i = 0; i < dir.size(); i++) {
		string name;
        name = "galleries/gallery" + ofToString(i) + "/";
		gallery_name.push_back(name);
	}

}

void Gallery::strip_setup(int id) {

	//load specific gallery
    gallery_id  = id;
	loaded = false;
    path = "galleries/gallery" + ofToString(id) + "/";
	gallery_name = { path };

}

void Gallery::draw_film_name()
{
    string textString = "";

    if(gallery_id == 1) {
        textString = "test1";
    }
    else if(gallery_id == 2) {
        textString = "test2";
    }
    else if(gallery_id == 3) {
        textString = "test3";
    }
    else if(gallery_id == 4) {
        textString = "test4";
    }
    else if(gallery_id == 5) {
        textString = "test5";
    }
    else if(gallery_id == 6) {
        textString = "test";
    }
    else if(gallery_id == 7) {
        textString = "test";
    }
    else if(gallery_id == 8) {
        textString = "test";
    }
    else if(gallery_id == 9) {
        textString = "test";
    }
    else if(gallery_id == 10) {
        textString = "test";
    }
    else if(gallery_id == 11) {
        textString = "test";
    } else {
        textString = "";
    }

    font.drawString(textString,320,1038);
}

void Gallery::reset_funct() {

	reset = ofGetElapsedTimeMillis();

}

void Gallery::drawSpeed(float _speed) {
	
    speed = (ofGetElapsedTimeMillis() - reset) / 10 *_speed;

}

void Gallery::load() {

	if (loaded == false) {

		//--- look in folders and make string vector of paths
		for (int i = 0; i < gallery_name.size(); i++) {
			
            ofLogNotice() << "Load Gallery: " << gallery_name[i];
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

		//author paths
			ofDirectory dir1(gallery_name[i]);
			//only show txt files
			dir1.allowExt("txt");
			//populate the directory object
			dir1.listDir();
			for (int j = 0; j < dir1.size(); j++) {
				author_paths.push_back(ofToString(dir1.getPath(j)));
			}
			dir1.close();
		}
				
		//--- randomize order and load images from string vector

		
		ofRandomize(image_paths);
		
		for (int i = 0; i < image_vec.size(); i++) {
            loader->loadFromDisk(image_vec[i], image_paths[i]);

		}
		loaded = true;
		
		reset_funct();
	}

}

void Gallery::drawStrip(int xoffset, int yoffset, int total_width, int image_height) {

if(loaded) {

	ofSetColor(255);
	//ofRect(0, 0, total_width, image_height);
	float x_pos = 0;
    float prev_image_width = 0;
    for (unsigned int i = 0; i < image_vec.size(); i++) {

        float image_scale = image_height / image_vec[i].getHeight();
		float new_width = image_vec[i].getWidth()*image_scale;

		float image_width = new_width;
        //cout << "image iwdth = " << image_width << endl;

        x_pos = x_pos + prev_image_width;

		if (x_pos - speed <= total_width && x_pos + image_width - speed > 0) {

            image_vec[i].draw(x_pos - speed + xoffset, yoffset, image_width, image_height);

            // draw name
			string str = image_paths[i];
			string newstr = str.substr(str.find_last_of("\\") + 1);
            //font.drawString(newstr, x_pos - speed, yoffset);
            //font.drawString(ofToString(image_width), x_pos - speed, yoffset);
            //font.drawString(ofToString(x_pos) + "  "+ ofToString(image_width), x_pos - speed, yoffset);
		}

		if (i == image_vec.size() - 1) {
			if (x_pos + image_width - speed < total_width) {
				reset_funct();
			}
		}

        prev_image_width = image_width;
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
    //loader.stopThread();
    delete loader;
    loader = new ofxThreadedImageLoader();

	image_vec.clear();
	image_paths.clear();
	gallery_name.clear();

	loaded = false;

}
