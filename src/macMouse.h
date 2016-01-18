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

void moveMouseTo(ofVec2f pt);

struct mouseMonitor {
  mouseMonitor() : globalMonitor(0), localMonitor(0) {}
  void *globalMonitor;
  void *localMonitor;
};

mouseMonitor addMouseMonitor(std::function<void(ofVec2f)> func);
void stopMouseMonitor(mouseMonitor mon);
