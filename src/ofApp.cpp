#include "ofApp.h"

#include "ofxRemoteUIServer.h"

#include <iostream>
using namespace std;

static const bool kOverlayUI = false;

ofApp::ofApp() : gazeInp(&rawGazeInp),
  animatedPipeline(&gazeInp, &ltrInp),
  rakePipeline(&gazeInp, &ltrInp),
  liberalPipeline(&gazeInp, &ltrInp),
  offPipeline(&gazeInp, &ltrInp),
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
  offPipeline.setup();

  detector.setup(this);

  mousing = false;
}

//--------------------------------------------------------------
void ofApp::update(){
  pointer.update();
  if(ltrInp.userEngaged && mousing) {
    moveMouseTo(mouseSrc, pointer.val);
    if(detector.shouldMouseDown()) {
      mouseEventAtPoint(mouseSrc, kMouseButtonLeft, kEventMouseDown, pointer.val);
    }
    if(detector.shouldMouseUp()) {
      mouseEventAtPoint(mouseSrc, kMouseButtonLeft, kEventMouseUp, pointer.val);
    }
    if(detector.scrollDown) {
      emitScrollEvent(mouseSrc, -20);
    }
    if(detector.scrollUp) {
      emitScrollEvent(mouseSrc, 20);
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
  if(!detector.enableSounds) {
    ofDrawBitmapString("sounds disabled", 10, 85);
  }
  if(detector.enableExtraSounds) {
    ofDrawBitmapString("extra sounds enabled", 10, 105);
  }

  detector.draw();

  ofPushMatrix();
  ofTranslate(-ofGetWindowPositionX(), -ofGetWindowPositionY());
  if(pointer.inp != &rakePipeline) gazeInp.draw();
  pointer.draw();
  if(!mousing) ofDrawCircle(pointer.val.x, pointer.val.y, 2);
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
  if(key == 's') detector.enableSounds = !detector.enableSounds;
  if(key == 'e') detector.enableExtraSounds = !detector.enableExtraSounds;

  if(key == 'r') {
    cout << "Rake cursor pipeline activated" << endl;
    pointer.inp = &rakePipeline;
  }
  if(key == 'a') {
    cout << "Animated MAGIC pipeline activated" << endl;
    pointer.inp = &animatedPipeline;
  }
  if(key == 'l') {
    cout << "Liberal MAGIC pipeline activated" << endl;
    pointer.inp = &liberalPipeline;
  }
  if(key == 'o') {
    cout << "Offset pipeline activated" << endl;
    pointer.inp = &offPipeline;
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
