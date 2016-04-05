// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "animatedMagicPipeline.h"
#include "ofxRemoteUIServer.h"
#include "ofGraphics.h"
#include "ofAppRunner.h"
#include <iostream>
#include <algorithm>

static const int kAnimatedMagicMinimumJump = 200;
static const float kSpeedExpandFactor = 10000.0;
static const float kSmallJumpFactor = 0.75;
static const float kHeadSmoothingFactor = 0.3;
// TODO should be radians per second but I don't think it is
static const float kThrowThreshSpeed = 0.001;
// pixels per second
static const float kThrowSpeed = 8000;

animatedMagicPipeline::animatedMagicPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : rawGaze(gaze), dlcGaze(gaze), headInp(head, "animated"), speedExpandFactor(kSpeedExpandFactor),
  gazeInp(&dlcGaze, "animated"), minJump(kAnimatedMagicMinimumJump),
  smoothedHeadVel(0.0), headSmoothingFactor(kHeadSmoothingFactor),
  throwThreshSpeed(kThrowThreshSpeed), throwSpeed(kThrowSpeed) {}

void animatedMagicPipeline::setup() {
  dlcGaze.setup();
  gazeInp.setup();
  headInp.setup();
  RUI_NEW_GROUP("Animated MAGIC");
  RUI_SHARE_PARAM(minJump, 0, 800);
  RUI_SHARE_PARAM(speedExpandFactor, 0, 50000);
  RUI_SHARE_PARAM(headSmoothingFactor, 0, 1);
  RUI_SHARE_PARAM(throwThreshSpeed, 0, 0.01);
  RUI_SHARE_PARAM(throwSpeed, 0, 50000);

  screenSize = ofGetWindowPtr()->getScreenSize();
}

void animatedMagicPipeline::update() {
  gazeInp.update();
  headInp.update();

  // teleport to gaze if gaze is too far away
  // Note: cursor must also be away from the last teleport location
  smoothedHeadVel = smoothedHeadVel*(1-headSmoothingFactor) +
                    headInp.rawVel.length()*headSmoothingFactor;
  // std::cout << smoothedHeadVel << std::endl;
  if(lookingFarAway() && smoothedHeadVel > throwThreshSpeed && !throwing) {
    throwing = true;
  }

  if(throwing) {
    double dt = ofGetLastFrameTime();
    double throwDist = (throwSpeed*dt);
    ofVec2f dirn = (gazeInp.val - val).getNormalized();
    if(val.distance(gazeInp.val)-minJump > throwDist) {
      val += dirn*throwDist;
    } else {
      lastJumpDestination = gazeInp.val;
      val = gazeInp.val + dirn*(-minJump);
      throwing = false;
    }
  }

  // use relative motion from head
  val = confineToScreen(val+headInp.val);
}

void animatedMagicPipeline::draw() {
  dlcGaze.draw();
  gazeInp.draw();

  ofSetColor(255,0,255);
  ofNoFill();
  float jumpRadius = calcJumpRadius();
  ofDrawCircle(lastJumpDestination.x, lastJumpDestination.y, jumpRadius*kSmallJumpFactor);
  ofDrawCircle(val.x, val.y, jumpRadius);
  ofFill();
}

float animatedMagicPipeline::calcJumpRadius() const {
  return minJump + smoothedHeadVel*speedExpandFactor;
}

bool animatedMagicPipeline::lookingFarAway() const {
  float jumpRadius = calcJumpRadius();
  float smallJump = jumpRadius*kSmallJumpFactor;
  return val.distance(gazeInp.val) > jumpRadius &&
     lastJumpDestination.distance(gazeInp.val) > smallJump;
}

ofVec2f animatedMagicPipeline::confineToScreen(ofVec2f pt) {
  pt.x = std::max(0.0f, std::min(screenSize.x, pt.x));
  pt.y = std::max(0.0f, std::min(screenSize.y, pt.y));
  return pt;
}
