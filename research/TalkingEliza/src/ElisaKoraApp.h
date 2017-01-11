#pragma once

#include "ofMain.h"
#include "ofxEliza.h"
#include "TalkerEliza.h"
#include "ConversationEliza.h"

class ElisaKoraApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);

    arstu::TalkerEliza          talkerOne;
    arstu::ConversationEliza    conversationEliza;

        string voice;
		string elizaResponse;
        string textInput = {};
        bool    shouldSpeak = false;

	void speak();
};
