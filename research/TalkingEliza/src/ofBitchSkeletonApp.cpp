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
    auto gap = 10;
    auto shift = 0;
    if ( conversationEliza.getTalkerCurrentID() == 0 )
    {
        shift = 0;
    }
    else {
        shift = ofGetWidth() / 2;
    }

    ofPushStyle( );
        ofDrawRectangle( gap + shift, gap, ofGetWidth( ) / 2 - 2 * gap, ofGetHeight( ) - 2 * gap );
    ofPopStyle( );
    
    ofDrawBitmapStringHighlight( conversationEliza.getName( 0 ) , ofGetWidth() / 4 , 100);
    ofDrawBitmapStringHighlight( conversationEliza.getName( 1 ) , ofGetWidth() * 3/4, 100);
    
    ofDrawBitmapStringHighlight( conversationEliza.getAnswerFromID( 0 ), 100, 200 );
    ofDrawBitmapStringHighlight( conversationEliza.getAnswerFromID( 1 ), 500, 200 );
    ofDrawBitmapStringHighlight( "voice: " + voice, 100, 300 );

     
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
