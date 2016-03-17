// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "udpGazeInput.h"
#include "ofAppRunner.h"
#include "ofxJSON.h"
#include <iostream>
#include <string>

using namespace std;

udpGazeInput::udpGazeInput() {}

void udpGazeInput::setup() {
  udpConn.Create();
  udpConn.Bind(11249);
  udpConn.SetNonBlocking(true);
}

void udpGazeInput::update() {
  char udpMessage[2000];
  int recieved;
  do {
   recieved = udpConn.Receive(udpMessage,2000);
   if(recieved != 0) parsePacket(udpMessage);
  } while(recieved != 0);
}

bool udpGazeInput::parsePacket(const string &s) {
  ofxJSON json;
  json.parse(s);

  if(json.size() == 0) return false;

  if(json.isMember("gaze")) {
    // cout << s << endl;
    auto coords = json["gaze"];
    val = ofVec2f(coords[0].asFloat(), coords[1].asFloat());
  }

  return true;
}
