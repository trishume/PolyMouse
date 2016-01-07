//
//  offsetTransformer.hpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"

#include <string>

class offsetTransformer : public inputProcess<ofVec2f> {
public:
  offsetTransformer(inputProcess<ofVec2f> *inp, std::string name);
  void setup();
  void update();

  void recenter();
private:
  inputProcess<ofVec2f> *inp;
  std::string name;

  ofVec2f center;
  float scale;
};
