// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "pupilGazeInput.h"
#include "ofAppRunner.h"
#include "ofxJSON.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

pupilGazeInput::pupilGazeInput() {}

void pupilGazeInput::setup() {
  triggered = false;
  screenW = ofGetScreenWidth();
  screenH = ofGetScreenHeight();

  cout << "connecting to server..." << endl;
  subscriber.connect("tcp://localhost:5000");
  // subscriber.setFilter("gaze_positions");
  cout << "connected" << endl;
}

void pupilGazeInput::update() {
  while (subscriber.hasWaitingMessage()) {
    ofBuffer data;
    subscriber.getNextMessage(data);

    cout << "received data: " << data << endl;
    string msg = data.getText();
    if(msg == "gaze_positions") {
      triggered = true;
    } else if(triggered) {
      parsePacket(msg);
      triggered = false;
    }
  }
}

bool pupilGazeInput::parsePacket(const string &s) {
  ofxJSON json;
  json.parse(s);

  if(json.size() == 0) return false;
  auto coords = json[0]["realtime gaze on screen"];
  ofVec2f fraction(coords[0].asFloat(), coords[1].asFloat());
  val = ofVec2f(fraction.x * screenW, (1-fraction.y) * screenH);

  auto coords2 = json[0]["realtime corrected gaze on screen"];
  ofVec2f fraction2(coords2[0].asFloat(), coords2[1].asFloat());
  altVal = ofVec2f(fraction2.x * screenW, (1-fraction2.y) * screenH);

  return true;
}
