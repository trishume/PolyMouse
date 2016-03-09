// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include "ofxZmq.h"

class pupilGazeInput : public inputProcess<ofVec2f> {
public:
  pupilGazeInput();
  void setup();
  void update();
private:
  bool parsePacket(const string &s);
  ofxZmqSubscriber subscriber;
  bool triggered;
  int screenW;
  int screenH;
};
