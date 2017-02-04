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
    string update();
    void            setTextToSend( const string &textToSend_ ) { bitcherOSC::textToSend_ = textToSend_; }
    const string    &getAnswer() { return textRecieved_; }
    const string    &getTextToSend() { return textToSend_; }
    void            sendPicturePath();

private:
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
    string  textToSend_     = "";
    string  recieveText();
    void    sendText( string &text );
};


#endif //RESEARCH_OSC_OSCBITCHER_H
