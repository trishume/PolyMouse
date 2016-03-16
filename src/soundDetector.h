// PolyMouse
// Copyright (C) 2016  Tristan Hume
// Released under the GPLv3, see the LICENSE file for the full text

#pragma once

#include "ofMain.h"

namespace _VampHost {
  namespace Vamp {
    class Plugin;
  };
};

class soundDetector {
public:
  soundDetector() : frame(0), doDown(false), doUp(false), scrollDown(false), initialized(false) {}
  void setup(ofBaseApp *base);
  bool shouldMouseDown();
  bool shouldMouseUp();
  void draw();
  bool scrollDown;
  bool scrollUp;

  void audioIn(float * input, int bufferSize, int nChannels);

  bool enableSounds;
  bool enableExtraSounds;
private:
  ofSoundStream *soundStream;
  _VampHost::Vamp::Plugin *popPlugin;
  _VampHost::Vamp::Plugin *tssPlugin;
  _VampHost::Vamp::Plugin *scrollDownPlugin;
  _VampHost::Vamp::Plugin *scrollUpPlugin;
  unsigned long long frame;
  bool doDown;
  bool doUp;
  bool initialized;
};
