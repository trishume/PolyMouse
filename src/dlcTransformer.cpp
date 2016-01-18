//
//  dlcTransformer.cpp
//  PolyMouse
//
//  Created by Tristan Hume on 2016-01-18.
//
//

#include "dlcTransformer.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
using namespace std;

static const int kCellsX = 8;
static const int kCellsY = 6;
static const int kNumCells = kCellsX*kCellsY;
static const float kGarbageOffsetThresh = 200;

static ofVec2f cellPos(ofVec2f cellDim, int x, int y) {
  return ofVec2f(cellDim.x * (x+0.5), cellDim.y * (y+0.5));
}

static float safeInv(float x) {
  if(x == 0) {
    return 3.0;
  } else {
    return 1.0/x;
  }
}

dlcTransformer::dlcTransformer(inputProcess<ofVec2f> *inp)
  : inp(inp), offsets(kCellsX*kCellsY,ofVec2f(0,0)),
  initialized(kCellsX*kCellsY, false), mon() { }

dlcTransformer::~dlcTransformer() {
  stopMouseMonitor(mon);
}

void dlcTransformer::setup() {
  inp->setup();

  mon = addMouseMonitor([this](ofVec2f pt) {this->newPoint(pt);});
  cout << "Initialized DLC transformer" << endl;
}

void dlcTransformer::update() {
  inp->update();
  // cout << "Updating DLC transformer" << endl;

  ofVec2f cellDim(ofGetScreenWidth() / kCellsX, ofGetScreenHeight() / kCellsY);
  float totalDistance = 0.0;
  for(unsigned x = 0; x < kCellsX; ++x) {
    for(unsigned y = 0; y < kCellsY; ++y) {
      if(!initialized[x+y*kCellsX]) continue;
      totalDistance += safeInv(cellPos(cellDim, x, y).distance(inp->val));
    }
  }

  // nothing to calibrate if nothing initialized
  if(totalDistance == 0.0) {
    val = inp->val;
    return;
  }

  ofVec2f weightedOffset(0,0);
  for(unsigned x = 0; x < kCellsX; ++x) {
    for(unsigned y = 0; y < kCellsY; ++y) {
      if(!initialized[x+y*kCellsX]) continue;
      float invDist = safeInv(cellPos(cellDim, x, y).distance(inp->val));
      float weight = (invDist/totalDistance);
      weightedOffset += offsets[x+y*kCellsX]*weight;
    }
  }
  cout << "Total distance: " << totalDistance <<
    "Weighted offset: " << weightedOffset << endl;

  val = inp->val + weightedOffset;
}

void dlcTransformer::draw() {
  ofSetColor(255,0,0,150);
  ofVec2f cellDim(ofGetScreenWidth() / kCellsX, ofGetScreenHeight() / kCellsY);
  for(unsigned x = 0; x < kCellsX; ++x) {
    for(unsigned y = 0; y < kCellsY; ++y) {
      if(!initialized[x+y*kCellsX]) continue;
      ofVec2f pos = cellPos(cellDim, x, y);
      ofDrawCircle(pos.x,pos.y, 2);
      ofLine(pos, pos + offsets[x+y*kCellsX]);
    }
  }
  ofSetColor(100,0,0,255);
  ofDrawCircle(inp->val.x,inp->val.y, 5);
}

void dlcTransformer::newPoint(ofVec2f pt) {

  ofVec2f cellDim(ofGetScreenWidth() / kCellsX, ofGetScreenHeight() / kCellsY);
  int x = inp->val.x / cellDim.x;
  int y = inp->val.y / cellDim.y;

  ofVec2f offset = pt - inp->val;
  if(offset.length() < kGarbageOffsetThresh) {
    offsets[x + y*kCellsX] = offset;
    initialized[x + y*kCellsX] = true;
  }

  cout << "Got new point at " << pt << " while gaze at " << inp->val <<
    " yielding offset " << offset << endl;
}
