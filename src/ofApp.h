#pragma once

#include "ofMain.h"
#include "Clock.h"
#include "Gallery.h"
#include "ofxAruco.h"

class ofApp : public ofBaseApp {

public:

	void setup();

	void align_init();

	void update();
	void draw();
    void exit();

	void startTimer();
	void updateTimer();
	void timers();

	void drawClock();
	void check_markers();
	void load_loop(int looper);
	void gallery_load(int select_gallery);
	void gallery_home_load();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int timeOut;

	int w, h;

	float curTime, prevTime, frame, reset;

	int heading;
	int body;
	int body1;
	int body2;

	int left;
	int left1;
	int xcentre;
	int ycentre;
	int right;
	int right1;
	int top;
	int top1;
	int bottom;
	int bottom1;

	bool timedout;

	ofImage logo;
	int fontsize;

	ofTrueTypeFont font;
	ofTrueTypeFont font1;

	Clock clock;
	Gallery gallery;

	//~~~~~~~~~~~~~~~~~~~~~ofxAruco~~~~~~~~~~~~~~~~~~~~~~~
	ofVideoGrabber grabber;
	ofVideoPlayer player;

	ofBaseVideoDraws * video;

	ofxAruco aruco;
	bool useVideo;
	bool showMarkers;
	//bool showBoard;
	//bool showBoardImage;
	ofImage board;
	ofImage marker;

	bool bDebug;
	int state;
	int numMarkers;

	int toggle;
	vector<bool> loaded;

	vector<bool> markerDetected;

};
