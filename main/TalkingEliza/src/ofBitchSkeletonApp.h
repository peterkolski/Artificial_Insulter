#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
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

    void setVoice();
    void drawVerboseText();
    void reset();
    void setupOSC();
    void saveImage( string &fileNamePath );
    void processImage( string targetPath );
    void setupWarping( int width, int height, int xPosLeft, int yPosLeft, int xPosRight, int yPosRight );
    void drawVideosWarped();
    void setupVideo( int &camWidth, int &camHeight );

    // --- XML
    ofxXmlSettings  xml;
    string defaultXMLError = "NIX";

    // --- CONVERSATION
    ConversationOSC    bitches;
    string textCurrent = "";
    string textFromInput      = "";

    // --- SEEING
    ofVideoGrabber      vidGrabber;
    string              imageNamePath   = "imageFromTalkingElisa.jpg";
    string              textInput;
    string              pathTargetImage;

    // --- SOUND
    void speak();
    string voice;
    bool    shouldSpeak = false;

    // --- VISUALIZER
    ofFbo           fboLeft, fboRight;
    ofxQuadWarp     warperLeft, warperRight;
    ofVideoPlayer   vidPlayerLeft, vidPlayerRight;
    bool            isVerbose = true;
    void drawActiveSpeakerRect() const;
};
