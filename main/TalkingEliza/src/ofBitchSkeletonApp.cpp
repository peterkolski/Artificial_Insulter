#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    setVoice( );
    ofSetLogLevel( OF_LOG_VERBOSE );
//    ofEnableAlphaBlending();
    ofDisableAlphaBlending();
    setupXML( "/Users/sonneundasche/programming/of/apps/ElisaKora/bin/data/settings.txt" );

    textCurrent = bitches.getAnswerCurrent();

    pathTargetImage = "/Users/nesa/Documents/Developer/bloke/pictureOutput/picFromNetwork.jpg"; //TODO from XML

    setupOSC();
    int camWidth = 1280;
    int camHeight = 720;
    // --- Syphon
    syphonLeft.setup();
    syphonRight.setup();
    string appName = "Max";
    string serverName1 = "left";
    string serverName2 = "right";
    syphonLeft.set( serverName1, appName );
    syphonRight.set( serverName2, appName );

    setupVideo( camWidth, camHeight );
    setupWarping( camWidth / 3, camHeight / 2, 10, 10, ofGetWidth() / 2, 10 );

    bitches.doConversation( "I hate you all 0 Left", 0 );
    bitches.doConversation( "I hate you all 1 Right", 1 );
    bitches.doConversation( "I hate you all 2 Left", 2 );
    bitches.doConversation( "I hate you all 3 Right", 3 );

    verdana14.load("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::update(){
    vidPlayerLeft.update();
    vidPlayerRight.update();
    vidGrabber.update();
    bitches.recieveMessages();

    sendSoundNotification( 10 );

//    speak();

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

    drawText();

    if ( isVerbose ) { drawVerboseText(); }
}

void ofBitchSkeletonApp::drawActiveSpeakerRect()
{
    auto gap = 10;
    auto shift = 0;
    if ( bitches.getNameSpeaker() == "Left" )
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
            ofSetColor( ofColor::lightGray, 100 );
            ofDrawRectangle( gap + shift, gap, ofGetWidth( ) / 2 - 2 * gap, ofGetHeight( ) - 2 * gap );
        }
        ofPopStyle( );
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::drawVideosWarped()
{
    ofPushStyle();
    ofSetColor( ofColor::white, 255 );
    fboLeft.begin();
    {
//        ofDisableAlphaBlending();
        syphonLeft.draw( 0, 0, fboLeft.getWidth(), fboLeft.getHeight() );
//        vidPlayerLeft.draw( 0, 0, fboLeft.getWidth(), fboLeft.getHeight() );
//        ofEnableAlphaBlending();
    }
    fboLeft.end();
    fboRight.begin();
    {
        syphonRight.draw( 0, 0, fboRight.getWidth(), fboRight.getHeight() );
//        vidPlayerRight.draw( 0, 0, fboRight.getWidth(), fboRight.getHeight() );
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
        processImage( pathTargetImage );
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
        textCurrent = bitches.getAnswerCurrent(); // For checking when new text come in
        bitches.doConversation();

        if ( textFromInput == "" )
        {
            ofLogError() << "No Text input";
        }
    }
//    else
//    {
//        textInput += key;
//    }
}

void ofBitchSkeletonApp::sendSoundNotification( float durationDivision )
{
    if ( textCurrent != bitches.getAnswerCurrent() ) // TODO das wird immer untscheidlich sein, da die speaker wechseln
    {
        ofLogVerbose() << "Sound Text before: " << textCurrent;
        textCurrent = bitches.getAnswerCurrent();
        ofLogVerbose() << "Sound Text after: " << textCurrent;

        setVoice();
        shouldSpeak = true;
        
        float duration = (float)textCurrent.length() / durationDivision;
        if ( bitches.getNameSpeaker() == "Left" )
        {
            bitches.sendSoundStartLeft( duration );
        }
        else
        {
            bitches.sendSoundStartRight( duration );
        }
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::processImage( string targetPath )
{
    saveImage( imageNamePath );
    bitches.sendPicturePath( targetPath );

    // TODO too fast, processing takes some time
    // TODO HACK

    //switch to mutant
    bitches.sendStartMutant( "a flock of birds sitting on top of a power line", "a group of birds sitting on top of a sign" );
    bitches.setIsMutantChatbot( true );

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
    ofLogNotice() << "sendPic: " << xml.getValue( "OSC:PORT:SENDPIC", defaultXMLError );
    ofLogNotice() << "recieve1: " << xml.getValue( "OSC:PORT:RECIEVE1", defaultXMLError );
    ofLogNotice() << "recieve2: " << xml.getValue( "OSC:PORT:RECIEVE2", defaultXMLError );
    ofLogNotice() << "Host: " << xml.getValue( "OSC:HOST", defaultXMLError );

    string host              = xml.getValue( "OSC:HOST", defaultXMLError );
    int    portToPython1     = xml.getValue( "OSC:PORT:SEND1", 9000 );
    int    portToPython2     = xml.getValue( "OSC:PORT:SEND2", 9000 );
    int    portToPythonPic   = xml.getValue( "OSC:PORT:SENDPIC", 9000 );
    int    portFromPython1   = xml.getValue( "OSC:PORT:RECIEVE1", 9000 );
    int    portFromPython2   = xml.getValue( "OSC:PORT:RECIEVE2", 9000 );

    bitches.setup( 0, host, portToPython1, portFromPython1 );
    bitches.setup( 1, host, portToPython2, portFromPython2 );
    bitches.setup( 2, host, 20002, 20001 );
    bitches.setup( 3, host, 20004, 20003 );
    bitches.setupPicturePath( host, portToPythonPic, "/recognize" );
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

    ofDrawBitmapStringHighlight( bitches.getAnswerLeft(), 100, 200 );
    ofDrawBitmapStringHighlight( bitches.getAnswerRight(), 600, 200 );

    ofDrawBitmapStringHighlight( "voice: " + voice, ofGetWidth() - 180, ofGetHeight() - 20 );
    ofDrawBitmapStringHighlight( "Said to Elisa: " + textFromInput, 10, ofGetHeight() - 20 );
}

void ofBitchSkeletonApp::drawText()
{
    ofSetColor(225);
    if ( bitches.isSoundPlayingLeft() )
    {
        ofDrawBitmapStringHighlight( bitches.getAnswerLeft(), 100, 300 );
        verdana14.drawString( bitches.getAnswerLeft() , 100, 250);
//        ofDrawBitmapStringHighlight( "LEFT", 100, 200 );
    }

    if ( bitches.isSoundPlayingRight() )
    {
        ofDrawBitmapStringHighlight( bitches.getAnswerRight(), 600, 350 );
        verdana14.drawString( bitches.getAnswerRight(), 600, 270);
//        ofDrawBitmapStringHighlight( "RIGHT", 600, 200 );
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::setupVideo( int &camWidth, int &camHeight )
{
    vidPlayerLeft.load( xml.getValue("PATH:VID1", "Lacuna - AI 1.mov") );
    vidPlayerRight.load( xml.getValue("PATH:VID2", "Lacuna - AI 2.mov")  );
    vidPlayerLeft.play();
    vidPlayerRight.play();// try to grab at this size.vidGrabber.setDeviceID( 0 );
    vidGrabber.setDesiredFrameRate( 15 );
    vidGrabber.initGrabber( camWidth, camHeight);
}

void ofBitchSkeletonApp::setupXML( string settingsPath )
{//    string settingsPath = ofFilePath1.getCurrentWorkingDirectory() + "../../../data/settings.txt";
    ofLogNotice() << settingsPath;
    if (!xml.loadFile( settingsPath ) )
    {
        ofLogError() << "No XML file loaded";
    }

    imageNamePath = xml.getValue( "PATH:SAVEPIC", "../out.jpg" );
    ofLogNotice() << "Path to write file" << imageNamePath;
}
