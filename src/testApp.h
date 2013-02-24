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

#define DIFFICULTY_EASY 0
#define DIFFICULTY_NORMAL 1
#define DIFFICULTY_HARD 2

struct Score {
	float time;
	int difficulty;
	bool hit;
};

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
	Score recordScore(bool hit);
	
	int state;
	int difficulty;
	
	// The state sometimes changes automatically after a deadline.
	float deadline;
	
	// The time when the zombie was first shown. Used for calculating response time.
	float startTime;
	
	ofImage introImage;
	ofImage backgroundImage;
	ofImage zombieImage;
	ofImage zombieHitImage;
	ofImage missImage;
	ofImage hitImage;
	
	ofPoint zombiePoint;
	ofPoint hitPoint;
	ofPoint missPoint;
	
	ofTrueTypeFont verdana14;
	ofTrueTypeFont verdana30;
	
	// A record of scores in milliseconds.
	vector<Score> scores;
};

