#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

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
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(47, 54, 64);
	logo.draw(0, 980);
	drawClock();
}

//--------------------------
void ofApp::drawClock() {

	clock.getTime();
	clock.display(font, right, top);

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
