#include "ofApp.h"

#include "ofxRemoteUIServer.h"
#include "macMouse.h"

#include <iostream>
using namespace std;

static const bool kOverlayUI = false;

ofApp::ofApp() : gazeInp(&rawGazeInp),
  animatedPipeline(&gazeInp, &ltrInp),
  rakePipeline(&gazeInp, &ltrInp),
  liberalPipeline(&gazeInp, &ltrInp),
  pointer(&animatedPipeline), detector() { }

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  ofEnableAlphaBlending();
//   ofSetVerticalSync(true);
  if(kOverlayUI) {
    transparent.afterMainSetup(ofxTransparentWindow::SCREENSAVER);
    ofSetFullscreen(true);
  }

  RUI_SETUP();


  rawGazeInp.setup();
  gazeInp.setup();
  ltrInp.setup();

  animatedPipeline.setup();
  rakePipeline.setup();
  liberalPipeline.setup();

  detector.setup(this);

  mousing = false;
}

//--------------------------------------------------------------
void ofApp::update(){
  pointer->update();
  if(ltrInp.userEngaged) {
    if(mousing) moveMouseTo(pointer->val);
    if(detector.shouldMouseDown()) {
      mouseEventAtPoint(kMouseButtonLeft, kEventMouseDown, pointer->val);
    }
    if(detector.shouldMouseUp()) {
      mouseEventAtPoint(kMouseButtonLeft, kEventMouseUp, pointer->val);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  if(kOverlayUI) transparent.update();
  ofSetColor(255, 0, 255);
  ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 25);
  if(!ltrInp.userEngaged) {
    ofDrawBitmapString("clicking disabled", 10, 45);
  }

  detector.draw();

  ofPushMatrix();
  ofTranslate(-ofGetWindowPositionX(), -ofGetWindowPositionY());
  if(pointer != &rakePipeline) gazeInp.draw();
  pointer->draw();
  if(!mousing) ofDrawCircle(pointer->val.x, pointer->val.y, 2);
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
  detector.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'f') ofToggleFullscreen();
  if(key == 'm') mousing = !mousing;

  if(key == 'r') {
    cout << "Rake cursor pipeline activated" << endl;
    pointer = &rakePipeline;
  }
  if(key == 'a') {
    cout << "Animated MAGIC pipeline activated" << endl;
    pointer = &animatedPipeline;
  }
  if(key == 'l') {
    cout << "Liberal MAGIC pipeline activated" << endl;
    pointer = &liberalPipeline;
  }
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
