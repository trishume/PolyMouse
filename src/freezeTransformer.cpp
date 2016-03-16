// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "freezeTransformer.h"
#include "ofxRemoteUIServer.h"
#include <iostream>
#include <cmath>
using namespace std;

freezeTransformer::freezeTransformer(inputProcess<ofVec2f> *inp)
  : inp(inp) {}

void freezeTransformer::setup() {
}

void freezeTransformer::update() {
  inp->update();
  val = inp->val;
}

void freezeTransformer::draw() {
  inp->draw();
}
