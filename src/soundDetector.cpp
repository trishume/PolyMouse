#include "soundDetector.h"

void soundDetector::setup() {
    fftFile.setMirrorData(false);
    fftFile.setup();
    fftLive.setMirrorData(false);
    fftLive.setup();

    soundPlayer.loadSound("/Users/tristan/Music/popping.wav");
    soundPlayer.setLoop(true);
    soundPlayer.play();
}

//--------------------------------------------------------------
void soundDetector::update() {
    fftFile.update();
    fftLive.update();
}

//--------------------------------------------------------------
void soundDetector::draw() {
    ofSetColor(255);
    ofDrawBitmapString("AUDIO FROM MIC (LIVE)", 10, 20);
    ofDrawBitmapString("AUDIO FROM FILE (Popping)", 10, 310);

    fftLive.draw(10, 30);
    fftFile.draw(10, 320);
}
