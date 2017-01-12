#include "ElisaKoraApp.h"

//--------------------------------------------------------------
void ElisaKoraApp::setup(){
    chooseVoice();

    textCurrent = conversationEliza.getAnswerCurrent();
}

//--------------------------------------------------------------
void ElisaKoraApp::update(){

}

//--------------------------------------------------------------
void ElisaKoraApp::draw(){

    ofDrawBitmapStringHighlight( conversationEliza.getNameSpeaker() , 10, 100);
    ofDrawBitmapStringHighlight( textCurrent, 100, 100);
    ofDrawBitmapStringHighlight( textLast, 100, 200);
    ofDrawBitmapStringHighlight( "voice: " + voice, 100, 300);

    speak( );
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
        chooseVoice();
        shouldSpeak = true;
    }
}

void ElisaKoraApp::chooseVoice()
{
    if ( conversationEliza.getNameSpeaker() == "Elisa" ) { voice = "Allison"; }
    else {
        voice = "Tom";
    }

}
