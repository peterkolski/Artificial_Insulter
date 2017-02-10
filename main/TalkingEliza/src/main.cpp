#include "ofMain.h"
#include "ofBitchSkeletonApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	ofSetupOpenGL( 1500,800, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new ofBitchSkeletonApp() );

}
