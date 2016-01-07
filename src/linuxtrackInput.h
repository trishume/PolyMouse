//
//  linuxtrackInput.hpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"

class linuxtrackInput : public inputProcess<ofVec2f> {
public:
  linuxtrackInput();
  void setup();
  void update();
};
