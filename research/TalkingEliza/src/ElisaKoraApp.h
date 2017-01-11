#pragma once

#include "ofMain.h"
#include "ofxEliza.h"
#include "TalkerEliza.h"

class ElisaKoraApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);

    arstu::TalkerEliza  talkerOne;

        ofxEliza eliza;

        string voice;
		string elizaResponse;
        string textInput = {};
        bool    shouldSpeak = false;

	void speak();
};
