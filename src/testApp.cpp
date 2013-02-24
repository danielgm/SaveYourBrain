#include "testApp.h"
//#include "Leap.h"

//using namespace Leap;

void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofSetFrameRate(60);
	
	//old OF default is 96 - but this results in fonts looking larger than in other programs.
	ofTrueTypeFont::setGlobalDpi(72);
	
	verdana14.loadFont("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
	
	verdana30.loadFont("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
	
	// Load slides.
	introImage.loadImage("saveyourbrain.jpg");
	backgroundImage.loadImage("saveyourbrainbg.jpg");
	zombieImage.loadImage("zombie_normal.jpg");
	zombieHitImage.loadImage("zombie_hit.jpg");
	hitImage.loadImage("hit.jpg");
	missImage.loadImage("miss.jpg");
	
	setState(STATE_INTRO);
	difficulty = DIFFICULTY_EASY;
}

void testApp::update() {
	if (deadline > 0 && ofGetSystemTime() > deadline) {
		deadline = -1;
		
		switch (state) {
			case STATE_INTRO:
				break;
			case STATE_READY:
				setState(STATE_ZOMBIE);
				break;
			case STATE_ZOMBIE:
				setState(STATE_READY);
				break;
			case STATE_MISS:
				setState(STATE_READY);
				break;
			case STATE_HIT:
				setState(STATE_READY);
				break;
			case STATE_SCORE:
				break;
		}
	}
	else {
		switch (state) {
			case STATE_INTRO:
				break;
			case STATE_READY:
				break;
			case STATE_ZOMBIE:
				break;
			case STATE_MISS:
				break;
			case STATE_HIT:
				break;
			case STATE_SCORE:
				break;
		}
	}
	
}

void testApp::draw() {
	ofBackground(0);
	ofSetColor(255, 255, 255);
	
	switch (state) {
		case STATE_INTRO:
			introImage.draw(0, 0);
			break;
		
		case STATE_READY:
			backgroundImage.draw(0, 0);
			ofSetColor(0);
			break;
			
		case STATE_ZOMBIE:
			backgroundImage.draw(0, 0);
			zombieImage.draw(zombiePoint.x, zombiePoint.y);
			break;
			
		case STATE_MISS:
			backgroundImage.draw(0, 0);
			zombieImage.draw(zombiePoint.x, zombiePoint.y);
			missImage.draw(hitPoint.x, hitPoint.y);
			break;
			
		case STATE_HIT:
			backgroundImage.draw(0, 0);
			zombieHitImage.draw(zombiePoint.x, zombiePoint.y);
			hitImage.draw(hitPoint.x, hitPoint.y);
			
			ofSetColor(255);
			verdana30.drawString(ofToString(floor(latestScore.time)) + " ms", hitPoint.x, hitPoint.y);
			break;
			
		case STATE_SCORE:
			break;
			
		default:;
	}
	
	if (hits.size() > 0) {
		ofSetColor(255);
		verdana14.drawString("Average", 20, 20);
		verdana30.drawString(ofToString(floor(getAverageHitTimes())) + " ms", 20, 40);
	}}

void testApp::exit() {
}

void testApp::keyPressed (int key) {
	int i;
	
	switch (key) {
		case ' ':
			setState(STATE_SCORE);
			
			cout << misses.size() << " misses." << endl;
			cout << hits.size() << " hits:" << endl;
			
			for (i = 0; i < hits.size(); i++) {
				cout << hits[i].time << " ms" << endl;
			}
						
			cout << "Average:" << getAverageHitTimes() << " ms" << endl;
			
			break;
			
		default:;
	}
}

void testApp::mouseDragged(int x, int y, int button) {
}

void testApp::mousePressed(int x, int y, int button) {
}

void testApp::mouseReleased(int x, int y, int button) {
	switch (state) {
		case STATE_INTRO:
			setState(STATE_READY);
			break;
		case STATE_READY:
			setState(STATE_MISS);
			break;
		case STATE_ZOMBIE:
			if (hitZombie(mouseX, mouseY)) {
				setState(STATE_HIT);
				recordHit();
			}
			else {
				setState(STATE_MISS);
				recordMiss();
			}
			break;
		case STATE_MISS:
			recordMiss();
			break;
		case STATE_HIT:
			break;
		case STATE_SCORE:
			break;
		default:;
			
	}
}

void testApp::windowResized(int w, int h) {
}

void testApp::setState(int s) {
	state = s;
	
	float offset;
	
	switch (state) {
		case STATE_INTRO:
			cout << "STATE_INTRO" << endl;
			break;
			
		case STATE_READY:
			cout << "STATE_READY" << endl;
			// Set the deadline for when the next zombie appears.
			deadline = ofGetSystemTime() + 200 + ofRandom(1) * 800;
			break;
			
		case STATE_ZOMBIE:
			cout << "STATE_ZOMBIE" << endl;
			if (difficulty == DIFFICULTY_HARD) {
				// Set the deadline for when the zombie hides.
				deadline = ofGetSystemTime() + 500 + ofRandom(1) * 1500;
			}
			else {
				// No deadline for other difficulties.
				deadline = -1;
			}
			
			offset = floor(ofRandom(1) * 5);
			zombiePoint = ofPoint(30 + offset * 280, 400);
			hitPoint = ofPoint(120 + offset * 280, 300);
			missPoint = ofPoint(120 + offset * 280, 300);
			
			startTime = ofGetSystemTime();
			break;
			
		case STATE_MISS:
			cout << "STATE_MISS" << endl;
			// Set the deadline for when the "Missed!" message disappears.
			deadline = ofGetSystemTime() + 1000;
			break;
			
		case STATE_HIT:
			cout << "STATE_HIT" << endl;
			// Set the deadline for when the "Hit!" message disappears.
			deadline = ofGetSystemTime() + 1200 + ofRandom(1) * 800;
			break;
			
		case STATE_SCORE:
			cout << "STATE_SCORE" << endl;
			break;
	}
}

bool testApp::hitZombie(int x, int y) {
	return zombiePoint.x < x && x < zombiePoint.x + zombieImage.width
		&& zombiePoint.y < y && y < zombiePoint.y + zombieImage.height;
}

Score testApp::recordHit() {
	Score score;
	score.difficulty = difficulty;
	score.time = ofGetSystemTime() - startTime;
	
	hits.push_back(score);
	latestScore = score;
	
	return score;
}

Score testApp::recordMiss() {
	Score score;
	score.difficulty = difficulty;
	score.time = ofGetSystemTime() - startTime;
	
	misses.push_back(score);
	latestScore = score;
	
	return score;
}

float testApp::getAverageHitTimes() {
	float total = 0;
	for (int i = 0; i < hits.size(); i++) {
		total += hits[i].time;
	}
	return total / hits.size();
}