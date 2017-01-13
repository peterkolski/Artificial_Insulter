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
    return idTalker_;
}

string arstu::ConversationEliza::getNameSpeaker()
{
    return getName( idTalker_ );
}

string arstu::ConversationEliza::getNameListener()
{
    return getName( idListener_ );
}

const string &arstu::ConversationEliza::getAnswerCurrent()
{
    return answerCurrent_;
}


const string &arstu::ConversationEliza::getAnswerBefore()
{
    return answerBefore_;
}

void arstu::ConversationEliza::next()
{
    if ( idTalker_ == 0 )
    {
        idTalker_   = 1;
        idListener_ = 0;
    }
    else {
        idTalker_   = 0;
        idListener_ = 1;
    }
}

void arstu::ConversationEliza::doConversation()
{
    answerBefore_ = answerCurrent_;
    doConversation( answerBefore_ );
}

void arstu::ConversationEliza::doConversation( string txt )
{
    answerCurrent_ = talkerVec_[ idTalker_ ]->ask( txt );
}

const string &arstu::ConversationEliza::getAnswerFromID( int id )
{
    if ( id < talkerMaxAmount_ )
    {
        return talkerVec_[ id ]->getAnswer();
    }
    else
    {
        ofLogError( ) << logNameClass_ << "Wrong ID";
        return "";

    }
}

void arstu::ConversationEliza::tell( string txt, int id )
{
    setTalkerActive( id );
    doConversation( txt );
}

void arstu::ConversationEliza::setTalkerActive( int id )
{
    idTalker_ = id;
    if ( idTalker_ == 0 )
    {
        idListener_ = 1;
    }
    else
    {
        idListener_ = 0;
    }
}


