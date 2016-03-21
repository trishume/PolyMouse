// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include "udpGazeInput.h"

class udpHeadInput : public inputProcess<ofVec2f> {
public:
  udpHeadInput(udpGazeInput &udpInp);
  void setup();
  void update();
  void draw();
  bool userEngaged;
private:
  ofVec3f lastLeft;
  ofVec3f lastRight;
  udpGazeInput &udpInput;
};
