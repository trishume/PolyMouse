//
//  pupilGazeInput.hpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-06.
//
//

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
  ofVec2f parsePoint(const string &s);
  ofxZmqSubscriber subscriber;
};
