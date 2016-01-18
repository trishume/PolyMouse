//
//  dlcTransformer.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-18.
//
//

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"

#include "macMouse.h"

#include <vector>

// Uses feedback from global mouse events to calibrate gaze position
// Assumes that when a mouse click happens and the gaze is close by
// the user was looking exactly at the cursor and the gaze point
// should have been there.
class dlcTransformer : public inputProcess<ofVec2f> {
public:
  dlcTransformer(inputProcess<ofVec2f> *inp);
  ~dlcTransformer();
  void setup();
  void update();

  void draw();
private:
  void newPoint(ofVec2f pt);

  inputProcess<ofVec2f> *inp;

  mouseMonitor mon;

  std::vector<ofVec2f> offsets;
  std::vector<bool> initialized;
};
