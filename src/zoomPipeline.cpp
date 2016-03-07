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
#include <algorithm>

static const float confidentFraction = 0.18;

zoomPipeline::zoomPipeline(inputProcess<ofVec2f> *gaze)
  : rawGaze(gaze), gazeInp(gaze, "zoom") {}

void zoomPipeline::setup() {
  gazeInp.setup();
  screenW = ofGetScreenWidth();
  screenH = ofGetScreenHeight();
}

void zoomPipeline::update() {
  gazeInp.update();
  val = gazeInp.val;
}

void zoomPipeline::draw() {
  gazeInp.draw();

  ofRectangle zoomRect;
  zoomRect.setFromCenter(val, screenW * confidentFraction, screenH * confidentFraction);
  zoomRect.setX(std::min(screenW-(screenW*confidentFraction), std::max(0.0f, zoomRect.getX())));
  zoomRect.setY(std::min(screenH-(screenH*confidentFraction), std::max(0.0f, zoomRect.getY())));
  ofLog() << zoomRect;
  ofSetColor(255,0,255);
  ofNoFill();
  ofDrawRectangle(zoomRect);
  ofFill();
}
