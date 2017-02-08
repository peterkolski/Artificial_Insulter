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

    const string    &getAnswer() { return textRecieved_; }
    const string    &getTextAsked() { return textSent_; }
    void            recieveText();

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
    std::string     adressRecieverSending_;
    std::string     adressRecieverArrived_;
    std::string     adressSenderText_;
    std::string     adressSenderSending_;
    std::string     adressSenderArrived_;

    string  textRecieved_   = "";
    string  textSent_     = "";
};


#endif //RESEARCH_OSC_OSCBITCHER_H
