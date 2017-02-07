#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
//#include "ofxSoundProcessor.h"
#include "ofxQuadWarp.h"

#include "ConversationOSC.h"
#include "bitcherOSC.h"


class ofBitchSkeletonApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
//    void audioIn( float*input, int bufferSize, int nChannels );

    void setVoice();

    // --- XML
    ofxXmlSettings  xml;
    string defaultXMLError = "NIX";

    // --- CONVERSATION
    ConversationOSC    bitches;
//    bitcherOSC  bitchElisa;
    string textCurrent = "";
    string textLast = "";
    string textFromInput      = "";

    // --- SEEING
    ofVideoGrabber      vidGrabber;
    string              imageNamePath   = "imageFromTalkingElisa.jpg";
    int                 widthView       = 160;
    int                 heightView      = 120;
    ofxUITextInput      *textInput;
    ofxUISuperCanvas    *gui2;

    // --- SOUND
    void speak();
    string voice;
    bool    shouldSpeak = false;

    // --- VISUALIZER
//    ofxSoundAnalyser    analyser;
    ofFbo               fboLeft, fboRight;
    ofxQuadWarp         warperLeft, warperRight;
    ofVideoPlayer       vidPlayerLeft, vidPlayerRight;

    void drawText();
    void reset();
//    void drawVoice( double scale );
    void setupOSC();
    void setupGUI();
//    void setupSoundAnalysis();
    void saveImage( string &fileNamePath );
    void processImage();
    void setupWarping( int width, int height, int xPosLeft, int yPosLeft, int xPosRight, int yPosRight );
};
