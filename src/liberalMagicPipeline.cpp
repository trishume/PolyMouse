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

static const int kLiberalMagicMinimumJump = 200;

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
  if(val.squareDistance(gazeInp.val) > minJump*minJump) {
    val = gazeInp.val;
  }

  val += headInp.val; // use relative motion from head
}

void liberalMagicPipeline::draw() {
  ofSetColor(255, 0, 0);
  ofDrawCircle(gazeInp.val.x, gazeInp.val.y, 3);
  ofSetColor(0, 255, 0);
  ofDrawCircle(rawGaze->val.x, rawGaze->val.y, 2);
}
