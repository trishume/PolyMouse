// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "pupilGazeInput.h"
#include "ofAppRunner.h"
#include "ofxJSON.h"
#include <iostream>
#include <string>

using namespace std;

pupilGazeInput::pupilGazeInput() {}

void pupilGazeInput::setup() {
  triggered = false;
  connected = false;
  screenW = ofGetScreenWidth();
  screenH = ofGetScreenHeight();

  cout << "sending port request ..." << endl;
  req.connect("tcp://localhost:50020");
  req.send("SUB_PORT");
}

void pupilGazeInput::connectBus(string port) {
  cout << "found server on port " << port << endl;
  string busAddress("tcp://localhost:");
  busAddress.append(port);
  subscriber.setFilter("gaze");
  subscriber.connect(busAddress);
  cout << "connected" << endl;
  connected = true;
}

void pupilGazeInput::update() {
  if(!connected) {
    if(req.hasWaitingMessage()) {
      string port;
      req.receive(port);
      connectBus(port);
    }
    return;
  }
  while (subscriber.hasWaitingMessage()) {
    ofBuffer data;
    subscriber.getNextMessage(data);

    // cout << "received data: " << data << endl;
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

  return true;
}
