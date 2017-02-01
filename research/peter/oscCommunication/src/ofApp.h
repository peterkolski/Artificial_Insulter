#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "oscBitcher.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void keyPressed( int key ) override;
    
    oscBitcher  bitchElisa;
    oscBitcher  bitchKora;

};
