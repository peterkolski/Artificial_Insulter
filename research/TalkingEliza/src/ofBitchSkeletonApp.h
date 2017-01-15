#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#include "TalkerEliza.h"
#include "ConversationEliza.h"


class ofBitchSkeletonApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    void setVoice();

    // --- CONVERSATION
    arstu::ConversationEliza    bitches;
    string textCurrent = "";
    string textLast = "";
    string textFromInput      = "";

    // --- SEEING
    ofxUITextInput *textInput;
    ofxUISuperCanvas *gui2;

    // --- SOUND
    void speak();
    string voice;
    bool    shouldSpeak = false;

    // --- VISUALIZER

    void drawText();
    void reset();
};
