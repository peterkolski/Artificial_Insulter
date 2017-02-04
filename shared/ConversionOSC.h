//
// Created by Peter A. Kolski on 05.02.17.
//

#ifndef ELISAKORA_CONVERSIONOSC_H
#define ELISAKORA_CONVERSIONOSC_H

#include "bitcherOSC.h"

class ConversionOSC
{
public:
    ConversionOSC();
    void    next();
    void    doConversation();
    void    doConversation( string txt, int id );

    int     getTalkerCurrentID() const;
    string  getNameSpeaker();
    string  getNameListener();
    string  getName( int id );
    const string &getAnswerBefore();
    const string &getAnswerCurrent();
    const string &getAnswerFromID( int id );


private:
    string  logNameClass_       = "arstu::ConversationEliza => ";
    vector< std::unique_ptr< bitcherOSC > >       talkerVec_;

    vector< string >            talkerNames_;
    void    setTalkerActive( int id );
    int     talkerMaxAmount_    = 2;
    int     idTalker_           = 0;
    int     idOther_         = 1;
    string  answerCurrent_      = "";
    string  answerBefore_       = "";
};


#endif //ELISAKORA_CONVERSIONOSC_H
