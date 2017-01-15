#include "ofMain.h"
#include "ofBitchSkeletonApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	ofSetupOpenGL( 1000,400, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new ofBitchSkeletonApp() );

}
