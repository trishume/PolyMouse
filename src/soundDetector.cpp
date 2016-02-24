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
static const int kTssDownOutput = 3;
static const int kTssUpOutput = 4;
static const int kScrollOnOutput = 3;
static const int kScrollOffOutput = 4;
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

  PluginLoader *loader = PluginLoader::getInstance();
  PluginLoader::PluginKey popKey = loader->composePluginKey("popclick", "popdetector");
  popPlugin = loader->loadPlugin(popKey, kSampleRate, PluginLoader::ADAPT_ALL);
  PluginLoader::PluginKey tssKey = loader->composePluginKey("popclick", "tssdetector");
  tssPlugin = loader->loadPlugin(tssKey, kSampleRate, PluginLoader::ADAPT_ALL);
  PluginLoader::PluginKey templateKey = loader->composePluginKey("popclick", "templatedetector");
  scrollDownPlugin = loader->loadPlugin(templateKey, kSampleRate, PluginLoader::ADAPT_ALL);

  scrollUpPlugin = loader->loadPlugin(templateKey, kSampleRate, PluginLoader::ADAPT_ALL);
  scrollUpPlugin->selectProgram("blow2");

  if (!popPlugin->initialise(1, kBufferSize, kBufferSize)) {
    cerr << "ERROR: Plugin pop initialise failed." << endl;
  }
  if (!tssPlugin->initialise(1, kBufferSize, kBufferSize)) {
    cerr << "ERROR: Plugin tss initialise failed." << endl;
  }
  if (!scrollDownPlugin->initialise(1, kBufferSize, kBufferSize)) {
    cerr << "ERROR: Plugin scrolldown initialise failed." << endl;
  }
  if (!scrollUpPlugin->initialise(1, kBufferSize, kBufferSize)) {
    cerr << "ERROR: Plugin scrolldown initialise failed." << endl;
  }
  initialized = true;
}

//--------------------------------------------------------------
bool soundDetector::shouldMouseDown() {
  if(doDown) {
    cerr << "Mouse down!" << endl;
    doDown = false;
    return true;
  }
  return false;
}

//--------------------------------------------------------------
bool soundDetector::shouldMouseUp() {
  if(doUp) {
    cerr << "Mouse up!" << endl;
    doUp = false;
    return true;
  }
  return false;
}

//--------------------------------------------------------------
void soundDetector::draw() {
}

void soundDetector::audioIn(float * input, int bufferSize, int nChannels) {
  if(!initialized) return;
  RealTime rt = RealTime::frame2RealTime(frame * kBufferSize, kSampleRate);

  Plugin::FeatureSet popFeatures = popPlugin->process(&input, rt);
  Plugin::FeatureSet tssFeatures = tssPlugin->process(&input, rt);
  Plugin::FeatureSet scrollDownFeatures = scrollDownPlugin->process(&input, rt);
  Plugin::FeatureSet scrollUpFeatures = scrollUpPlugin->process(&input, rt);
  if(!popFeatures[kPopInstantOutput].empty()) {
    doDown = true;
    doUp = true;
  }
  if(!tssFeatures[kTssDownOutput].empty()) {
    doDown = true;
  }
  if(!tssFeatures[kTssUpOutput].empty()) {
    doUp = true;
  }
  if(!scrollDownFeatures[kScrollOnOutput].empty()) {
    scrollDown = true;
  }
  if(!scrollDownFeatures[kScrollOffOutput].empty()) {
    scrollDown = false;
  }
  if(!scrollUpFeatures[kScrollOnOutput].empty()) {
    scrollUp = true;
  }
  if(!scrollUpFeatures[kScrollOffOutput].empty()) {
    scrollUp = false;
  }

  frame += 1;
}
