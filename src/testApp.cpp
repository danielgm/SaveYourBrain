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
	
	state = STATE_INTRO;
}

void testApp::update() {
	if (ofGetSystemTime() > deadline) {
		deadline = -1;
		
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
			zombieImage.draw(200, 200);
			break;
			
		case STATE_MISS:
			backgroundImage.draw(0, 0);
			break;
			
		case STATE_HIT:
			backgroundImage.draw(0, 0);
			break;
			
		case STATE_SCORE:
			break;
			
		default:;
	}
}

void testApp::exit() {
}

void testApp::keyPressed (int key) {
}

void testApp::mouseDragged(int x, int y, int button)
{}

void testApp::mousePressed(int x, int y, int button)
{}

void testApp::mouseReleased(int x, int y, int button) {
	switch (state) {
		case STATE_INTRO:
			state = STATE_READY;
			break;
		case STATE_READY:
			state = STATE_MISS;
			break;
		case STATE_ZOMBIE:
			if (hitZombie(mouseX, mouseY)) {
				
			}
			break;
		case STATE_MISS:
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
			break;
		case STATE_READY:
			// Set the deadline for when the next zombie appears.
			deadline = ofGetSystemTime() + 1200 + ofRandom(1) * 800;
			break;
		case STATE_ZOMBIE:
			// Set the deadline for when the zombie hides.
			deadline = ofGetSystemTime() + 200 + ofRandom(1) * 600;
			break;
		case STATE_MISS:
			// Set the deadline for when the "Missed!" message disappears.
			deadline = ofGetSystemTime() + 1200 + ofRandom(1) * 800;
			break;
		case STATE_HIT:
			// Set the deadline for when the "Hit!" message disappears.
			deadline = ofGetSystemTime() + 1200 + ofRandom(1) * 800;
			break;
		case STATE_SCORE:
			break;
	}
}

bool testApp::hitZombie(int x, int y) {
	return true;
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