// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

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

  ofVec2f screenSize;
  ofVec2f confineToScreen(ofVec2f pt);
};
