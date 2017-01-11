#include "ElisaKoraApp.h"

//--------------------------------------------------------------
void ElisaKoraApp::setup(){
    voice = "Tom";

    elizaResponse = talkerOne.start();

}

//--------------------------------------------------------------
void ElisaKoraApp::update(){


//    std::getline(std::cin, userSays);

}

//--------------------------------------------------------------
void ElisaKoraApp::draw(){

    ofDrawBitmapStringHighlight( elizaResponse, 100, 100);

    ofDrawBitmapStringHighlight( textInput, 100, 200);

//    speak( );
}

void ElisaKoraApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + elizaResponse + " ";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
        textInput = "";
    }
}

//--------------------------------------------------------------
void ElisaKoraApp::keyPressed(int key){
    textInput += key;

    if ( key == OF_KEY_RETURN )
    {
        elizaResponse = talkerOne.ask( textInput );
        shouldSpeak = true;
    }
}
