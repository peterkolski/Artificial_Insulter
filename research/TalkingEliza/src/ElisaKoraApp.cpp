#include "ElisaKoraApp.h"

//--------------------------------------------------------------
void ElisaKoraApp::setup(){
    voice = "Tom";

    textCurrent = conversationEliza.getAnswerCurrent();
    ofLogNotice() << conversationEliza.getNameSpeaker( ) << ": "<< textCurrent;
}

//--------------------------------------------------------------
void ElisaKoraApp::update(){

}

//--------------------------------------------------------------
void ElisaKoraApp::draw(){

    ofDrawBitmapStringHighlight( conversationEliza.getNameSpeaker() , 10, 100);
    ofDrawBitmapStringHighlight( textCurrent, 100, 100);
    ofDrawBitmapStringHighlight( textLast, 100, 200);

//    speak( );
}

void ElisaKoraApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + textCurrent + " ";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
    }
}

//--------------------------------------------------------------
void ElisaKoraApp::keyPressed(int key){

    if ( key == ' ' )
    {
        conversationEliza.next();
        conversationEliza.doConversation();
        textCurrent = conversationEliza.getAnswerCurrent();
        textLast    = conversationEliza.getAnswerBefore();
    }
}
