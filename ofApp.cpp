#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(0.5);
	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	for (int i = 0; i < 1000; i++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

		for (int k = 0; k < 100; k++) {

			auto location = glm::vec3(
				ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + k) * 0.005), 0, 1, -200, 200),
				ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + k) * 0.005), 0, 1, -200, 200),
				ofMap(ofNoise(noise_seed.z, (ofGetFrameNum() + k) * 0.005), 0, 1, -200, 200));
			auto next = glm::vec3(
				ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + k + 1) * 0.005), 0, 1, -200, 200),
				ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + k + 1) * 0.005), 0, 1, -200, 200),
				ofMap(ofNoise(noise_seed.z, (ofGetFrameNum() + k + 1) * 0.005), 0, 1, -200, 200));

			auto len = glm::length(location);
			auto next_len = glm::length(next);

			if (len < 130) { location = glm::normalize(location) * 130;	}
			if (len > 170) { location = glm::normalize(location) * 170; }
			if (next_len < 130) { next = glm::normalize(next) * 130; }
			if (next_len > 170) { next = glm::normalize(next) * 170; }

			ofSetColor(192, ofMap(k, 0, 100, 0, 255));
			ofDrawLine(location, next);
		}
	}
	this->cam.end();

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}