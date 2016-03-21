#pragma once

#include "ofMain.h"
#include "ofxTransparentWindow.h"

#include "inputProcess.h"
#include "pupilGazeInput.h"
#include "udpGazeInput.h"
#include "linuxtrackInput.h"
#include "udpHeadInput.h"
#include "lookMouseInput.h"
#include "dlcTransformer.h"
#include "freezeTransformer.h"
#include "offsetPipeline.h"
#include "liberalMagicPipeline.h"
#include "animatedMagicPipeline.h"
#include "rakeCursorPipeline.h"
#include "macMouse.h"

#include "soundDetector.h"

class ofApp : public ofBaseApp{

	public:
		ofApp();

		void setup();
		void update();
		void draw();

		void audioIn(float * input, int bufferSize, int nChannels);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxTransparentWindow transparent;

		pupilGazeInput rawGazeInp;
		// udpGazeInput rawGazeInp;
		dlcTransformer gazeInp;

		linuxtrackInput rawHeadInp;
		// udpHeadInput rawHeadInp;
		// lookMouseInput rawHeadInp;

		animatedMagicPipeline animatedPipeline;
		rakeCursorPipeline rakePipeline;
		liberalMagicPipeline liberalPipeline;
		offsetPipeline offPipeline;
		freezeTransformer pointer;

		soundDetector detector;
		mouseEventSource mouseSrc;

		bool mousing;
};
