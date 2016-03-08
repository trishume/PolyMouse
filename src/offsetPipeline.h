// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "offsetTransformer.h"
#include "ofVec2f.h"

class offsetPipeline : public inputProcess<ofVec2f> {
public:
  offsetPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head);
  void setup();
  void update();
private:
  inputProcess<ofVec2f> *gazeInp;
  offsetTransformer headInp;
};
