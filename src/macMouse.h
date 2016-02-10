//
//  macMouse.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-11.
//
//

#pragma once

#include "ofVec2f.h"
#include <functional>

enum mouseButtonType {
  kMouseButtonLeft = 0,
  kMouseButtonRight = 1
};

enum mouseEventType {
  kEventMouseDown = 0,
  kEventMouseUp = 1
};

void moveMouseTo(ofVec2f pt);
void mouseEventAtPoint(mouseButtonType btn, mouseEventType evt, ofVec2f pt);

struct mouseMonitor {
  mouseMonitor() : globalMonitor(0), localMonitor(0) {}
  void *globalMonitor;
  void *localMonitor;
};

mouseMonitor addMouseMonitor(std::function<void(ofVec2f)> func);
void stopMouseMonitor(mouseMonitor mon);
