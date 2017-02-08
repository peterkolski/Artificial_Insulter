#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    setVoice( );
    ofSetLogLevel( OF_LOG_VERBOSE );
    ofEnableAlphaBlending();

//    string settingsPath = ofFilePath1.getCurrentWorkingDirectory() + "../../../data/settings.txt";
    string settingsPath = "/Users/sonneundasche/programming/of/apps/ElisaKora/bin/data/settings.txt";
    ofLogNotice() << settingsPath;
    if (!xml.loadFile( settingsPath ) )
    {
        ofLogError() << "No XML file loaded";
    }

    imageNamePath = xml.getValue( "PATH:SAVEPIC", "../out.jpg" );
    ofLogNotice() << "Path to write file" << imageNamePath;

    textCurrent = bitches.getAnswerCurrent();

    setupOSC();

    int camWidth;
    int camHeight;
    setupVideo( camWidth, camHeight );
    setupWarping( camWidth / 2, camHeight / 2, 10, 10, ofGetWidth() / 2, 10 );

    bitches.doConversation( "I hate you all", 0 );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::update(){
    vidPlayerLeft.update();
    vidPlayerRight.update();
    vidGrabber.update();
    speak( );
    bitches.recieveText();
    //TODO HACK
//    if(ofGetFrameNum() % 5 != 0) {
//        // only update every 5 frames.
//        return;
//    }
//    if ( ( ofGetFrameNum() % ( 60*10) ) == 0 )
//    {
//        processImage();
////        bitchElisa.update();
//    }
//    if ( ( ofGetFrameNum() % ( 60*5) ) == 0 )
//    {
////        processImage();
//        bitchElisa.update();
//    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::draw(){
    ofBackground( 0 );

    drawActiveSpeakerRect();
    drawVideosWarped();

    vidGrabber.draw( ofGetWidth() / 2 - 200 / 2 , 30, 200, 80 );

    if ( isVerbose ) { drawVerboseText(); }
}

void ofBitchSkeletonApp::drawActiveSpeakerRect() const
{
    auto gap = 10;
    auto shift = 0;
    if ( bitches.getTalkerCurrentID() == 0 )
    {
        shift = 0;
    }
    else {
        shift = ofGetWidth() / 2;
    }

    if ( isVerbose )
    {
        ofPushStyle( );
        {
            ofSetColor( ofColor_::lightGray, 100 );
            ofDrawRectangle( gap + shift, gap, ofGetWidth( ) / 2 - 2 * gap, ofGetHeight( ) - 2 * gap );
        }
        ofPopStyle( );
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::drawVideosWarped()
{
    ofPushStyle();
    ofSetColor( ofColor::white );
    fboLeft.begin();
    {
        vidPlayerLeft.draw( 0, 0, fboLeft.getWidth(), fboLeft.getHeight() );
    }
    fboLeft.end();
    fboRight.begin();
    {
        vidPlayerRight.draw( 0, 0, fboRight.getWidth(), fboRight.getHeight() );
    }
    fboRight.end();

    auto matrixWarpLeft = warperLeft.getMatrix();
    auto matrixWarpRight = warperRight.getMatrix();

    // --- use the matrix to transform our fbo.
    ofPushMatrix();
    {
        ofMultMatrix( matrixWarpLeft );
        fboLeft.draw( 0, 0);
    }
    ofPopMatrix();
    ofPushMatrix();
    {
        ofMultMatrix( matrixWarpRight );
        fboRight.draw( 0, 0);
    }
    ofPopMatrix();
    // --- draw quad warp UI
    ofSetColor( ofColor::yellow);
    warperLeft.drawCorners();
    warperRight.drawCorners();

    ofSetColor( ofColor::magenta);
    warperLeft.drawHighlightedCorner();
    warperRight.drawHighlightedCorner();

    ofSetColor( ofColor::red);
    warperLeft.drawSelectedCorner();
    warperRight.drawSelectedCorner();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::setupWarping( int width, int height, int xPosLeft, int yPosLeft, int xPosRight, int yPosRight )
{
    fboLeft.allocate( width, height );
    warperLeft.setSourceRect( ofRectangle( 0, 0, width, height ));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warperLeft.setTopLeftCornerPosition( ofPoint( xPosLeft, yPosLeft ));             // this is position of the quad warp corners, centering the image on the screen.
    warperLeft.setTopRightCornerPosition( ofPoint( xPosLeft + width, yPosLeft ));        // this is position of the quad warp corners, centering the image on the screen.
    warperLeft.setBottomLeftCornerPosition( ofPoint( xPosLeft, yPosLeft + height ));      // this is position of the quad warp corners, centering the image on the screen.
    warperLeft.setBottomRightCornerPosition( ofPoint( xPosLeft + width, yPosLeft + height )); // this is position of the quad warp corners, centering the image on the screen.
    warperLeft.setup();

    fboRight.allocate( width, height );
    warperRight.setSourceRect( ofRectangle( 0, 0, width, height ));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warperRight.setTopLeftCornerPosition( ofPoint( xPosRight, yPosRight ));             // this is position of the quad warp corners, centering the image on the screen.
    warperRight.setTopRightCornerPosition( ofPoint( xPosRight + width, yPosRight ));        // this is position of the quad warp corners, centering the image on the screen.
    warperRight.setBottomLeftCornerPosition( ofPoint( xPosRight, yPosRight + height ));      // this is position of the quad warp corners, centering the image on the screen.
    warperRight.setBottomRightCornerPosition( ofPoint( xPosRight + width, yPosRight + height )); // this is position of the quad warp corners, centering the image on the screen.
    warperRight.setup();
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::keyPressed(int key){

    if ( key == 'S' )
    {
        processImage();
    }

    if ( key == 'F' )
    {
        ofToggleFullscreen();
    }

    // --- Verbose
    if(key == 'v' || key == 'V') {
        warperLeft.toggleShow();
        warperRight.toggleShow();
        isVerbose = warperLeft.isShowing();
    }


    if ( key == OF_KEY_RETURN )
    {
        textFromInput = textInput;
        textInput = "";
        bitches.next();

        bitches.doConversation();
        if ( textFromInput == "" )
        {
            ofLogError() << "No Text input";
        }

        reset();
    }
//    else
//    {
//        textInput += key;
//    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::processImage()
{
    saveImage( imageNamePath );
    bitches.sendPicturePath( "/Users/nesa/Documents/Developer/bloke/pictureOutput/picFromNetwork.jpg" );
    // TODO too fast, processing takes some time

    ofLogNotice() << "Sent picture";
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::saveImage( string &fileNamePath )
{
    ofImage img;
    img.setFromPixels( vidGrabber.getPixels() );
    img.save( fileNamePath );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::setupOSC()
{
    ofLogNotice() << "send1: " << xml.getValue( "OSC:PORT:SEND1", defaultXMLError );
    ofLogNotice() << "send2: " << xml.getValue( "OSC:PORT:SEND2", defaultXMLError );
    ofLogNotice() << "recieve1: " << xml.getValue( "OSC:PORT:RECIEVE1", defaultXMLError );
    ofLogNotice() << "recieve2: " << xml.getValue( "OSC:PORT:RECIEVE2", defaultXMLError );
    ofLogNotice() << "Host: " << xml.getValue( "OSC:HOST", defaultXMLError );

    string host             = xml.getValue( "OSC:HOST", defaultXMLError );
    int    portToPython1     = xml.getValue( "OSC:PORT:SEND1", 9000 );
    int    portToPython2     = xml.getValue( "OSC:PORT:SEND2", 9000 );
    int    portFromPython1   = xml.getValue( "OSC:PORT:RECIEVE1", 9000 );
    int    portFromPython2   = xml.getValue( "OSC:PORT:RECIEVE2", 9000 );

    bitches.setup( 0, host, portToPython1, portFromPython1 );
    bitches.setup( 1, host, portToPython2, portFromPython2 );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::reset()
{
    textCurrent = bitches.getAnswerCurrent();     //TODO sort this logic out;
    setVoice();
    shouldSpeak = true;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofBitchSkeletonApp::setVoice()
{
    if ( bitches.getNameSpeaker() == "Elisa" ) { voice = "Allison"; }
    else {
        voice = "Tom";
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + bitches.getAnswerCurrent() + " &";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::drawVerboseText()
{
    ofDrawBitmapStringHighlight( bitches.getName( 0 ) , ofGetWidth() / 4 , 100);
    ofDrawBitmapStringHighlight( bitches.getName( 1 ) , ofGetWidth() * 3 / 4, 100);

    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 0 ), 100, 200 );
    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 1 ), 600, 200 );

    ofDrawBitmapStringHighlight( "voice: " + voice, ofGetWidth() - 180, ofGetHeight() - 20 );
    ofDrawBitmapStringHighlight( "Said to Elisa: " + textFromInput, 10, ofGetHeight() - 20 );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::setupVideo( int &camWidth, int &camHeight )
{
    camWidth= 1280;
    camHeight= 720;
    vidPlayerLeft.load( "/Users/sonneundasche/Movies/Render/Lacuna - AI 1.mov" );
    vidPlayerRight.load( "/Users/sonneundasche/Movies/Render/Lacuna - AI 2.mov" );
    vidPlayerLeft.play();
    vidPlayerRight.play();// try to grab at this size.vidGrabber.setDeviceID( 0 );
    vidGrabber.setDesiredFrameRate( 15 );
    vidGrabber.initGrabber( camWidth, camHeight);
}
