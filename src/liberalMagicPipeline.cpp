//
//  liberalMagicPipeline.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "liberalMagicPipeline.h"
#include "ofxRemoteUIServer.h"

liberalMagicPipeline::liberalMagicPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : gazeInp(gaze), headInp(head, "head velocity"), minJump(150) {}

void liberalMagicPipeline::setup() {
  gazeInp->setup();
  headInp.setup();
  RUI_NEW_GROUP("Liberal MAGIC");
  RUI_SHARE_PARAM(minJump, 0, 800);
}

void liberalMagicPipeline::update() {
  gazeInp->update();
  headInp.update();

  // teleport to gaze if gaze is too far away
  if(val.squareDistance(gazeInp->val) > minJump*minJump) {
    val = gazeInp->val;
  }

  val += headInp.val; // use relative motion from head
}
