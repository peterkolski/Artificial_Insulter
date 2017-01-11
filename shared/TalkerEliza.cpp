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
    return eliza_.start();
}

// -----------------------------------------------
/// Wrapping ofxEliza methods
/// \param text
/// \return
string arstu::TalkerEliza::ask( string text )
{
    return eliza_.ask( text );
}
