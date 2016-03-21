// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "offsetPipeline.h"
#include "ofxRemoteUIServer.h"

offsetPipeline::offsetPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : gazeInp(gaze), headInp(head, "head-based offset") {}

void offsetPipeline::setup() {
  headInp.setup();
}

void offsetPipeline::update() {
  gazeInp->update();
  headInp.update();
  val = gazeInp->val + headInp.val;
}
