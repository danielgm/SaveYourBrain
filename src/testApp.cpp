#include "testApp.h"
//#include "Leap.h"

//using namespace Leap;

void testApp::setup() {
	//ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	
	leap.open();
	
	//old OF default is 96 - but this results in fonts looking larger than in other programs.
	ofTrueTypeFont::setGlobalDpi(72);
	
	amplitudeBook14.loadFont("Amplitude-Book.ttf", 30, true, true);
	amplitudeBook14.setLineHeight(18.0f);
	amplitudeBook14.setLetterSpacing(1.037);
	
	amplitudeBook30.loadFont("Amplitude-Book.ttf", 60, true, true);
	amplitudeBook30.setLineHeight(18.0f);
	amplitudeBook30.setLetterSpacing(1.037);
	
	verdana14.loadFont("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
	
	verdana30.loadFont("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
	
	// Load slides.
	introImage.loadImage("saveyourbrain.png");
	backgroundImage.loadImage("saveyourbrainbg.jpg");
	scoreBackgroundImage.loadImage("saveyourbrainscorebg.png");
	zombieImage.loadImage("zombie_normal.png");
	zombieHitImage.loadImage("zombie_hit.png");
	hitImage.loadImage("hit.png");
	missImage.loadImage("miss.png");
	
	themeSound.loadSound("theme.wav");
	arghSound1.loadSound("arggggh.mp3");
	arghSound2.loadSound("arggggh2.mp3");
	brainsSound.loadSound("brains.mp3");
	hitSound.loadSound("blast.mp3");
	missSound.loadSound("miss.mp3");
	painSound.loadSound("pain.mp3");
	
	setState(STATE_INTRO);
	difficulty = DIFFICULTY_EASY;
	
	mute = false;
	
	calibrationMinX = -700;
	calibrationMaxX = 700;
	calibrationMinY = 500;
	calibrationMaxY = -500;
	screenWidth = 1440;
	screenHeight = 900;
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
				setState(STATE_HIT_MESSAGE);
				break;
			case STATE_HIT_MESSAGE:
				if (hits.size() > 4) {
					setState(STATE_SCORE);
				}
				else {
					setState(STATE_READY);
				}
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
			case STATE_HIT_MESSAGE:
				break;
			case STATE_SCORE:
				break;
		}
	}
	
    simpleHands = leap.getSimpleHands();
    
    if (leap.isFrameNew() && simpleHands.size()) {
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
		
		hasFingers = false;
        for(int i = 0; i < simpleHands.size(); i++){
            for(int j = 0; j < simpleHands[i].fingers.size(); j++){
                int id = simpleHands[i].fingers[j].id;
				cout << leapPoint.y << endl;
				// pt.x range is ±700
				// pt.y doesn't matter
				// pt.z is a click when < -200
				leapPoint = simpleHands[i].fingers[j].pos;
				if (leapPoint.z < -200) {
					if (!fingerClicking) {
						cout << "Fingered!" << endl;
						switch (state) {
							case STATE_INTRO:
								setState(STATE_READY);
								break;
								
							case STATE_READY:
								break;
								
							case STATE_ZOMBIE:
								if (hitZombie(ofMap(leapPoint.x, calibrationMinX, calibrationMaxX, 0, screenWidth), ofMap(leapPoint.y, calibrationMinY, calibrationMaxY, 0, screenHeight), true)) {
									setState(STATE_HIT);
									recordHit();
								}
								else {
									setState(STATE_MISS);
									recordMiss();
								}
								break;
								
							case STATE_HIT:
								break;
								
							case STATE_HIT_MESSAGE:
								break;
								
							case STATE_MISS:
								break;
								
							case STATE_SCORE:
								hits.clear();
								misses.clear();
								
								setState(STATE_READY);
								break;
						}
						fingerClicking = true;
					}
				}
				else {
					fingerClicking = false;
				}
				
				hasFingers = true;
            }
        }
    }
	
	leap.markFrameAsOld();
}

void testApp::draw() {
	ofBackground(0);
	ofSetColor(255);
	
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

			if (hasFingers) {
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofMap(leapPoint.x, calibrationMinX, calibrationMaxX, 0, screenWidth),
						 ofMap(leapPoint.y, calibrationMinY, calibrationMaxY, 0, screenHeight), 20);
			}
			break;
			
		case STATE_MISS:
			backgroundImage.draw(0, 0);
			zombieImage.draw(zombiePoint.x, zombiePoint.y);
			missImage.draw(hitPoint.x, hitPoint.y);
			break;
			
		case STATE_HIT:
			backgroundImage.draw(0, 0);
			zombieHitImage.draw(zombiePoint.x, zombiePoint.y + 8); // Alignment quickfix.
			hitImage.draw(hitPoint.x, hitPoint.y);
			amplitudeBook30.drawString(ofToString(floor(latestScore.time)) + " ms", 20, 60);
			break;
			
		case STATE_HIT_MESSAGE:
			backgroundImage.draw(0, 0);
			hitImage.draw(hitPoint.x, hitPoint.y);
			amplitudeBook30.drawString(ofToString(floor(latestScore.time)) + " ms", 20, 60);
			break;
			
		case STATE_SCORE:
			scoreBackgroundImage.draw(0,0);
			amplitudeBook14.drawString("Average Reaction Time", 580, 200);
			amplitudeBook30.drawString(ofToString(floor(getAverageHitTimes())) + " ms", 620, 270);
			zombieHitImage.draw(1000, 500);
			break;
	}
}

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
			
		case 'm':
			mute = !mute;
			cout << (mute ? "Muted." : "Unmuted.") << endl;
			break;
	}
}

void testApp::mouseDragged(int x, int y, int button) {
}

void testApp::mousePressed(int x, int y, int button) {
}

void testApp::mouseReleased(int x, int y, int button) {
	switch (state) {
		case STATE_INTRO:
			// Play the "brains" sound here so it only happens the first time.
			if (!mute) {
				themeSound.stop();
				brainsSound.play();
			}
			setState(STATE_READY);
			break;
		case STATE_READY:
			setState(STATE_MISS);
			break;
		case STATE_ZOMBIE:
			if (hitZombie(mouseX, mouseY, false)) {
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
			hits.clear();
			misses.clear();
			
			setState(STATE_READY);
			break;
	}
}

void testApp::windowResized(int w, int h) {
}

void testApp::setState(int s) {
	state = s;
	
	float offset, r;
	
	switch (state) {
		case STATE_INTRO:
			cout << "STATE_INTRO" << endl;
			themeSound.play();
			break;
			
		case STATE_READY:
			cout << "STATE_READY" << endl;
			// Set the deadline for when the next zombie appears.
			deadline = ofGetSystemTime() + 200 + ofRandom(1) * 800;
			break;
			
		case STATE_ZOMBIE:
			cout << "STATE_ZOMBIE" << endl;
			
			if (!mute) {
				r = ofRandom(1);
				if (r < 0.2) {
					arghSound1.play();
				}
				else if (r < 0.4) {
					arghSound2.play();
				}
			}
			
			if (difficulty == DIFFICULTY_HARD) {
				// Set the deadline for when the zombie hides.
				deadline = ofGetSystemTime() + 500 + ofRandom(1) * 1500;
			}
			else {
				// No deadline for other difficulties.
				deadline = -1;
			}
			
			offset = floor(ofRandom(1) * 6);
			zombiePoint = ofPoint(30 + offset * 180, 220);
			hitPoint = ofPoint(190 + offset * 180, 30);
			missPoint = ofPoint(190 + offset * 180, 30);
			
			startTime = ofGetSystemTime();
			break;
			
		case STATE_MISS:
			cout << "STATE_MISS" << endl;
			if (!mute) {
				missSound.play();
			}
			
			// Set the deadline for when the "Missed!" message disappears.
			deadline = ofGetSystemTime() + 1000;
			break;
			
		case STATE_HIT:
			cout << "STATE_HIT" << endl;
			if (!mute) {
				hitSound.play();
			}
			
			// Set the deadline for when the hit zombie disappears.
			deadline = ofGetSystemTime() + 600;
			break;
			
		case STATE_HIT_MESSAGE:
			cout << "STATE_HIT_MESSAGE" << endl;
			// Set the deadline for when the "Hit!" message disappears.
			deadline = ofGetSystemTime() + 1200;
			break;
			
		case STATE_SCORE:
			cout << "STATE_SCORE" << endl;
			if (!mute) {
				painSound.play();
			}
			break;
	}
}

bool testApp::hitZombie(int x, int y, bool isLeap) {
	return zombiePoint.x < x && x < zombiePoint.x + zombieImage.width
		&& (isLeap || (zombiePoint.y < y && y < zombiePoint.y + zombieImage.height));
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