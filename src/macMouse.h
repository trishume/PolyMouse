// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

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

struct mouseEventSource {
  mouseEventSource();
  ~mouseEventSource();
  void *evtSrc;
};

void moveMouseTo(mouseEventSource &src, ofVec2f pt);
void mouseEventAtPoint(mouseEventSource &src, mouseButtonType btn, mouseEventType evt, ofVec2f pt);
void emitScrollEvent(mouseEventSource &src, int amount);
bool isMouseDown();

struct mouseMonitor {
  mouseMonitor() : globalMonitor(0), localMonitor(0) {}
  void *globalMonitor;
  void *localMonitor;
};

mouseMonitor addMouseMonitor(std::function<void(ofVec2f)> func);
void stopMouseMonitor(mouseMonitor mon);
