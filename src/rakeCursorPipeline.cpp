// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#include "rakeCursorPipeline.h"
#include "ofxRemoteUIServer.h"
#include "ofGraphics.h"
#include <cmath>
#include <iostream>
using namespace std;

static const float kCursorSpacing = 300.0;
static const float kVerticalSpacingScale = 0.866025;

static float wrap(float x, float d) {
  if (x>=0)
    return fmod(x, d);
  else
    return fmod(x, d)+d;
}

template<typename Func>
static void allCursors(ofVec2f offset, float cursorSpacing, Func f) {
    const float dy = kVerticalSpacingScale*cursorSpacing;
    int screenH = ofGetScreenHeight();
    int screenW = ofGetScreenWidth();
    int shift = true;
    for(float y = offset.y - dy; y < screenH; y += dy) {
      float startShift = shift ? cursorSpacing/2 : 0;
      for(float x = offset.x - startShift; x < screenW; x += cursorSpacing) {
        if(x >= 0 && y >= 0) f(ofVec2f(x,y));
      }
      shift = !shift;
    }
}

rakeCursorPipeline::rakeCursorPipeline(inputProcess<ofVec2f> *gaze, inputProcess<ofVec2f> *head)
  : headInp(head, "rake"), gazeInp(gaze), cursorSpacing(kCursorSpacing) {}

void rakeCursorPipeline::setup() {
  gazeInp->setup();
  headInp.setup();
  RUI_NEW_GROUP("Rake Cursors");
  RUI_SHARE_PARAM(cursorSpacing, 0, 800);
}

void rakeCursorPipeline::update() {
  gazeInp->update();
  headInp.update();


  offset += headInp.val; // use relative motion from head
  offset.x = wrap(offset.x, cursorSpacing);
  offset.y = wrap(offset.y, kVerticalSpacingScale*cursorSpacing*2);
  // cout << headInp.val << ' ' << offset << endl;

  float closestDistSquared = 100000;
  ofVec2f closestCursor = offset;
  allCursors(offset, cursorSpacing, [&](ofVec2f p) {
    float distSquared = p.squareDistance(this->gazeInp->val);
    if(distSquared <= closestDistSquared) {
      closestDistSquared = distSquared;
      closestCursor = p;
    }
  });

  val = closestCursor;
}

void rakeCursorPipeline::draw() {
  ofSetColor(255,0,255);
  allCursors(offset, cursorSpacing, [](ofVec2f p) { ofDrawCircle(p.x,p.y,3); });
}
