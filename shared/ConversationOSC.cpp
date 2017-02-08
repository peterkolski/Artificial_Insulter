//
// Created by Peter A. Kolski on 05.02.17.
//

#include "ConversationOSC.h"

ConversationOSC::ConversationOSC() {
    talkerVec_.resize( talkerMaxAmount_ );
    talkerVec_[ 0 ] = make_unique< bitcherOSC >();
    talkerVec_[ 1 ] = make_unique< bitcherOSC >();

    talkerNames_.resize( talkerMaxAmount_ );
    talkerNames_[ 0 ] = "Elisa";
    talkerNames_[ 1 ] = "Kora";

    answerCurrent_ = talkerVec_[ 0 ]->getAnswer();
}

void ConversationOSC::setup( int id, string host, int portSender, int portReciever )
{
    if ( id < talkerMaxAmount_)
    {
        talkerVec_[ id ]->setup( host, portSender, portReciever );
    }
    else {
        ofLogError() << logNameClass_ << "Setup: ID invalid";
    }
}

string ConversationOSC::getName( int id )
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

int ConversationOSC::getTalkerCurrentID() const
{
    return idTalker_;
}

string ConversationOSC::getNameSpeaker()
{
    return getName( idTalker_ );
}

string ConversationOSC::getNameListener()
{
    return getName( idOther_ );
}


const string &ConversationOSC::getAnswerCurrent()
{
    return answerCurrent_;
}

const string &ConversationOSC::getAnswerBefore()
{
    return answerBefore_;
}

void ConversationOSC::next()
{
    if ( idTalker_ == 0 )
    {
        idTalker_   = 1;
        idOther_ = 0;
    }
    else {
        idTalker_   = 0;
        idOther_ = 1;
    }
}

void ConversationOSC::doConversation()
{
    answerBefore_ = answerCurrent_;
    doConversation( answerBefore_, idTalker_ );
}

void ConversationOSC::doConversation( string txt, int id )
{
    setTalkerActive( id );
    answerCurrent_ = talkerVec_[ idTalker_ ]->ask( txt );
}

const string &ConversationOSC::getAnswerFromID( int id )
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

void ConversationOSC::setTalkerActive( int id )
{
    idTalker_ = id;
    if ( idTalker_ == 0 )
    {
        idOther_ = 1;
    }
    else
    {
        idOther_ = 0;
    }
}

void ConversationOSC::recieveText()
{
    talkerVec_[ idTalker_ ]->recieveText();
    answerCurrent_ = talkerVec_[ idTalker_ ]->getAnswer();
}

