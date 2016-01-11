#include "ofApp.h"

#include "ofxRemoteUIServer.h"
#include "macMouse.h"

ofApp::ofApp() : pointer(&gazeInp, &ltrInp) {

}

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  ofEnableAlphaBlending();
//   ofSetVerticalSync(true);
  transparent.afterMainSetup(ofxTransparentWindow::SCREENSAVER);
  ofSetFullscreen(true);

  RUI_SETUP();

  pointer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
  pointer.update();
//  moveMouseTo(pointer.val);
}

//--------------------------------------------------------------
void ofApp::draw(){
  transparent.update();
  pointer.draw();
  ofSetColor(255, 0, 255);
  ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 25);
  ofDrawCircle(pointer.val.x, pointer.val.y, 5);
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
