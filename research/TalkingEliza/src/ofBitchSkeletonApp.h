#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "ofxSoundProcessor.h"


#include "TalkerEliza.h"
#include "ConversationEliza.h"
#include "bitcherOSC.h"


class ofBitchSkeletonApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    void audioIn( float*input, int bufferSize, int nChannels );

    void setVoice();

    // --- CONVERSATION
    arstu::ConversationEliza    bitches;
    string textCurrent = "";
    string textLast = "";
    string textFromInput      = "";
    bitcherOSC  bitchElisa;
    bitcherOSC  bitchKora;

    // --- SEEING
    ofxUITextInput *textInput;
    ofxUISuperCanvas *gui2;

    // --- SOUND
    void speak();
    string voice;
    bool    shouldSpeak = false;

    // --- VISUALIZER
    ofxSoundAnalyser    analyser;

    void drawText();
    void reset();
    void drawVoice( double scale );
};
