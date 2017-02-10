//
// Created by Peter A. Kolski on 01.02.17.
//

#ifndef RESEARCH_OSC_OSCBITCHER_H
#define RESEARCH_OSC_OSCBITCHER_H

#include <string>
#include "ofMain.h"
#include "ofxOsc.h"

using namespace std;

class bitcherOSC
{
public:
    void setup( string &hostSendingTo, int portSender, int portReciever );
    string          ask( string &text );
    void            startMutant( string txt1, string txt2 );

    const string    &getAnswer() { return textRecieved_; }
    const string    &getTextAsked() { return textSent_; }
    void            recieveText();
    bool            switchChatbot() { return switchChatbot_; }

private:
    void            sendText( string &text );
    std::string     logInfo_ = "BitcherOSC || ";
    string getOscMsgAsString( ofxOscMessage m );
    ofxOscSender    sender_;
    ofxOscReceiver  reciever_;
    int             portSender_;
    int             portReciever_;
    std::string     hostSendSendingTo_;
    std::string     adressRecieverText_;
    std::string     adressSenderText_;
    bool            switchChatbot_ = false;

    string  textRecieved_   = "";
    string  textSent_     = "";
};


#endif //RESEARCH_OSC_OSCBITCHER_H
