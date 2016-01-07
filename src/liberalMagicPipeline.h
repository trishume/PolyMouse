//
//  liberalMagicPipeline.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "diffTransformer.h"
#include "ofVec2f.h"

class liberalMagicPipeline : public inputProcess<ofVec2f> {
public:
  liberalMagicPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head);
  void setup();
  void update();
private:
  inputProcess<ofVec2f> *gazeInp;
  diffTransformer headInp;

  float minJump;
};
