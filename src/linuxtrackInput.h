// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"

class linuxtrackInput : public inputProcess<ofVec2f> {
public:
  linuxtrackInput();
  void setup();
  void update();
  bool userEngaged;
private:
  ofVec2f last;
  int countNoChange;
};
