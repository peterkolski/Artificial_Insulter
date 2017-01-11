//
// Created by Peter A. Kolski on 11.01.17.
//

#include "TalkerEliza.h"

// -----------------------------------------------
/// Input file should be loaded
arstu::TalkerEliza::TalkerEliza()
{
    eliza_.load();
}

// -----------------------------------------------
/// Wrapping ofxEliza methods
/// \return
string arstu::TalkerEliza::start()
{
    answer_ = eliza_.start();
    return getAnswer();
}

// -----------------------------------------------
/// Wrapping ofxEliza methods
/// \param text
/// \return
string arstu::TalkerEliza::ask( string text )
{
    answer_ = eliza_.ask( text );
    return getAnswer();
}

const string &arstu::TalkerEliza::getAnswer()
{
    return answer_;
}
