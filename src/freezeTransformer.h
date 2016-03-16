// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include <cstdint>

class freezeTransformer : public inputProcess<ofVec2f> {
public:
  freezeTransformer(inputProcess<ofVec2f> *inp);
  void setup();
  void update();
  void draw();

  inputProcess<ofVec2f> *inp;
private:
  bool mouseWasUpLastFrame;
  uint64_t lastMouseDownTime;
};
