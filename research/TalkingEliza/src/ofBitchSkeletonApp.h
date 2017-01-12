#pragma once

#include "ofMain.h"
#include "ofxEliza.h"
#include "TalkerEliza.h"
#include "ConversationEliza.h"

class ofBitchSkeletonApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    void chooseVoice();

    arstu::ConversationEliza    bitches;

    string voice;
    string textCurrent = "";
    string textLast = "";
    string str      = "";
    bool    shouldSpeak = false;

    void speak();

};
