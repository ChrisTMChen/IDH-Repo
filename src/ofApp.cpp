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
	gallery.setup();


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
	showBoard = true;
	showBoardImage = false;

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

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(47, 54, 64);
	logo.draw(0, 980);
	//drawClock(); //->slow atm probs TTF

	video->draw(w / 4, h / 4, w / 2, h / 2); // view camera feed

	//gallery.load();
	//gallery.draw(100, 100, 640, 480);
	
	//aruco.draw();

	if (showMarkers) {
		for (int i = 0; i < aruco.getNumMarkers(); i++) {
			aruco.begin(i);
			drawMarker(0.15, ofColor::white);
			aruco.end();
		}
	}


	if (showBoard && aruco.getBoardProbability() > 0.03) {
		for (int i = 0; i < aruco.getNumBoards(); i++) {
			aruco.beginBoard(i);
			drawMarker(.5, ofColor::red);
			aruco.end();
		}
	}


	ofSetColor(255);
	if (showBoardImage) {
		board.draw(ofGetWidth() - 320, 0, 320, 320 * float(board.getHeight()) / float(board.getWidth()));
	}
	ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()), 20, 20);
	ofDrawBitmapString("fps " + ofToString(ofGetFrameRate()), 20, 40);
	ofDrawBitmapString("m toggles markers", 20, 60);
	ofDrawBitmapString("b toggles board", 20, 80);
	ofDrawBitmapString("i toggles board image", 20, 100);
	ofDrawBitmapString("s saves board image", 20, 120);
	ofDrawBitmapString("0-9 saves marker image", 20, 140);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'm') showMarkers = !showMarkers;
	if (key == 'b') showBoard = !showBoard;
	if (key == 'i') showBoardImage = !showBoardImage;
	if (key == 's') board.save("boardimage.png");
	if (key >= '0' && key <= '9') {
		// there's 1024 different markers
		int markerID = key - '0';
		aruco.getMarkerImage(markerID, 240, marker);
		marker.save("marker" + ofToString(markerID) + ".png");
	}
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
