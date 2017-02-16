//
// Created by Peter A. Kolski on 05.02.17.
//

#include "bitcherOSC.h"
#include "ConversationOSC.h"
/// Init of instances of the chatter, names and sound communication
ConversationOSC::ConversationOSC() {
    chatterVec_.resize( talkerMaxAmount_ );
    chatterVec_[ 0 ] = make_unique< bitcherOSC >();
    chatterVec_[ 1 ] = make_unique< bitcherOSC >();
    chatterVec_[ 2 ] = make_unique< bitcherOSC >();
    chatterVec_[ 3 ] = make_unique< bitcherOSC >();

    chatterNames_.resize( talkerMaxAmount_ );
    chatterNames_[ 0 ] = "Left";
    chatterNames_[ 1 ] = "Right";
    chatterNames_[ 2 ] = "Left";
    chatterNames_[ 3 ] = "Right";

    answerCurrent_ = chatterVec_[ 0 ]->getAnswer();

    // --- SETUP Sound control
    senderSoundConfirmation_.setup( hostSound_, portSoundSender_ );
    recieverSoundConfirmation_.setup( portSoundReciever_ );
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::setup( int id, string host, int portSender, int portReciever )
{
    if ( id < talkerMaxAmount_)
    {
        chatterVec_[ id ]->setup( host, portSender, portReciever );
    }
    else {
        ofLogError() << logInfo_ << "Setup: ID invalid";
    }
}

//----------------------------------------------------------------------------------------------------------------------

string ConversationOSC::getName( int id )
{
    if ( id < talkerMaxAmount_)
    {
        return chatterNames_[ id ];
    }
    else
    {
        ofLogError() << logInfo_ << "Wrong name id";
    }
}

//----------------------------------------------------------------------------------------------------------------------

/// Switching the chatter
void ConversationOSC::nextChatter()
{
    if ( chatterVec_[ idTalker_ ]->switchMutantChatbot() )
    {
        isMutantChatbot_ = !isMutantChatbot_;
        ofLogVerbose() << logInfo_ << "Chatbots switched " << isMutantChatbot_;
    }

    if ( isMutantChatbot_ )
    {
        if ( idTalker_ == 2 )
        {
            idTalker_   = 3;
        }
        else {
            idTalker_   = 2;
        }
    }
    else
    {
        if ( idTalker_ == 0 )
        {
            idTalker_   = 1;
        }
        else {
            idTalker_   = 0;
        }
    }
    ofLogVerbose() << logInfo_ << "Next chatbot " << idTalker_ << "  | Is mutant: " << isMutantChatbot_;
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::doConversation()
{
    answerBefore_ = answerCurrent_;
    doConversation( answerBefore_, idTalker_ );
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::doConversation( string txt, int id )
{
    setTalkerActive( id );
    answerCurrent_ = chatterVec_[ idTalker_ ]->ask( txt );   //TODO is this correct? Passing
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::recieveMessages()
{
    if (chatterVec_[ idTalker_ ]->recieveOscText() )
    {
        answerCurrent_ = chatterVec_[ idTalker_ ]->getAnswer();
    }

//    answerCurrent_ = chatterVec_[ idTalker_ ]->getAnswer(); // TODO Maybe here I should not write all the time

    recieveSoundFinished();
    recievePictureFinished();
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::setupPicturePath( string host, int portSender, int portReceiver, string adressPath )
{
    ofLogVerbose() << "Pic Receive port " << portReceiver << " | adress: " << adressPicRecieved_;
    senderPictureAnalysis_.setup( host, portSender );
    receiverPictureAnalysis_.setup( portReceiver );
    adressPicSent_ = adressPath;
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::sendPicturePath( string &filePathPicSent )
{
    ofxOscMessage m;

    m.setAddress( adressPicSent_ );
    m.addStringArg( filePathPicSent );
    senderPictureAnalysis_.sendMessage( m, false );

    ofLogVerbose() << logInfo_ << "sent to adress: " << adressPicSent_;
    ofLogVerbose() << logInfo_ << "sent message: " << m.getArgAsString( 0 );
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::sendSoundStartLeft( float length )
{
    ofLogVerbose() << logInfo_ << "Sending Sound LEFT | port " << portSoundSender_ << " | adr " << adressSoundLeft_;
    ofLogVerbose() << logInfo_ << "length: " << length;

    isSoundPlayingLeft_ = true;
    ofxOscMessage m;
    m.setAddress( adressSoundLeft_ );
    m.addStringArg( "start" );
    m.addFloatArg( length );
    senderSoundConfirmation_.sendMessage( m, false );
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::sendSoundStartRight( float length )
{
    ofLogVerbose() << logInfo_ << "Sending Sound RIGHT | port " << portSoundSender_ << " | adr " << adressSoundRight_;
    ofLogVerbose() << logInfo_ << "length: " << length;

    isSoundPlayingRight_ = true;
    ofxOscMessage m;
    m.setAddress( adressSoundRight_ );
    m.addStringArg( "start" );
    m.addFloatArg( length );
    senderSoundConfirmation_.sendMessage( m, false );
}

//----------------------------------------------------------------------------------------------------------------------


void ConversationOSC::recieveSoundFinished()
{
    while ( recieverSoundConfirmation_.hasWaitingMessages() )
    {
        ofxOscMessage _message;
        recieverSoundConfirmation_.getNextMessage( _message );

        // check the address of the incoming message
        if ( _message.getNumArgs() > 0 )
        {
            if ( ( _message.getAddress() == adressSoundLeft_ ) && ( _message.getArgAsString( 0 ) == textSoundDone_ ) )
            {
                isSoundPlayingLeft_ = false;
                ofLogVerbose() << logInfo_ << "Sound message from " << adressSoundLeft_ << " Done? " << textSoundDone_;
            }
            if ( ( _message.getAddress() == adressSoundRight_ ) && ( _message.getArgAsString( 0 ) == textSoundDone_ ) )
            {
                isSoundPlayingRight_ = false;
                ofLogVerbose() << logInfo_ << "Sound message from " << adressSoundRight_ << " Done? " << textSoundDone_;
            }
        }
        else
        {
            ofLogWarning() << logInfo_ << "Message did't contain anything: " << _message.getAddress();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::recievePictureFinished()
{
    while ( receiverPictureAnalysis_.hasWaitingMessages() )
    {
        ofxOscMessage _message;
        receiverPictureAnalysis_.getNextMessage( _message );

        if ( _message.getNumArgs() > 0 )
        {
            if ( ( _message.getAddress() == adressPicRecieved_ ) )
            {
                pictureRecievedText1_ = _message.getArgAsString( 0 );
                pictureRecievedText2_ = _message.getArgAsString( 1 );
                ofLogVerbose() << logInfo_ << "Picture message from " << adressPicRecieved_;
                ofLogVerbose() << logInfo_ << "Picture Text1: " << pictureRecievedText1_;
                ofLogVerbose() << logInfo_ << "Picture Text2: " << pictureRecievedText2_;

                sendStartMutant( pictureRecievedText1_, pictureRecievedText2_ );
                setIsMutantChatbot( true );
            }
        }
        else
        {
            ofLogWarning() << logInfo_ << "Message did't contain anything: " << _message.getAddress();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void ConversationOSC::sendStartMutant( string txt1, string txt2 )
{
    idTalker_ = 2;
    chatterVec_.at( idTalker_ )->startMutant( txt1, txt2 );
}

//----------------------------------------------------------------------------------------------------------------------

string ConversationOSC::getAnswerLeft()
{
    if ( isMutantChatbot_ )
    {
        return chatterVec_[ 2 ]->getAnswer();
    }
    else {
        return chatterVec_[ 0 ]->getAnswer();
    }
}

//----------------------------------------------------------------------------------------------------------------------

string ConversationOSC::getAnswerRight()
{
    if ( isMutantChatbot_ )
    {
        return chatterVec_[ 3 ]->getAnswer();
    }
    else {
        return chatterVec_[ 1 ]->getAnswer();
    }
}

