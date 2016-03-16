// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "freezeTransformer.h"
#include "ofxRemoteUIServer.h"
#include "macMouse.h"
#include <iostream>
#include <cmath>
using namespace std;

static const uint64_t mouseFreezeMillis = 300ULL;

freezeTransformer::freezeTransformer(inputProcess<ofVec2f> *inp)
  : inp(inp) {}

void freezeTransformer::setup() {
  mouseWasUpLastFrame = true;
}

void freezeTransformer::update() {
  inp->update();

  bool pressed = isMouseDown();
  if(pressed && mouseWasUpLastFrame) {
    lastMouseDownTime = ofGetElapsedTimeMillis();
  }

  // only update position when unfrozen
  if(!pressed || ofGetElapsedTimeMillis() >= lastMouseDownTime+mouseFreezeMillis) {
    val = inp->val;
  }
  mouseWasUpLastFrame = !pressed;
}

void freezeTransformer::draw() {
  inp->draw();
}
