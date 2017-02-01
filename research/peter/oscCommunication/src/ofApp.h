#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "bitcherOSC.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void keyPressed( int key ) override;

    bitcherOSC  bitchElisa;
    bitcherOSC  bitchKora;

};
