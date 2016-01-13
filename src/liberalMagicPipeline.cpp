//
//  liberalMagicPipeline.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "liberalMagicPipeline.h"
#include "ofxRemoteUIServer.h"
#include "ofGraphics.h"

static const int kLiberalMagicMinimumJump = 150;
static const float kSmallJumpFactor = 0.75;

liberalMagicPipeline::liberalMagicPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : rawGaze(gaze), headInp(head, "head velocity"),
  gazeInp(gaze, "fixation detection"), minJump(kLiberalMagicMinimumJump) {}

void liberalMagicPipeline::setup() {
  gazeInp.setup();
  headInp.setup();
  RUI_NEW_GROUP("Liberal MAGIC");
  RUI_SHARE_PARAM(minJump, 0, 800);
}

void liberalMagicPipeline::update() {
  gazeInp.update();
  headInp.update();

  // teleport to gaze if gaze is too far away
  // Note: cursor must also be away from the last teleport location
  float smallJump = minJump*0.75;
  if(val.squareDistance(gazeInp.val) > minJump*minJump &&
     lastJumpDestination.squareDistance(gazeInp.val) > (smallJump*smallJump)) {
    val = gazeInp.val;
    lastJumpDestination = gazeInp.val;
  }

  val += headInp.val; // use relative motion from head
}

void liberalMagicPipeline::draw() {
  gazeInp.draw();

  ofSetColor(255,0,255);
  ofNoFill();
  ofDrawCircle(lastJumpDestination.x, lastJumpDestination.y, minJump*kSmallJumpFactor);
  ofDrawCircle(val.x, val.y, minJump);
  ofFill();
}
