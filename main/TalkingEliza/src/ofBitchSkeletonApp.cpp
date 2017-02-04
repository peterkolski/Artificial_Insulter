#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    setVoice( );
    ofSetLogLevel( OF_LOG_VERBOSE );

//    string settingsPath = ofFilePath1.getCurrentWorkingDirectory() + "../../../data/settings.txt";
    string settingsPath = "/Users/sonneundasche/programming/of/apps/ElisaKora/bin/data/settings.txt";
    ofLogNotice() << settingsPath;
    if (!xml.loadFile( settingsPath ) )
    {
        ofLogError() << "No XML file loaded";
    }

    imageNamePath = xml.getValue( "PATH:SAVEPIC", "../out.jpg" );
    ofLogNotice() << "Path to write file" << imageNamePath;


    ofLogNotice() << "INFO: " << xml.getValue( "OSC:PORT:SEND", defaultXMLError );
    ofLogNotice() << "INFO: " << xml.getValue( "OSC:PORT:RECIEVE", defaultXMLError );
    ofLogNotice() << "INFO: " << xml.getValue( "OSC:ADRESS:RECIEVE:TEXT", defaultXMLError );
    ofLogNotice() << "INFO: " << xml.getValue( "OSC:ADRESS:SEND:TEXT", defaultXMLError );
    ofLogNotice() << "INFO: " << xml.getValue( "OSC:HOST", defaultXMLError );

    textCurrent = bitches.getAnswerCurrent();

    setupSoundAnalysis();
    setupGUI();
    setupOSC();

    auto camWidth = 1280;  // try to grab at this size.
    auto camHeight = 720;
    vidGrabber.setDeviceID( 0 );
    vidGrabber.setDesiredFrameRate( 15 );
    vidGrabber.initGrabber(camWidth, camHeight);

}

//--------------------------------------------------------------
void ofBitchSkeletonApp::update(){
    vidGrabber.update();
    speak( );
    //TODO HACK
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
    auto gap = 10;
    auto shift = 0;
    if ( bitches.getTalkerCurrentID() == 0 )
    {
        shift = 0;
    }
    else {
        shift = ofGetWidth() / 2;
    }

    ofPushStyle( );
        ofDrawRectangle( gap + shift, gap, ofGetWidth( ) / 2 - 2 * gap, ofGetHeight( ) - 2 * gap );
    ofPopStyle( );

    auto scale = 1.0;
    drawVoice( scale );

    vidGrabber.draw( ofGetWidth() / 2 - ( widthView / 2 ), 20, widthView, heightView );
    drawText( );

    gui2->draw( );
}

void ofBitchSkeletonApp::drawVoice( double scale )
{
    ofPushStyle( );
    ofSetColor( ofColor::red );
    ofDrawRectangle( 0, ofGetHeight() / 2, ofGetWidth( ), ofGetHeight( ) * analyser.getAmplitude() * scale );
    ofPopStyle( );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::keyPressed(int key){

    if ( key == 'S' )
    {
        processImage();
    }


    if  ( key == ' ' ){}
    {
        if ( !textInput->isFocused() )
        {
            bitches.next();
            bitches.doConversation();

            bitchElisa.update();
            //    bitchKora.update();

            reset();
        }
    }

    if (    ( key == OF_KEY_RETURN )
         && ( textInput->isClicked() ) )
    {
        textFromInput = textInput->getTextString();
        textInput->setTextString( "" );

        if ( textFromInput != "" )
        {
//            bitches.doConversation( textFromInput, 0 );
            bitchElisa.setTextToSend( textFromInput );
        }
        else
        {
            ofLogError() << "No Text input";
        }

        reset();
    }

}

void ofBitchSkeletonApp::processImage()
{
    saveImage( imageNamePath );
    bitchElisa.sendPicturePath();
//    bitchElisa.update(); // TODO too fast, processing taes some time

    ofLogNotice() << "Sent picture";
}

void ofBitchSkeletonApp::saveImage( string &fileNamePath )
{
    ofImage img;
    img.setFromPixels( vidGrabber.getPixels() );
    img.save( fileNamePath );
}

void ofBitchSkeletonApp::setupSoundAnalysis()
{
    auto bufferSize = 512;
    auto sampleRate = 44100;

    analyser.setup( sampleRate, bufferSize * 2, bufferSize, bufferSize / 2, 100 ); // call before ofSoundStreamSetup()
    ofSoundStreamSetup( 1, 1, this, sampleRate, bufferSize, 1 );
}

void ofBitchSkeletonApp::setupGUI()
{
    gui2 = new ofxUISuperCanvas( "Talk to Elisa", 400, 300, 200, 100 );
    textInput = gui2->addTextInput( "TEXT: ", "Hello Elisa");
    textInput->setAutoUnfocus( false);
    textInput->setAutoClear( false );
}

void ofBitchSkeletonApp::setupOSC()
{
    string host             = xml.getValue( "OSC:HOST", defaultXMLError );
    int    portToPython     = xml.getValue( "OSC:PORT:SEND", 9000 );
    int    portFromPython   = xml.getValue( "OSC:PORT:RECIEVE", 9000 );

    bitchElisa.setup( host, portToPython, portFromPython );
//    bitchKora.setup( host, portFromPython, portToPython );
}

void ofBitchSkeletonApp::reset()
{
    textCurrent = bitchElisa.getTextRecieved();
//    textCurrent = bitches.getAnswerCurrent();     //TODO sort this logic out
    textLast    = bitches.getAnswerBefore();
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
void ofBitchSkeletonApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + textCurrent + " &";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
    }
}

void ofBitchSkeletonApp::drawText()
{
    ofDrawBitmapStringHighlight( bitches.getName( 0 ) , ofGetWidth() / 4 , 100);
    ofDrawBitmapStringHighlight( bitches.getName( 1 ) , ofGetWidth() * 3 / 4, 100);

    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 0 ), 100, 200 );
    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 1 ), 600, 200 );
    ofDrawBitmapStringHighlight( "OSC to Python: " + bitchElisa.getTextToSend(), 100, 220 );
    ofDrawBitmapStringHighlight( "OSC from Python: " + bitchElisa.getTextRecieved(), 100, 240 );
//    ofDrawBitmapStringHighlight( "OSC: " + bitchKora.getTextRecieved(), 600, 220 );

    ofDrawBitmapStringHighlight( "voice: " + voice, ofGetWidth() - 180, ofGetHeight() - 20 );
    ofDrawBitmapStringHighlight( "Said to Elisa: " + textFromInput, 10, ofGetHeight() - 20 );
}

void ofBitchSkeletonApp::audioIn( float*input, int bufferSize, int nChannels )
{
    analyser.grabAudioBuffer( input );
}
