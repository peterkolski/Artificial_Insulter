//
// Created by Peter A. Kolski on 01.02.17.
//

#ifndef RESEARCH_OSC_OSCBITCHER_H
#define RESEARCH_OSC_OSCBITCHER_H

#include <string>
#include "ofMain.h"
#include "ofxOsc.h"

using namespace std;

class oscBitcher
{
public:
    bool isRecievable() ;
    bool isSendable() ;
    const string    &getTextRecieved() ;
    void            setTextRecieved( const string &textRecieved_ );
    const string    &getTextToSend() ;
    void            setTextToSend( const string &textToSend_ );

private:
    bool    recievable_   = false;
    bool    sendable_     = false;
    string  textRecieved_   = "";
    string  textToSend_     = "";
};


#endif //RESEARCH_OSC_OSCBITCHER_H
