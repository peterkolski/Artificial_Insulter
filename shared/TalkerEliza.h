//
// Created by Peter A. Kolski on 11.01.17.
//

#ifndef ELISAKORA_TALKERELIZA_H
#define ELISAKORA_TALKERELIZA_H

#include "ofMain.h"
#include "ofxEliza.h"

namespace arstu
{

class TalkerEliza
{
public:
    TalkerEliza();

    string          start();
    string          ask( string text );
    const string    &getAnswer();

private:
    ofxEliza eliza_;
    string  answer_ = "";
};

}


#endif //ELISAKORA_TALKERELIZA_H
