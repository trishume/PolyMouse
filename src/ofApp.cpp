#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  transparent.afterMainSetup(ofxTransparentWindow::SCREENSAVER);
  ofSetFullscreen(true);

  gazeInp.setup();
  headInp.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
  transparent.update();
  gazeInp.update();
  headInp.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  transparent.update();
  ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 25);
  ofSetColor(255, 0, 255);
  ofDrawCircle(gazeInp.val.x, gazeInp.val.y, 5);
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