// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "udpHeadInput.h"
#include "ofGraphics.h"

#include <iostream>
#include <cmath>

using namespace std;

udpHeadInput::udpHeadInput(udpGazeInput &udpInp) : userEngaged(false), udpInput(udpInp), lastLeft(0,0,0), lastRight(0,0,0) {}

void udpHeadInput::setup() {
}

void udpHeadInput::update() {
  ofVec3f zeros(0,0,0);

  ofVec3f leftDiff = udpInput.leftEye - lastLeft;
  ofVec3f rightDiff = udpInput.rightEye - lastRight;
  bool leftDead = udpInput.leftEye == zeros || lastLeft == zeros;
  bool rightDead = udpInput.rightEye == zeros || lastRight == zeros;

  if(leftDead && rightDead) {
    leftDiff = zeros;
    rightDiff = zeros;
  } else if(leftDead) {
    leftDiff = rightDiff;
  } else if(rightDead) {
    rightDiff = leftDiff;
  }

  ofVec3f avgDiff = (leftDiff + rightDiff) / 2.0f;
  val = ofVec2f(avgDiff.x, -avgDiff.y);

  userEngaged = udpInput.leftEye != zeros && udpInput.rightEye != zeros;

  lastLeft = udpInput.leftEye;
  lastRight = udpInput.rightEye;
}

void udpHeadInput::draw() {
  ofSetColor(0,255,0);
  ofDrawCircle(udpInput.leftEye.x+100, udpInput.leftEye.y+100, 3);
}
