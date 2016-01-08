//
//  diffTransformer.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "diffTransformer.h"
#include "ofxRemoteUIServer.h"
#include <iostream>
using namespace std;

diffTransformer::diffTransformer(inputProcess<ofVec2f> *inp, std::string name)
  : inp(inp), name(name), scale(500) {}

void diffTransformer::setup() {
  inp->setup();
  RUI_NEW_GROUP(name);
  RUI_SHARE_PARAM(scale, 0, 1000);
}

void diffTransformer::update() {
  ofVec2f prevVal = inp->val;
  inp->update();
  ofVec2f diff = inp->val - prevVal;
  float dt = ofGetLastFrameTime();
  val = diff * dt * scale;
  // cout << "diff: " << val << endl;
}
