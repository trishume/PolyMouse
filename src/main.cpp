#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
  ofGLFWWindowSettings settings;

  settings.width = 1024;
  settings.height = 768;
  settings.resizable = true;
  // settings.doubleBuffering = false;
  shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	// ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
  shared_ptr<ofApp> mainApp(new ofApp());

  ofRunApp(mainWindow, mainApp);
  ofRunMainLoop();
}
