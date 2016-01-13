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
  mousing = true;
}

//--------------------------------------------------------------
void ofApp::update(){
  pointer.update();
  if(mousing) moveMouseTo(pointer.val);
}

//--------------------------------------------------------------
void ofApp::draw(){
  transparent.update();
  ofSetColor(255, 0, 255);
  ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 25);

  ofPushMatrix();
  ofTranslate(-ofGetWindowPositionX(), -ofGetWindowPositionY());
  pointer.draw();
  ofDrawCircle(pointer.val.x, pointer.val.y, 5);
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'f') ofToggleFullscreen();
  if(key == 'm') mousing = !mousing;
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
