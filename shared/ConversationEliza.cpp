//
// Created by Peter A. Kolski on 11.01.17.
//

#include "ConversationEliza.h"

arstu::ConversationEliza::ConversationEliza()
{
//    talkerVec_.resize( talkerMaxAmount_ );
//    TalkerEliza elisa;
//    TalkerEliza kora;
    talkerVec_.resize( talkerMaxAmount_ );
    talkerVec_[ 0 ] = make_unique< TalkerEliza >();
    talkerVec_[ 1 ] = make_unique< TalkerEliza >();

    talkerNames_.resize( talkerMaxAmount_ );
    talkerNames_[ 0 ] = "Elisa";
    talkerNames_[ 1 ] = "Kora";

    for ( auto &&talker : talkerVec_ )
    {
        talker->start();
    }

    answerCurrent_ = talkerVec_[ 0 ]->getAnswer();
}

string arstu::ConversationEliza::getName( int id )
{
    if ( id < talkerMaxAmount_)
    {
        return talkerNames_[ id ];
    }
    else
    {
        ofLogError() << logNameClass_ << "Wrong name id";
    }
}

int arstu::ConversationEliza::getTalkerCurrentID() const
{
    return talkerCurrentID_;
}

const string &arstu::ConversationEliza::getAnswerCurrent()
{
    return answerCurrent_;
}

string arstu::ConversationEliza::getName()
{
    return getName( talkerCurrentID_ );
}
