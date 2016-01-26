#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxFFTFile.h"

class soundDetector {
public:
  soundDetector() = default;
  void setup();
  void update();
  void draw();
private:
  ofSoundPlayer soundPlayer;
  ofxFFTLive fftLive;
  ofxFFTFile fftFile;
};
