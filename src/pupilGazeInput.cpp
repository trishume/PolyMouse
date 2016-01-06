//
//  pupilGazeInput.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-06.
//
//

#include "pupilGazeInput.h"
#include "ofAppRunner.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

pupilGazeInput::pupilGazeInput() {}

void pupilGazeInput::setup() {
  cout << "connecting to server..." << endl;
  subscriber.connect("tcp://localhost:5000");
  cout << "connected" << endl;
}

void pupilGazeInput::update() {
  while (subscriber.hasWaitingMessage()) {
    ofBuffer data;
    subscriber.getNextMessage(data);

    // cout << "received data: " << data << endl;
    parsePacket(data.getText());
  }
}

bool pupilGazeInput::parsePacket(const string &s) {
  stringstream ss(s);
  string item;

  getline(ss, item);
  if(item != "Gaze") return false;

  while (getline(ss, item, ':')) {
    string valueForItem;
    getline(ss, valueForItem);
    if(item == "realtime gaze on screen") {
      ofVec2f fraction = parsePoint(valueForItem);
      val = ofVec2f(fraction.x * ofGetScreenWidth(), (1-fraction.y) * ofGetScreenHeight());
      cout << "gaze at " << valueForItem << ' ' << fraction << " = " << val << endl;
    }
  }

  return true;
}

ofVec2f pupilGazeInput::parsePoint(const string &s) {
  assert(s.size() > 3);
  stringstream ss(s.substr(1, s.size()-2));

  ofVec2f vec;
  char c;
  ss >> vec.x >> c >> vec.y;
  assert(c == ',');

  return vec;
}
