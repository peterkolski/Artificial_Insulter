#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxQuadWarp.h"
#include "ofxSyphon.h"
#include "ofxGui.h"

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
    void drawText();
    void reset();
    void setupOSC();
    void saveImage( string &fileNamePath );
    void processImage( string targetPath );
    void setupWarping( int width, int height, int xPosLeft, int yPosLeft, int xPosRight, int yPosRight );
    void drawVideosWarped();
    void setupVideo( int &camWidth, int &camHeight );

    void updateConversation();
    void copyInputText();

    // --- XML
    ofxXmlSettings  xml;
    string defaultXMLError = "NIX";

    // --- CONVERSATION
    ConversationOSC    bitchConversation;
    string textCurrent = "";
    string textFromInput      = "";

    // --- SEEING
    ofVideoGrabber      vidGrabber;
    string              imageNamePath   = "imageFromTalkingElisa.jpg";
    string              textInput;
    string              pathTargetImage;

    // --- SOUND
    void speak();
    void sendSoundNotification( float durationDivision );
    string voice;
    bool    shouldSpeak = false;

    // --- VISUALIZER
    void            setupXML( string settingsPath );
    void            drawActiveSpeakerRect();
    ofFbo           fboLeft, fboRight;
    ofxQuadWarp     warperLeft, warperRight;
    ofVideoPlayer   vidPlayerLeft, vidPlayerRight;
    bool            isVerbose = true;
    ofxSyphonClient syphonLeft, syphonRight;
    ofTrueTypeFont	verdana14;


    // --- GUI
    void         setupGui();
    bool         drawGui = true;
    ofxIntSlider xPosTextLeft;
    ofxIntSlider xPosTextRight;
    ofxIntSlider yPosTextLeft;
    ofxIntSlider yPosTextRight;
    ofxIntSlider xPosCam;
    ofxIntSlider yPosCam;
    ofxIntSlider textTokenSize;
    ofxIntSlider roundsAmount;
    ofxPanel     gui;



    int secondsElapsedCurrent = 0;
    int secondsMarker = 0;
    int roundCounter = 0;
    bool isTalking = false;
    string fileWarperSettingsLeft = "settingsMappingLeft.xml";
    string fileWarperSettingsRight = "settingsMappingLeft.xml";
    string fileGuiSettings = "settingsGUI.xml";
};
