//
//  fixationTransformer.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#include "fixationTransformer.h"
#include "ofxRemoteUIServer.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

static const int kFixationBufferSize = 16;

// these parameters are highly related
static const float kDefaultMinFixationSeconds = 0.05;
static const float kDefaultMaxVelocity = 200.0;

fixationTransformer::fixationTransformer(inputProcess<ofVec2f> *inp, std::string name)
  : inp(inp), name(name),
  minFixationSeconds(kDefaultMinFixationSeconds), maxVelocity(kDefaultMaxVelocity) {
  for(unsigned i = 0; i < kFixationBufferSize; ++i) {
    buffer.push_back(ofVec2f(0,0));
  }
}

void fixationTransformer::setup() {
  inp->setup();
  RUI_NEW_GROUP(name);
  RUI_SHARE_PARAM(minFixationSeconds, 0, 1.0);
  RUI_SHARE_PARAM(maxVelocity, 0, 2000.0);
}

void fixationTransformer::update() {
  inp->update();

  buffer.pop_front();
  buffer.push_back(inp->val);

  // NOTE: this assumes that past frames took around the same amount of time as this one
  float frameSeconds = ofGetLastFrameTime();
  if(frameSeconds == 0.0) return; // occurs on first frame
  int pastFramesToSample = round(minFixationSeconds / frameSeconds);

  if(pastFramesToSample > kFixationBufferSize) {
    cerr << "Warning: not enough fixation buffer, raise kFixationBufferSize" << endl;
    pastFramesToSample = kFixationBufferSize;
  }

  // compute dispersion for pastFramesToSample by the method from the I-DT algorithm
  auto minmaxX = minmax_element(buffer.end()-pastFramesToSample, buffer.end(),
    [](ofVec2f a, ofVec2f b){ return a.x < b.x; });
  auto minmaxY = minmax_element(buffer.end()-pastFramesToSample, buffer.end(),
    [](ofVec2f a, ofVec2f b){ return a.y < b.y; });
  float dispersion = (minmaxX.second->x - minmaxX.first->x) + (minmaxY.second->y - minmaxY.first->y);

  // update gaze point if it is fixated on something
  float maxDispersion = maxVelocity*minFixationSeconds;
  if(dispersion < maxDispersion) {
    val = inp->val;
  } else {
    // cout << "Filtered out saccade." << endl;
  }
}
