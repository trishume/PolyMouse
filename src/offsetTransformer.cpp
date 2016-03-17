// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "offsetTransformer.h"
#include "ofxRemoteUIServer.h"
#include <iostream>
using namespace std;

offsetTransformer::offsetTransformer(inputProcess<ofVec2f> *inp, std::string name)
  : inp(inp), name(name), scale(20.0) {}

void offsetTransformer::setup() {
  recenter();

  RUI_NEW_GROUP(name);
  RUI_SHARE_PARAM(scale, 0, 50);
  RUI_SHARE_PARAM(center.x, -50, 50);
  RUI_SHARE_PARAM(center.y, -50, 50);
}

void offsetTransformer::update() {
  inp->update();
  ofVec2f offset = inp->val - center;
  val = offset * scale;
  // cout << "offset: " << val << endl;
}

void offsetTransformer::recenter() {
  center = inp->val;
}
