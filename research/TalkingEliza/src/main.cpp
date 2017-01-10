#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	ofSetupOpenGL(680,800, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new testApp() );

}
