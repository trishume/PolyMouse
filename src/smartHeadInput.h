// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include "ofxZmq.h"

class smartHeadInput : public inputProcess<ofVec2f> {
public:
  smartHeadInput();
  void setup();
  void update();
  bool userEngaged;
private:
  bool parsePacket(const string &s);
  ofxZmqSubscriber subscriber;
  ofVec2f last;
  int countNoChange;
};
