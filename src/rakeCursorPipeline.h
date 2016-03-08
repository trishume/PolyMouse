// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "diffTransformer.h"
#include "fixationTransformer.h"
#include "ofVec2f.h"

class rakeCursorPipeline : public inputProcess<ofVec2f> {
public:
  rakeCursorPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head);
  void setup();
  void update();
  void draw(); // for debugging
private:
  inputProcess<ofVec2f> *gazeInp;
  diffTransformer headInp;

  float cursorSpacing;

  ofVec2f offset;
};
