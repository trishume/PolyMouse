//
//  offsetPipeline.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "offsetPipeline.h"
#include "ofxRemoteUIServer.h"

offsetPipeline::offsetPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : gazeInp(gaze), headInp(head, "head-based offset") {}

void offsetPipeline::setup() {
  gazeInp->setup();
  headInp.setup();
}

void offsetPipeline::update() {
  gazeInp->update();
  headInp.update();
  val = gazeInp->val + headInp.val;
}
