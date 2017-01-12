#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    chooseVoice();

    textCurrent = conversationEliza.getAnswerCurrent();
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::update(){
    speak( );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::draw(){

    ofDrawBitmapStringHighlight( conversationEliza.getNameSpeaker() , 10, 100);
    ofDrawBitmapStringHighlight( textCurrent, 100, 100);
    ofDrawBitmapStringHighlight( textLast, 100, 200);
    ofDrawBitmapStringHighlight( "voice: " + voice, 100, 300);
}

void ofBitchSkeletonApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + textCurrent + " &";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
    }
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::keyPressed(int key){

    if ( key == ' ' )
    {
        conversationEliza.next();
        conversationEliza.doConversation();
        textCurrent = conversationEliza.getAnswerCurrent();
        textLast    = conversationEliza.getAnswerBefore();
        chooseVoice();
        shouldSpeak = true;
    }
}

void ofBitchSkeletonApp::chooseVoice()
{
    if ( conversationEliza.getNameSpeaker() == "Elisa" ) { voice = "Allison"; }
    else {
        voice = "Tom";
    }

}
