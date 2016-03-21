// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "lookMouseInput.h"
#include "linuxtrack.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include "ofxJSON.h"

using namespace std;

static int seekBack(unsigned char *buffer, int end) {
  for(int i = end-1; i >= 0; --i) {
    if(buffer[i] == '\n') {
      return i;
    }
  }
  return -1;
}

lookMouseInput::lookMouseInput() : userEngaged(false) {}

void lookMouseInput::setup() {
  cout << "Initializing lookmouse ... " << endl;

  // initialize buffer with non-newlines
  for(unsigned i = 0; i < kLookMouseBufferSize; ++i) {
    buffer[i] = '.';
  }

  serial.listDevices();
  vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
  for(auto&& d : deviceList) {
    cout << d.getDeviceName() << " " << d.getDeviceID() << endl;
  }

  serial.setup("cu.usbmodem1141211", 57600);
}

void lookMouseInput::update() {
  serial.writeByte('c'); // add credit

  unsigned char tempBuffer[kLookMouseBufferSize];
  int toRead = serial.available();
  while(toRead > 0) {
    int countRead = serial.readBytes(tempBuffer, min(kLookMouseBufferSize,toRead));
    toRead -= countRead;

    int toMove = kLookMouseBufferSize - countRead;
    std::memmove(buffer, buffer+countRead, toMove);
    std::memcpy(buffer+toMove, tempBuffer, countRead);
  }

  int lastLineEnd = seekBack(buffer, kLookMouseBufferSize);
  if(lastLineEnd < 0) return; // no last line
  int lastLineStart = seekBack(buffer, lastLineEnd);
  if(lastLineStart < 0) return; // no full line
  string line = string((const char*)(buffer+lastLineStart+1), lastLineEnd-lastLineStart-2);

  // cout << '>' << line << '|' << endl;
  if(!line.empty() && line[0] == '{') {
    parsePacket(line);
  }
}

bool lookMouseInput::parsePacket(const string &s) {
  ofxJSON json;
  json.parse(s);

  if(json.size() == 0 || !json.isMember("orient")) return false;
  auto coords = json["orient"];

  float compensation = coords[1].asFloat() * coords[2].asFloat() * -(1.0/90.0);
  ofVec2f orientation(coords[0].asFloat()+compensation, coords[1].asFloat() * -1);
  val = orientation - last;
  // cout << "head pose: " << val << endl;

  userEngaged = true;
  last = orientation;
}
