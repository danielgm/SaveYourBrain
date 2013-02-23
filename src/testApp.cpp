#include "testApp.h"


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
	introImage.loadImage("slide_intro.jpg");
	backgroundImage.loadImage("gameplay_background.jpg");
	zombieImage.loadImage("zombie_normal.jpg");
	zombieHitImage.loadImage("zombie_hit.jpg");
	
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
			break;
			
		case STATE_ZOMBIE:
			backgroundImage.draw(0, 0);
			zombieImage.draw(zombiePoint.x, zombiePoint.y);
			break;
			
		case STATE_MISS:
			backgroundImage.draw(0, 0);
			break;
			
		case STATE_HIT:
			backgroundImage.draw(0, 0);
			zombieHitImage.draw(zombiePoint.x, zombiePoint.y);
			break;
			
		case STATE_SCORE:
			break;
			
		default:;
	}
}

void testApp::exit() {
}

void testApp::keyPressed (int key) {
	float total;
	switch (key) {
		case 'p':
			cout << "Scores:" << endl;
			
			total = 0;
			for (int i = 0; i < scores.size(); i++) {
				cout << scores[i].time << " ms" << endl;
				total += scores[i].time;
			}
			cout << "Average:" << (total/scores.size()) << endl;
			
			break;
			
		default:;
	}
}

void testApp::mouseDragged(int x, int y, int button)
{}

void testApp::mousePressed(int x, int y, int button)
{}

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
				recordScore(true);
			}
			else {
				setState(STATE_MISS);
				recordScore(false);
			}
			break;
		case STATE_MISS:
			recordScore(false);
			break;
		case STATE_HIT:
			break;
		case STATE_SCORE:
			break;
		default:;
			
	}
}

void testApp::windowResized(int w, int h)
{}

void testApp::drawIntro() {
	ofSetColor(255, 255, 255);

	
	
	
	string typeStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789,:&!?";
	
	ofSetColor(225);
	verdana14.drawString("Font Example - use keyboard to type", 30, 35);
	
	ofSetColor(245, 58, 135);
	verdana14.drawString("anti aliased", 145, 92);
	verdana14.drawString("anti aliased", 145, 195);
	
	ofSetColor(225);
	verdana14.drawString("verdana 14pt - ", 30, 92);
	verdana14.drawString(typeStr, 30, 111);
	
	ofRect(420, 97, 292, 62);
	ofSetColor(54, 54, 54);
	
	
	ofSetColor(29,29,29);
	ofLine(30, 169, ofGetWidth()-4, 169);
	
	ofSetColor(225);
	verdana14.drawString("verdana 30pt - ", 30, 195);
	verdana30.drawString(typeStr, 30, 229);
	
	stringstream reportStream;
	reportStream << "Zombies and stuff!" << endl
	<< "fps: " << ofGetFrameRate() << endl;
	ofDrawBitmapString(reportStream.str(),20,652);
}

void testApp::drawTest() {
	ofSetColor(255, 255, 255);
	
	string typeStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789,:&!?";
	
	ofSetColor(225);
	verdana14.drawString("Font Example - use keyboard to type", 30, 35);
	
	ofSetColor(245, 58, 135);
	verdana14.drawString("anti aliased", 145, 92);
	verdana14.drawString("anti aliased", 145, 195);
	
	ofSetColor(225);
	verdana14.drawString("verdana 14pt - ", 30, 92);
	verdana14.drawString(typeStr, 30, 111);
	
	ofRect(420, 97, 292, 62);
	ofSetColor(54, 54, 54);
	
	
	ofSetColor(29,29,29);
	ofLine(30, 169, ofGetWidth()-4, 169);
	
	ofSetColor(225);
	verdana14.drawString("verdana 30pt - ", 30, 195);
	verdana30.drawString(typeStr, 30, 229);
	
	stringstream reportStream;
	reportStream << "Zombies and stuff!" << endl
	<< "fps: " << ofGetFrameRate() << endl;
	ofDrawBitmapString(reportStream.str(),20,652);
}

void testApp::setState(int s) {
	state = s;
	
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
			
			zombiePoint = ofPoint(30 + floor(ofRandom(1) * 5) * 280, 500);
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

Score testApp::recordScore(bool hit) {
	Score score;
	score.hit = hit;
	score.difficulty = difficulty;
	score.time = ofGetSystemTime() - startTime;
	scores.push_back(score);
	
	return score;
}


/*
 Snippets:
 
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
 
 */