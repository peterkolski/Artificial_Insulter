#include "ofBitchSkeletonApp.h"

//--------------------------------------------------------------
void ofBitchSkeletonApp::setup(){
    switchVoice( );

    textCurrent = bitches.getAnswerCurrent();

    gui2 = new ofxUISuperCanvas( "Talk to Elisa", 400, 300, 200, 100 );
    textInput = gui2->addTextInput("TEXT: ", "Hello Elisa");
    textInput->setAutoUnfocus(false);
    textInput->setAutoClear( false );
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

    drawText( );

    gui2->draw( );
}

//--------------------------------------------------------------
void ofBitchSkeletonApp::keyPressed(int key){

    if  ( key == ' ' )
    {
        if ( !textInput->isFocused() )
        {
            bitches.next();
            bitches.doConversation();
            textCurrent = bitches.getAnswerCurrent();
            textLast    = bitches.getAnswerBefore();
            switchVoice( );
            shouldSpeak = true;
        }
    }

    if ( key == OF_KEY_RETURN )
    {
        str = textInput->getTextString();
        bitches.tell( std::string( ), 0 );

        textInput->setTextString( "" );
    }

}
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofBitchSkeletonApp::switchVoice()
{
    if ( bitches.getNameSpeaker() == "Elisa" ) { voice = "Allison"; }
    else {
        voice = "Tom";
    }

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

void ofBitchSkeletonApp::drawText()
{
    ofDrawBitmapStringHighlight( bitches.getName( 0 ) , ofGetWidth() / 4 , 100);
    ofDrawBitmapStringHighlight( bitches.getName( 1 ) , ofGetWidth() * 3 / 4, 100);

    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 0 ), 100, 200 );
    ofDrawBitmapStringHighlight( bitches.getAnswerFromID( 1 ), 500, 200 );
    ofDrawBitmapStringHighlight( "voice: " + voice, 100, 300 );
    ofDrawBitmapStringHighlight( "Said to Elisa: " + str, 10, ofGetHeight() - 20 );
}
