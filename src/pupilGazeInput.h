// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include "ofxZmq.h"

#include <string>

class pupilGazeInput : public inputProcess<ofVec2f> {
public:
  pupilGazeInput();
  void setup();
  void update();
private:
  bool parsePacket(const std::string &s);
  void connectBus(std::string port);
  ofxZmqSubscriber subscriber;
  ofxZmqRequest req;
  bool triggered;
  bool connected;
  int screenW;
  int screenH;
};
