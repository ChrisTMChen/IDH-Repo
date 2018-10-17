#include "ofApp.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofBitmapFont.h"

void drawMarker(float size, const ofColor & color) {
	ofDrawAxis(size);
	ofPushMatrix();
	// move up from the center by size*.5
	// to draw a box centered at that point
	ofTranslate(0, size*0.5, 0);
	ofFill();
	ofSetColor(color, 50);
	ofDrawBox(size);
	ofNoFill();
	ofSetColor(color);
	ofDrawBox(size);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);

	w = ofGetWidth();
	h = ofGetHeight();

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

	logo.load("FNDlogo.jpg");

	font.load("fonts/Roboto/Roboto-Regular.ttf", body, true, true, true);
	font1.load("fonts/Roboto/Roboto-Bold.ttf", body, true, true, true);

	clock.getTime();
	gallery.setup(0);
	
	state = 0;
	numMarkers = 3;

	for (int i = 0; i <= numMarkers; i++) {
		
		bool init = false;
		markerDetected.push_back(init);
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
		grabber.setDeviceID(0);
		grabber.initGrabber(640, 480);
		video = &grabber;
	}

	//aruco.setThreaded(false);
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
		//cout << "detect" << endl;
	}
}

void ofApp::update_state() {

	if (state != 0) {
		return;
		state = 0;
	}
	for (int i = 0; i < aruco.getNumMarkers(); i++) {

		if (aruco.getNumMarkers() <= numMarkers) {
			if (markerDetected[i] == true) {
				state = 1 + i;
			}
		}
	}
}

void ofApp::detect_marker() {

	for (int i = 0; i <= numMarkers; i++) {


		if (i == aruco.getNumMarkers()) {
			markerDetected[i] = true;
			cout << "found markers: " + ofToString(i) << endl;
		}
		else
		{
			markerDetected[i] = false;
		}
	}

	for (auto& m : aruco.getMarkers()) {
		string marker = ofToString(m).substr(0, 3);
		cout << "marker: " + marker << endl;

		if (marker == "154") {
			gallery.drawSpeed(1);
			gallery.drawStrip(0, h / 2 - 240, 480, w);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(47, 54, 64);
	logo.draw(0, 980);
	
	//drawClock(); //->slow atm probs TTF
	
	update_state();
	detect_marker();
	
	video->draw(0, 0, w / 4, h / 4); // view camera feed

	/*if (showMarkers) {
		for (int i = 0; i < aruco.getNumMarkers(); i++) {
			aruco.begin(i);
			drawMarker(0.15, ofColor::white);
			aruco.end();
		}
	}
*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::drawClock() {

	clock.getTime();
	clock.display(font, right, top);

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
