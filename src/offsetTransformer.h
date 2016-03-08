// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

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
