//
//  zoomPipeline.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "fixationTransformer.h"
#include "ofVec2f.h"

class zoomPipeline : public inputProcess<ofVec2f> {
public:
  zoomPipeline(inputProcess<ofVec2f> *gaze);
  void setup();
  void update();
  void draw();
private:
  inputProcess<ofVec2f> *rawGaze;
  fixationTransformer gazeInp;

  float screenW;
  float screenH;
};
