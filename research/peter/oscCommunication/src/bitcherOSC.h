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
    void setup( string &hostSender, int portSender, int portReciever );
    void update();

    bool            isRecievable() ;
    bool            isSendable() ;
    const string    &getTextRecieved() ;
    void            setTextRecieved( const string &textRecieved_ );
    const string    &getTextToSend() ;
    void            setTextToSend( const string &textToSend_ );
    void            setAdress( const string &adress );

private:

    string getOscMsgAsString( ofxOscMessage m );
    ofxOscSender    sender_;
    ofxOscReceiver  reciever_;
    int             portSender_;
    int             portReciever_;
    std::string     hostSenderToOther_;
    std::string     adress_;

    bool    recievable_   = false;
    bool    sendable_     = false;
    string  textRecieved_   = "";
    string  textToSend_     = "";
    string  recieveText();
    void sendText( string &text );
};


#endif //RESEARCH_OSC_OSCBITCHER_H
