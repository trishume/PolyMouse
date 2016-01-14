//
//  animatedMagicPipeline.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "animatedMagicPipeline.h"
#include "ofxRemoteUIServer.h"
#include "ofGraphics.h"
#include <iostream>

static const int kAnimatedMagicMinimumJump = 100;
static const float kSpeedExpandFactor = 10000.0;
static const float kSmallJumpFactor = 0.75;
static const float kHeadSmoothingFactor = 0.2;
// TODO should be radians per second but I don't think it is
static const float kThrowThreshSpeed = 0.002;
// pixels per second
static const float kThrowSpeed = 2000;

animatedMagicPipeline::animatedMagicPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : rawGaze(gaze), headInp(head, "head velocity"), speedExpandFactor(kSpeedExpandFactor),
  gazeInp(gaze, "fixation detection"), minJump(kAnimatedMagicMinimumJump),
  smoothedHeadVel(0.0), headSmoothingFactor(kHeadSmoothingFactor),
  throwThreshSpeed(kThrowThreshSpeed), throwSpeed(kThrowSpeed) {}

void animatedMagicPipeline::setup() {
  gazeInp.setup();
  headInp.setup();
  RUI_NEW_GROUP("Animated MAGIC");
  RUI_SHARE_PARAM(minJump, 0, 800);
  RUI_SHARE_PARAM(speedExpandFactor, 0, 50000);
  RUI_SHARE_PARAM(headSmoothingFactor, 0, 1);
  RUI_SHARE_PARAM(throwThreshSpeed, 0, 0.01);
  RUI_SHARE_PARAM(throwSpeed, 0, 10000);
}

void animatedMagicPipeline::update() {
  gazeInp.update();
  headInp.update();

  // teleport to gaze if gaze is too far away
  // Note: cursor must also be away from the last teleport location
  smoothedHeadVel = smoothedHeadVel*(1-headSmoothingFactor) +
                    headInp.rawVel.length()*headSmoothingFactor;
  std::cout << smoothedHeadVel << std::endl;
  if(lookingFarAway() && smoothedHeadVel > throwThreshSpeed) {
    val = gazeInp.val;
    lastJumpDestination = gazeInp.val;
  }

  val += headInp.val; // use relative motion from head
}

void animatedMagicPipeline::draw() {
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
