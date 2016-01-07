//
//  offsetPipeline.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

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
