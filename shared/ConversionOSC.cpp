//
// Created by Peter A. Kolski on 05.02.17.
//

#include "ConversionOSC.h"

ConversionOSC::ConversionOSC() {
    
}


string ConversionOSC::getName( int id )
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

int ConversionOSC::getTalkerCurrentID() const
{
    return idTalker_;
}

string ConversionOSC::getNameSpeaker()
{
    return getName( idTalker_ );
}

string ConversionOSC::getNameListener()
{
    return getName( idOther_ );
}

const string &ConversionOSC::getAnswerCurrent()
{
    return answerCurrent_;
}


const string &ConversionOSC::getAnswerBefore()
{
    return answerBefore_;
}

void ConversionOSC::next()
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

void ConversionOSC::doConversation()
{
    answerBefore_ = answerCurrent_;
    doConversation( answerBefore_, idTalker_ );
}

void ConversionOSC::doConversation( string txt, int id )
{
    setTalkerActive( id );
    answerCurrent_ = talkerVec_[ idTalker_ ]->ask( txt );
}

const string &ConversionOSC::getAnswerFromID( int id )
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

void ConversionOSC::setTalkerActive( int id )
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

