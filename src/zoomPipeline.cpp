//
//  zoomPipeline.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "zoomPipeline.h"
#include "ofGraphics.h"
#include "ofAppRunner.h"
#include "ofxDisplay.h"
#include <algorithm>

static const float confidentFraction = 0.18;

zoomPipeline::zoomPipeline(inputProcess<ofVec2f> *gaze)
  : rawGaze(gaze), gazeInp(gaze, "zoom"), zooming(0) {}

void zoomPipeline::setup() {
  gazeInp.setup();
  screenW = ofGetScreenWidth();
  screenH = ofGetScreenHeight();
  curImage.allocate(screenW*confidentFraction, screenH*confidentFraction, OF_IMAGE_COLOR_ALPHA);
//  curImage.clear();
}

void zoomPipeline::update() {
  gazeInp.update();
}

void zoomPipeline::trigger() {
  zooming = (zooming + 1) % 3;
  if(zooming) {
    ofxDisplay *disp = ofxDisplay::getMainDisplay();
    ofRectangle zoomRect = getZoomRect();
    disp->grabImage(curImage, zoomRect);
    delete disp;
  }
}

void zoomPipeline::draw() {
  if(zooming) {
    ofSetColor(255,255,255);
    curImage.draw(0,0,screenW, screenH);
  }

  gazeInp.draw();

  ofRectangle zoomRect = getZoomRect();
  ofSetColor(255,0,255);
  ofNoFill();
  ofDrawRectangle(zoomRect);
  ofFill();
}

ofRectangle zoomPipeline::getZoomRect() {
  ofRectangle zoomRect;
  zoomRect.setFromCenter(gazeInp.val, screenW * confidentFraction, screenH * confidentFraction);
  zoomRect.setX(std::min(screenW-(screenW*confidentFraction), std::max(0.0f, zoomRect.getX())));
  zoomRect.setY(std::min(screenH-(screenH*confidentFraction), std::max(0.0f, zoomRect.getY())));
  return zoomRect;
}
