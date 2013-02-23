#pragma once

#include "ofMain.h"
#include "ofUtils.h"
#include "ofxKinect.h"
#include "vector.h"
//#include "Leap.h"


using namespace std;
//using namespace Leap;

#define STATE_INTRO 0
#define STATE_READY 1
#define STATE_ZOMBIE 2
#define STATE_MISS 3
#define STATE_HIT 4
#define STATE_SCORE 5
#define STATE_ -1

class testApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	void drawIntro();
	void drawTest();
	
	// Test whether the mouse hit the zombie.
	bool hitZombie(int x, int y);
	
	void setState(int s);
	
	int state;
	
	// The state sometimes changes automatically after a deadline.
	float deadline;
	
	ofImage introImage;
	ofImage backgroundImage;
	ofImage zombieImage;
	ofImage zombieHitImage;
	ofImage missImage;
	ofImage hitImage;
	
	ofTrueTypeFont verdana14;
	ofTrueTypeFont verdana30;
};
