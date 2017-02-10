//
// Created by Peter A. Kolski on 05.02.17.
//

#include "bitcherOSC.h"
#include "ConversationOSC.h"

ConversationOSC::ConversationOSC() {
    talkerVec_.resize( talkerMaxAmount_ );
    talkerVec_[ 0 ] = make_unique< bitcherOSC >();
    talkerVec_[ 1 ] = make_unique< bitcherOSC >();
    talkerVec_[ 2 ] = make_unique< bitcherOSC >();
    talkerVec_[ 3 ] = make_unique< bitcherOSC >();

    talkerNames_.resize( talkerMaxAmount_ );
    talkerNames_[ 0 ] = "Left";
    talkerNames_[ 1 ] = "Right";
    talkerNames_[ 2 ] = "Left";
    talkerNames_[ 3 ] = "Right";

    answerCurrent_ = talkerVec_[ 0 ]->getAnswer();

    // --- SETUP Sound control
    senderSound_.setup( hostSound_, portSoundSender_ );
    recieverSound_.setup( portSoundReciever_ );
}

void ConversationOSC::setup( int id, string host, int portSender, int portReciever )
{
    if ( id < talkerMaxAmount_)
    {
        talkerVec_[ id ]->setup( host, portSender, portReciever );
    }
    else {
        ofLogError() << logInfo_ << "Setup: ID invalid";
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
        ofLogError() << logInfo_ << "Wrong name id";
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
    if ( talkerVec_[ idTalker_ ]->switchChatbot() )
    {
        isMutantChatbot_ = !isMutantChatbot_;
        ofLogVerbose() << logInfo_ << "Chatbots switched " << isMutantChatbot_;
    }

    if ( isMutantChatbot_ )
    {
        if ( idTalker_ == 2 )
        {
            idTalker_   = 3;
            idOther_ = 2;
        }
        else {
            idTalker_   = 2;
            idOther_ = 3;
        }
    }
    else
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
    ofLogVerbose() << logInfo_ << "Next chatbot " << idTalker_ << " Mutant: " << isMutantChatbot_;
}

void ConversationOSC::doConversation()
{
    answerBefore_ = answerCurrent_;
    doConversation( answerBefore_, idTalker_ );
}

void ConversationOSC::doConversation( string txt, int id )
{
    setTalkerActive( id );
    answerCurrent_ = talkerVec_[ idTalker_ ]->ask( txt );   //TODO is this correct? Passing
}

const string &ConversationOSC::getAnswerFromID( int id )
{
    if ( id < talkerMaxAmount_ )
    {
        return talkerVec_[ id ]->getAnswer();
    }
    else
    {
        ofLogError( ) << logInfo_ << "Wrong ID";
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

void ConversationOSC::recieveMessages()
{
    talkerVec_[ idTalker_ ]->recieveText();
    answerCurrent_ = talkerVec_[ idTalker_ ]->getAnswer();

    recieveSoundFinished();
}

void ConversationOSC::setupPicturePath( string host, int portSender, string adressPath )
{
    senderPictureAnalysis_.setup( host, portSender );
    adressPicSent_ = adressPath;
}

void ConversationOSC::sendPicturePath( string &filePathPicSent )
{
    ofxOscMessage m;

    m.setAddress( adressPicSent_ );
    m.addStringArg( filePathPicSent );
    senderPictureAnalysis_.sendMessage( m, false );

    ofLogVerbose() << logInfo_ << "sent to adress: " << adressPicSent_;
    ofLogVerbose() << logInfo_ << "sent message: " << m.getArgAsString( 0 );
}

void ConversationOSC::sendSoundStartLeft( int length )
{
    ofLogVerbose() << logInfo_ << "Sending Sound LEFT | port " << portSoundSender_ << " | adr " << adressSoundLeft_;
    ofLogVerbose() << logInfo_ << "length: " << length;

    isSoundPlayingLeft_ = true;
    ofxOscMessage m;
    m.setAddress( adressSoundLeft_ );
    m.addStringArg( "start" );
    m.addIntArg( length );
    senderSound_.sendMessage( m, false );
}

void ConversationOSC::sendSoundStartRight( int length )
{
    ofLogVerbose() << logInfo_ << "Sending Sound RIGHT | port " << portSoundSender_ << " | adr " << adressSoundRight_;
    ofLogVerbose() << logInfo_ << "length: " << length;

    isSoundPlayingRight_ = true;
    ofxOscMessage m;
    m.setAddress( adressSoundRight_ );
    m.addStringArg( "start" );
    m.addIntArg( length );
    senderSound_.sendMessage( m, false );
}

void ConversationOSC::recieveSoundFinished()
{
    while ( recieverSound_.hasWaitingMessages() )
    {
        ofxOscMessage _message;
        recieverSound_.getNextMessage( _message );

        // check the address of the incoming message
        if ( _message.getNumArgs() > 0 )
        {
            if ( ( _message.getAddress() == adressSoundLeft_ ) && ( _message.getArgAsString( 0 ) == textSoundDone_ ) )
            {
                isSoundPlayingLeft_ = false;
                ofLogVerbose() << logInfo_ << "message recieved from " << adressSoundLeft_ << " => " << textSoundDone_;
            }
            if ( ( _message.getAddress() == adressSoundRight_ ) && ( _message.getArgAsString( 0 ) == textSoundDone_ ) )
            {
                isSoundPlayingRight_ = false;
                ofLogVerbose() << logInfo_ << "message recieved from " << adressSoundRight_ << " => " << textSoundDone_;
            }
        }
        else
        {
            ofLogWarning() << logInfo_ << "Message did't contain anything: " << _message.getAddress();
        }
    }
}

bool ConversationOSC::isSoundPlayingLeft()
{
    return isSoundPlayingLeft_;
}

bool ConversationOSC::isSoundPlayingRight()
{
    return isSoundPlayingRight_;
}

void ConversationOSC::sendStartMutant( string txt1, string txt2 )
{
    idTalker_ = 2;
    talkerVec_.at( idTalker_ )->startMutant( txt1, txt2 );
}

void ConversationOSC::setIsMutantChatbot( bool isMutantChatbot )
{
    ConversationOSC::isMutantChatbot_ = isMutantChatbot;
}

