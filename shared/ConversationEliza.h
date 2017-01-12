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

    void    next();

    int     getTalkerCurrentID() const;
    string  getNameSpeaker();
    string  getNameListener();
    string  getName( int id );
    const string &getAnswerBefore();
    const string &getAnswerCurrent();


private:
    string  logNameClass_       = "arstu::ConversationEliza => ";
    vector< std::unique_ptr< TalkerEliza > >       talkerVec_;
    vector< string >            talkerNames_;

    int     talkerMaxAmount_    = 2;
    int     idTalker_           = 0;
    int     idListener_         = 1;
    string  answerCurrent_      = "";
    string  answerBefore_       = "";
};
}


#endif //ELISAKORA_CONVERSATIONELIZA_H
