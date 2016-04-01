// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "smartHeadInput.h"
#include "ofAppRunner.h"
#include "ofxJSON.h"
#include <iostream>
#include <string>

using namespace std;

smartHeadInput::smartHeadInput() {}

void smartHeadInput::setup() {
  countNoChange = 0;
  cout << "connecting to head server..." << endl;
  subscriber.connect("tcp://localhost:5456");
  cout << "connected to head server" << endl;
}

void smartHeadInput::update() {
  while (subscriber.hasWaitingMessage()) {
    ofBuffer data;
    subscriber.getNextMessage(data);

    // cout << "received data: " << data << endl;
    string msg = data.getText();
    parsePacket(msg);
  }
}

bool smartHeadInput::parsePacket(const string &s) {
  ofxJSON json;
  json.parse(s);

  if(json.size() == 0) return false;

  ofVec2f pos(json["x"].asFloat(), json["y"].asFloat());
  val = (pos - last) * 0.2;

  if(pos == last) {
    countNoChange++;
  } else {
    countNoChange = 0;
  }
  userEngaged = (countNoChange < 30);
  last = pos;

  return true;
}
