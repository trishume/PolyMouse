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
  : inp(inp), name(name),
    cdMin(16.0, 10.0), cdMax(58.5, 72.0),
    vMin(0.0003,0.0004), vMax(0.0025, 0.0025),
    lambda(1000.0, 1000.0), ratio(0.7, 0.7) {}

void diffTransformer::setup() {
  RUI_NEW_GROUP(name+" head velocity");
  // RUI_SHARE_PARAM_WCN(name+" scale",scale, 0, 10000);
  // RUI_SHARE_PARAM_WCN(name+" exponent",exponent, 0, 5);
}

void diffTransformer::update() {
  ofVec2f prevVal = inp->val;
  inp->update();
  ofVec2f diff = inp->val - prevVal;

  float dt = ofGetLastFrameTime();
  ofVec2f vInf = ratio*(vMax - vMin) + vMin;
  ofVec2f v = diff*dt;

  for(unsigned i = 0; i < 2; ++i) {
    float exponent = -(lambda[i])*(abs(v[i])-vInf[i]);
    float cd = ((cdMax[i]-cdMin[i])/(1.0+exp(exponent)))+cdMin[i];
    val[i] = diff[i] * cd;
  }
  // cout << "raw diff: " << diff*dt << endl;
  cout << "diff: " << val << endl;
}
