#pragma once

#include "ofMain.h"
#include "ofxTransparentWindow.h"

#include "pupilGazeInput.h"
#include "linuxtrackInput.h"
#include "offsetPipeline.h"
#include "liberalMagicPipeline.h"
#include "animatedMagicPipeline.h"
#include "rakeCursorPipeline.h"

class ofApp : public ofBaseApp{

	public:
		ofApp();

		void setup();
		void update();
		void draw();

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

		pupilGazeInput gazeInp;
		linuxtrackInput ltrInp;
		animatedMagicPipeline pointer;

		bool mousing;
};
