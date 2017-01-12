#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    chooseVoice();

    textCurrent = bitches.getAnswerCurrent();
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::update(){
    speak( );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::draw(){
    auto gap = 10;
    auto shift = 0;
    if ( bitches.getTalkerCurrentID() == 0 )
    {
        shift = 0;
    }
    else {
        shift = ofGetWidth() / 2;
    }

    ofPushStyle( );
        ofDrawRectangle( gap + shift, gap, ofGetWidth( ) / 2 - 2 * gap, ofGetHeight( ) - 2 * gap );
    ofPopStyle( );
    
    ofDrawBitmapStringHighlight( bitches.getName( 0 ) , ofGetWidth() / 4 , 100);
    ofDrawBitmapStringHighlight( bitches.getName( 1 ) , ofGetWidth() * 3/4, 100);
    
    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 0 ), 100, 200 );
    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 1 ), 500, 200 );
    ofDrawBitmapStringHighlight( "voice: " + voice, 100, 300 );
    ofDrawBitmapStringHighlight( "Input: " + str, 100, 350 );


     
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

    if ( key == OF_KEY_RETURN )
    {
        bitches.next();
        bitches.doConversation();
        textCurrent = bitches.getAnswerCurrent();
        textLast    = bitches.getAnswerBefore();
        chooseVoice();
        shouldSpeak = true;
        str = "";
    }

    // delete one character
    if(key==8 && str.size()>0) {
        str = str.substr(0, str.size()-1);
    } else {
        str.append (1, (char)key );
    }
}

void ofBitchSkeletonApp::chooseVoice()
{
    if ( bitches.getNameSpeaker() == "Elisa" ) { voice = "Allison"; }
    else {
        voice = "Tom";
    }

}
