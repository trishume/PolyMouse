//
//  diffTransformer.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"

#include <string>

class diffTransformer : public inputProcess<ofVec2f> {
public:
  diffTransformer(inputProcess<ofVec2f> *inp, std::string name);
  void setup();
  void update();

  ofVec2f rawVel;
private:
  inputProcess<ofVec2f> *inp;
  std::string name;

  ofVec2f cdMin;
  ofVec2f cdMax;
  ofVec2f vMin;
  ofVec2f vMax;
  ofVec2f lambda;
  ofVec2f ratio;
};
