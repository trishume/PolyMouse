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
#include <cmath>
using namespace std;

static const float kDefaultVelocityScale = 5000;
static const float kDefaultVelocityExponent = 1.5;

diffTransformer::diffTransformer(inputProcess<ofVec2f> *inp, std::string name)
  : inp(inp), name(name), scale(kDefaultVelocityScale), exponent(kDefaultVelocityExponent) {}

void diffTransformer::setup() {
  RUI_NEW_GROUP(name+" head velocity");
  RUI_SHARE_PARAM_WCN(name+" scale",scale, 0, 10000);
  RUI_SHARE_PARAM_WCN(name+" exponent",exponent, 0, 5);
}

void diffTransformer::update() {
  ofVec2f prevVal = inp->val;
  inp->update();
  ofVec2f diff = inp->val - prevVal;
  float dt = ofGetLastFrameTime();
  float magnitude = pow(diff.length(),exponent) * dt * scale;
  val = diff.getNormalized() * magnitude;
  rawVel = diff * dt;
  // cout << "diff: " << val << endl;
}
