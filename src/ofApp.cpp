#include "ofApp.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofBitmapFont.h"

void ofApp::align_init() {

	heading = h / 15;
	body = h / 30;
	body1 = h / 22;
	left = w / 12;
	left1 = w / 16;
	right = w - w / 12;
	right1 = w - w / 16;
	top = h / 12;
	top1 = h / 16;
	bottom = h - h / 12;
	bottom1 = h - h / 16;
	xcentre = w / 2;
	ycentre = h / 2;

}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);

	w = ofGetWidth();
	h = ofGetHeight();
	
	align_init();

	bDebug = false;

	logo.load("FNDlogo.jpg");

	font.load("fonts/Roboto/Roboto-Regular.ttf", body, true, true, true);
	font1.load("fonts/Roboto/Roboto-Bold.ttf", body, true, true, true);

	clock.setup(body);
	gallery.setup();
	
	state = 0;
	numMarkers = 3;
	timeOut = 3000;
	timedout = false;
	frame = 0;
	reset = 0;

	toggle = 0;

	for (int i = 0; i <= numMarkers; i++) {
		bool init = false;
		markerDetected.push_back(init);
		loaded.push_back(init);
	}
	
	gallery.load();

	//~~~~~~~~~~~~~~~~~~~~~ofxAruco~~~~~~~~~~~~~~~~~~~~~~~
	useVideo = false;
	string boardName = "aruco/boardConfiguration.yml";

	if (useVideo) {
		player.load("aruco/videoboard.mp4");
		player.play();
		video = &player;
	}
	else {
		//grabber.setDeviceID(1);
		grabber.initGrabber(640, 480);
		video = &grabber;
	}

	//aruco.setThreaded(true);
	aruco.setup("aruco/intrinsics.int", video->getWidth(), video->getHeight(), boardName);
	aruco.getBoardImage(board.getPixels());
	board.update();

	showMarkers = true;
	//showBoard = true;
	//showBoardImage = false;

	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSetWindowTitle("OF_IDH ~ FPS:" + ofToString(ofGetFrameRate()));

	//~~~~~~~~~~~~~~~~~~~~~ofxAruco~~~~~~~~~~~~~~~~~~~~~~~
	video->update();
	if (video->isFrameNew()) {
		aruco.detectBoards(video->getPixels());
	}
}

//-------------------------------
void ofApp::startTimer() {
	
	prevTime = curTime = ofGetElapsedTimeMillis();

	ofBackground(47, 54, 64);
	logo.draw(0, 980);
//	clock.display(right, top); //->slow atm probs TTF

	if(bDebug) {
		video->draw(w / 4, h / 4, video->getWidth(), video->getHeight()); // view camera feed
	}
}


//-----------------------------------
void ofApp::updateTimer() {

	curTime = ofGetElapsedTimeMillis();
	if ((curTime - prevTime) > timeOut)
	{
		timedout = true;
		//cout << "marker timed out!" << endl;
		for (int i = 0; i < markerDetected.size(); i++) {
			markerDetected[i] = false;
		}

		state = 1;
		//cout << "reset timer" << endl;
	}

}

//---------------------------------------------------------------------
void ofApp::load_loop(int looper) {

	toggle = looper;

	if (loaded[looper] == false) {
		gallery.exit();
		if (looper == 0) {
			gallery_home_load();
			cout << "gallery loaded: home" << endl;
		}
		else {
			gallery_load(looper - 1);
			cout << "gallery loaded: " + ofToString(looper - 1) << endl;
		}
		loaded[looper] = true;
	}

	//cout << "toggle before: " + ofToString(toggle) << endl;
	//cout << ofToString(loaded) << endl;

	for (int j = 0; j <= numMarkers; j++) {
		if (j != looper) {
			loaded[j] = false;
		}
	}
	//cout << ofToString(loaded) << endl;
	//cout << ofToString(timedout) << endl;
}

//---------------------------------------------------------------------
void ofApp::check_markers() {
	
	for (auto& m : aruco.getMarkers()) {
		
		string marker = ofToString(m).substr(0, 3);
		//cout << "marker: " + marker << endl;

		for (int i = 0; i <= numMarkers; i++) {
			if (i == 1 && marker == "964") {
				//timedout = false;
				startTimer();
				load_loop(i);
				timedout = false;
			}
			if (i == 2 && marker == "691") {
				//timedout = false;
				startTimer();
				load_loop(i);
				timedout = false;
			}
			if (i == 3 && marker == "268") {
				//timedout = false;
				startTimer();
				load_loop(i);
				timedout = false;
			}

			//if (i == 0){
			//	load_loop(i);
			//}
		}
	}

	if (timedout == true) {
		load_loop(0);
	}

}

//--------------------------------------------------------------
void ofApp::gallery_load(int select_gallery){
	gallery.setup(select_gallery);
	gallery.load();
}

//--------------------------------------------------------------
void ofApp::gallery_home_load() {
	gallery.setup();
	gallery.load();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(47, 54, 64); // blue background
	logo.draw(0, 980); // film never die logo
	drawClock(); // clock
	updateTimer(); // timers
	check_markers(); // run marker events
	gallery.drawSpeed(1); // draw gallery speed
	gallery.drawStrip(0, h / 2 - 240, 480, w); // draw the current loaded gallery
	video->draw(0, 0, w / 4, h / 4); // view camera feed

}
//------------------------------------------------------------------
void ofApp::timers() {
	
	frame = frame + 0.005; // change for home toggle duration

	if (frame >= 2) {
		//display = 1;
		if (frame >= 6) {
			//display = 0;
			reset = frame;
			frame = frame - reset;
		}
	}

}

//--------------------------------------------------------------
void ofApp::drawClock() {

	clock.getTime();
	clock.display(right, top);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == ' ') bDebug = !bDebug;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
