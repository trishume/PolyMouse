#pragma once

#include "ofMain.h"

namespace _VampHost {
  namespace Vamp {
    class Plugin;
  };
};

class soundDetector {
public:
  soundDetector() = default;
  void setup(ofBaseApp *base);
  bool shouldMouseDown();
  bool shouldMouseUp();
  void draw();

  void audioIn(float * input, int bufferSize, int nChannels);
private:
  ofSoundStream *soundStream;
  _VampHost::Vamp::Plugin *popPlugin;
  _VampHost::Vamp::Plugin *tssPlugin;
  unsigned long long frame;
  bool doDown;
  bool doUp;
};
