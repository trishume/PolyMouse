// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "pupilGazeInput.h"
#include "ofAppRunner.h"
#include "ofxJSON.h"
#include "msgpack.hpp"
#include "form.hpp"
// #include "json.hpp"
#include <iostream>
#include <string>
#include <sstream>

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
  subscriber.setFilter("surface");
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
    string data;
    subscriber.getNextMessage(data);

    if(data == "surface") {
      triggered = true;
    } else if(triggered) {
      parsePacket(data);
      triggered = false;
    }
  }
}

bool pupilGazeInput::parsePacket(const string &s) {
  // cout << "received data: " << s << endl;
  std::istringstream inbuf(s);
  goodform::variant var;
  goodform::msgpack::deserialize(inbuf, var);
  // goodform::json::serialize(var, cout);
  goodform::form form(var);

  auto coords = form.at("gaze_on_srf").at(0);
  if(!form.is_good()) return false;

  ofVec2f fraction(coords.at(0).float32().val(), coords.at(1).float32().val());
  val = ofVec2f(fraction.x * screenW, (1-fraction.y) * screenH);
  // cout << "got coords " << val << endl;

  return true;
}
