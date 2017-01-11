//
// Created by Peter A. Kolski on 11.01.17.
//

#ifndef ELISAKORA_CONVERSATIONELIZA_H
#define ELISAKORA_CONVERSATIONELIZA_H

#include "TalkerEliza.h"

namespace arstu
{
class ConversationEliza
{
public:
    ConversationEliza();

    int     getTalkerCurrentID() const;
    string  getName( int id );


private:
    string  logNameClass_       = "arstu::ConversationEliza => ";
    vector< TalkerEliza >       talkerVec_;
    vector< string >            talkerNames_;

    int     talkerMaxAmount_    = 2;
    int     talkerCurrentID_     = 0;


};
}


#endif //ELISAKORA_CONVERSATIONELIZA_H
