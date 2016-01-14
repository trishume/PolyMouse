//
//  rakeCursorPipeline.h
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

class rakeCursorPipeline : public inputProcess<ofVec2f> {
public:
  rakeCursorPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head);
  void setup();
  void update();
  void draw(); // for debugging
private:
  fixationTransformer gazeInp;
  diffTransformer headInp;

  float cursorSpacing;

  ofVec2f offset;
};
