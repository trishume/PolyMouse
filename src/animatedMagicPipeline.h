//
//  animatedMagicPipeline.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "diffTransformer.h"
#include "fixationTransformer.h"
#include "ofVec2f.h"

class animatedMagicPipeline : public inputProcess<ofVec2f> {
public:
  animatedMagicPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head);
  void setup();
  void update();
  void draw(); // for debugging
private:
  inputProcess<ofVec2f> *rawGaze;
  fixationTransformer gazeInp;
  diffTransformer headInp;

  float minJump;
  float speedExpandFactor;
  float headSmoothingFactor;

  float throwThreshSpeed;
  float throwSpeed;

  ofVec2f lastJumpDestination;
  float smoothedHeadVel;

  bool throwing;

  float calcJumpRadius() const;
  bool lookingFarAway() const;
};
