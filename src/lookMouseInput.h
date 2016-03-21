// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"
#include "ofSerial.h"
#include <string>

static const int kLookMouseBufferSize = 256;

class lookMouseInput : public inputProcess<ofVec2f> {
public:
  lookMouseInput();
  void setup();
  void update();
  bool userEngaged;
private:
  ofVec2f last;
  ofSerial serial;
  unsigned char buffer[kLookMouseBufferSize];

  bool parsePacket(const std::string &packet);
};
