#include "soundDetector.h"

#include <vamp-hostsdk/PluginHostAdapter.h>
#include <vamp-hostsdk/PluginInputDomainAdapter.h>
#include <vamp-hostsdk/PluginLoader.h>

#include <iostream>

using namespace std;

using Vamp::Plugin;
using Vamp::PluginHostAdapter;
using Vamp::RealTime;
using Vamp::HostExt::PluginLoader;
using Vamp::HostExt::PluginWrapper;
using Vamp::HostExt::PluginInputDomainAdapter;

static const int kSampleRate = 44100;
static const int kPopInstantOutput = 7;
static const int kBufferSize = 512;

void soundDetector::setup(ofBaseApp *base) {
  ofSoundStream * soundStream = new ofSoundStream();
  soundStream->setup(base,                   // callback obj.
                     0,                      // out channels.
                     1,                      // in channels.
                     kSampleRate,            // sample rate.
                     kBufferSize,            // buffer size.
                     4);                     // number of buffers.
  this->soundStream = soundStream;

  frame = 0;
  doClick = false;
  PluginLoader *loader = PluginLoader::getInstance();
  PluginLoader::PluginKey key = loader->composePluginKey("popclick", "popdetector");
  plugin = loader->loadPlugin(key, kSampleRate, PluginLoader::ADAPT_ALL);

  if (!plugin->initialise(1, kBufferSize, kBufferSize)) {
    cerr << "ERROR: Plugin initialise failed." << endl;
  }
}

//--------------------------------------------------------------
bool soundDetector::shouldClick() {
  if(doClick) {
    cerr << "Pop!" << endl;
    doClick = false;
    return true;
  }
  return false;
}

//--------------------------------------------------------------
void soundDetector::draw() {
}

void soundDetector::audioIn(float * input, int bufferSize, int nChannels) {
  RealTime rt = RealTime::frame2RealTime(frame * kBufferSize, kSampleRate);
  Plugin::FeatureSet features = plugin->process(&input, rt);
  frame += 1;

  if(!features[kPopInstantOutput].empty()) {
    doClick = true;
  }
}
