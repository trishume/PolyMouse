//
//  fixationTransformer.h
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-07.
//
//

#pragma once

#include "inputProcess.h"
#include "ofVec2f.h"

#include <string>
#include <deque>

// Passes through the gaze only when it is fixated (not moving in a saccade)
// Uses an algorithm based on I-DT from [Salvucci et al. 2000] but in real time
// and without an expanding window. This means a slow travelling gaze can be classified
// as a fixation the entire time it moves a long distance, but this is acceptable.
class fixationTransformer : public inputProcess<ofVec2f> {
public:
  fixationTransformer(inputProcess<ofVec2f> *inp, std::string name);
  void setup();
  void update();
private:
  inputProcess<ofVec2f> *inp;
  std::string name;

  // the window in seconds searched to check if dispersion is lower than
  // the dispersion maxVelocity would create over minFixationSeconds
  float minFixationSeconds;
  // the velocity in pixels per seconds below which movement can be considered fixated
  float maxVelocity;

  // stores old points for measuring past dispersion
  std::deque<ofVec2f> buffer;
};
