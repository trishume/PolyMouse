// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include "ofxUDPManager.h"

// Recieves the UDP protocol sent by my Tobii EyeX DataShipper script
// found at: https://gist.github.com/trishume/b25492f25fc8ebe01dd9
class udpGazeInput : public inputProcess<ofVec2f> {
public:
  udpGazeInput();
  void setup();
  void update();
private:
  bool parsePacket(const string &s);
  ofxUDPManager udpConn;
};
