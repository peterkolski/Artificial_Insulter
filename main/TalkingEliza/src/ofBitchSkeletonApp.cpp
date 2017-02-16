#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    setVoice( );
    ofSetLogLevel( OF_LOG_VERBOSE );
//    ofEnableAlphaBlending();
    ofDisableAlphaBlending();
    setupXML( "/Users/sonneundasche/programming/of/apps/ElisaKora/bin/data/settings.txt" );

    textCurrent = bitchConversation.getAnswerCurrent();

    pathTargetImage = xml.getValue( "PATH:OSCPIC", "" );
    fileWarperSettingsLeft = "settingsMappingLeft.xml";
    fileWarperSettingsRight = "settingsMappingRight.xml";
    fileGuiSettings = "settingsGUI.xml";

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
//    setupWarping( camWidth / 3, camHeight / 2, 10, 10, ofGetWidth() / 2, 10 );
    setupWarping( ofGetWidth() / 2 - 20, ofGetHeight() - 100, 10, 10, ofGetWidth() / 2, 10 );

    bitchConversation.doConversation( "I hate you all 0 Left", 0 );
    bitchConversation.doConversation( "I hate you all 1 Right", 1 );
    bitchConversation.doConversation( "I hate you all 2 Left", 2 );
    bitchConversation.doConversation( "I hate you all 3 Right", 3 );

    verdana14.load("verdana.ttf", 20, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);

    gui.setup( "ElisaApp", fileGuiSettings );
    gui.add( xPosTextLeft.setup( "Text Left X", 240, 0, 2000 ) );
    gui.add( yPosTextLeft.setup( "Text Left Y", 900, 0, 2000 ) );
    gui.add( xPosTextRight.setup( "Text Right X", 1060, 0, 2000 ) );
    gui.add( yPosTextRight.setup( "Text Right Y", 900, 0, 2000 ) );
    gui.add( xPosCam.setup( "Cam X", 1500, 0, 2000 ) );
    gui.add( yPosCam.setup( "Cam Y", 900, 0, 2000 ) );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::update(){
    vidPlayerLeft.update();
    vidPlayerRight.update();
    vidGrabber.update();
    bitchConversation.recieveOscMessages();

    sendSoundNotification( 4 );

    updateCoversation();

//    speak();
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::draw() {
    ofBackground( 0 );

    drawActiveSpeakerRect();
    drawVideosWarped();

    vidGrabber.draw( xPosCam , yPosCam, 200, 80 );

    drawText();

    if ( isVerbose ) { drawVerboseText(); }
    if ( drawGui ) { gui.draw(); }
}

void ofBitchSkeletonApp::drawActiveSpeakerRect()
{
    auto gap = 10;
    auto shift = 0;
    if ( bitchConversation.getNameSpeaker() == "Left" )
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
        syphonLeft.draw( 0, 0, fboLeft.getWidth(), fboLeft.getHeight() );
//        vidPlayerLeft.draw( 0, 0, fboLeft.getWidth(), fboLeft.getHeight() );
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
void ofBitchSkeletonApp::keyPressed(int key)
{

    if ( key == 'S' )
    {
        processImage( pathTargetImage );
    }

    // --- save settings
    if ( key == 's' )
    {
        gui.saveToFile( fileGuiSettings );
        warperLeft.save( fileWarperSettingsLeft );
        warperRight.save( fileWarperSettingsRight );
    }

    // --- load settings
    if ( key == 'L' )
    {
        gui.loadFromFile( fileGuiSettings );
        warperLeft.load( fileWarperSettingsLeft );
        warperRight.load( fileWarperSettingsRight );
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
        drawGui = !drawGui;
    }


    if ( key == OF_KEY_RETURN )
    {
        updateCoversation();
    }
}

void ofBitchSkeletonApp::updateCoversation()
{
    secondsElapsedCurrent = (int)ofGetElapsedTimef() - secondsMarker;

    if ( ( secondsElapsedCurrent > 3 ) && ( !isTalking ) )
    {
        if ( roundCounter > 10 )
        {
            isTalking = true;
            processImage( pathTargetImage );
            roundCounter = 0;
        }
        else
        {
            isTalking = true;

            copyInputText();
            bitchConversation.nextChatter();
            textCurrent = bitchConversation.getAnswerCurrent(); // For checking when new text come in
            bitchConversation.doConversation();

            roundCounter++;
        }

        ofLogVerbose() << "ROUND: " << roundCounter;
    }

    if ( ( isTalking )
         && ( secondsElapsedCurrent > 6 )
        && ( !bitchConversation.isSoundPlayingRight() )
        && ( !bitchConversation.isSoundPlayingLeft() ) )
    {
        secondsMarker = (int)ofGetElapsedTimef();
        isTalking = false;

        ofLogVerbose() << "Ready for talking again";
    }
}

void ofBitchSkeletonApp::copyInputText()
{
    textFromInput = textInput;
    textInput = "";
    if ( textFromInput == "" )
    {
        ofLogError() << "No Text input";
    }
}

void ofBitchSkeletonApp::sendSoundNotification( float durationDivision )
{
    if ( textCurrent != bitchConversation.getAnswerCurrent() ) // TODO das wird immer untscheidlich sein, da die speaker wechseln
    {
        ofLogVerbose() << "Sound Text before: " << textCurrent;
        textCurrent = bitchConversation.getAnswerCurrent();
        ofLogVerbose() << "Sound Text after: " << textCurrent;

        setVoice();
        shouldSpeak = true;
        
        float duration = (float)textCurrent.length() / durationDivision;
        if ( bitchConversation.getNameSpeaker() == "Left" )
        {
            bitchConversation.sendSoundStartLeft( duration );
        }
        else
        {
            bitchConversation.sendSoundStartRight( duration );
        }
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::processImage( string targetPath )
{
    saveImage( imageNamePath );
    bitchConversation.sendPictureAnalyserFilePath( targetPath );
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
    int    portFromPython1   = xml.getValue( "OSC:PORT:RECIEVE1", 9000 );
    int    portFromPython2   = xml.getValue( "OSC:PORT:RECIEVE2", 9000 );
    int    portToPythonPic   = xml.getValue( "OSC:PORT:SENDPIC", 9000 );
    int    portFromPythonPic = xml.getValue( "OSC:PORT:RECIEVEPIC", 9000 );

    bitchConversation.setup( 0, host, portToPython1, portFromPython1 );
    bitchConversation.setup( 1, host, portToPython2, portFromPython2 );
    bitchConversation.setup( 2, host, 20002, 20001 );
    bitchConversation.setup( 3, host, 20004, 20003 );
    bitchConversation.setupPicturePath( "192.168.1.33", portToPythonPic, portFromPythonPic, "/recognize" );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::reset()
{
    textCurrent = bitchConversation.getAnswerCurrent();     //TODO sort this logic out;
    setVoice();
    shouldSpeak = true;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofBitchSkeletonApp::setVoice()
{
    if ( bitchConversation.getNameSpeaker() == "Elisa" ) { voice = "Allison"; }
    else {
        voice = "Tom";
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + bitchConversation.getAnswerCurrent() + " &";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::drawVerboseText()
{
    ofDrawBitmapStringHighlight( bitchConversation.getName( 0 ) , ofGetWidth() / 4 , 100);
    ofDrawBitmapStringHighlight( bitchConversation.getName( 1 ) , ofGetWidth() * 3 / 4, 100);

    ofDrawBitmapStringHighlight( bitchConversation.getAnswerLeft(), 100, 200 );
    ofDrawBitmapStringHighlight( bitchConversation.getAnswerRight(), 600, 200 );

    ofDrawBitmapStringHighlight( bitchConversation.getPictureRecievedText1(), 600, 250, ofColor::red );
    ofDrawBitmapStringHighlight( bitchConversation.getPictureRecievedText2(), 100, 250, ofColor::red );

    ofDrawBitmapStringHighlight( "voice: " + voice, ofGetWidth() - 180, ofGetHeight() - 20 );
    ofDrawBitmapStringHighlight( "Said to Elisa: " + textFromInput, 10, ofGetHeight() - 20 );
}

void ofBitchSkeletonApp::drawText()
{
    int maxNumCharacters = 40;

    ofSetColor(225);
    if ( bitchConversation.isSoundPlayingLeft() )
    {
//        verdana14.drawString( bitchConversation.getAnswerLeft() , 100, 250);
        verdana14.drawString( tokenizer( bitchConversation.getAnswerLeft(), maxNumCharacters ), xPosTextLeft, yPosTextLeft);
    }

    if ( bitchConversation.isSoundPlayingRight() )
    {
//        ofDrawBitmapStringHighlight( bitchConversation.getAnswerRight(), 600, 350 );
        verdana14.drawString( tokenizer( bitchConversation.getAnswerRight(), maxNumCharacters ), xPosTextRight, yPosTextRight);
    }

    // --- Drawing the Picture texts
    ofPushStyle();
    {
        ofSetColor( ofColor::red );
        verdana14.drawString( tokenizer( bitchConversation.getPictureRecievedText1(), maxNumCharacters ), xPosTextLeft, yPosTextLeft + 50);
        verdana14.drawString( tokenizer( bitchConversation.getPictureRecievedText2(), maxNumCharacters ), xPosTextRight, yPosTextRight + 50);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::setupVideo( int &camWidth, int &camHeight )
{
    vidPlayerLeft.load( xml.getValue("PATH:VID1", "Lacuna - AI 1.mov") );
    vidPlayerRight.load( xml.getValue("PATH:VID2", "Lacuna - AI 2.mov")  );
    vidPlayerLeft.play();
    vidPlayerRight.play();// try to grab at this size.
    vidGrabber.setDeviceID( xml.getValue("CAMEXTERNAL", 0 ) );
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

string ofBitchSkeletonApp::tokenizer( string input, int maxChar )
{
    if (!input.size()) {
        return "";
    }
    std::stringstream sStream;
    sStream << input[0];
    for (int i = 1; i < input.size(); i++)
    {
//        if ( ( i > maxChar ) && ( input[i] == ' ' ) )
        if ( i % maxChar == 0 )
        {
            sStream << "\n" << input[i];
        }
        else
        {
            sStream << input[i];
        }
    }
    return ofToString( sStream.str() );
}
