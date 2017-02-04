//
// Created by Peter A. Kolski on 01.02.17.
//

#include "bitcherOSC.h"

void bitcherOSC::setup( string &hostSender, int portSender, string adrSender, int portReciever, string adrRecieve )
{
    hostSenderToOther_  = hostSender;
    portSender_         = portSender;
    portReciever_       = portReciever;
    adressReciever_     = adrRecieve;
    adressSender_       = adrSender;

    ofLogVerbose() << logInfo_ << "Host: " << hostSenderToOther_;
    ofLogVerbose() << logInfo_ << "Port Sending to: " << portSender_;
    ofLogVerbose() << logInfo_ << "Port Recieving from: " << portReciever_;
    ofLogVerbose() << logInfo_ << "Adress Sender: " << adressSender_;
    ofLogVerbose() << logInfo_ << "Adress Reciever: " << adressReciever_;

    sender_.setup( hostSenderToOther_, portSender_ );
    reciever_.setup( portReciever_ );
}

void bitcherOSC::update()
{
    textRecieved_ = recieveText();
    sendText( textToSend_ );
}

void bitcherOSC::sendText( string &text )
{
    ofxOscMessage m;
    m.setAddress( adressSender_ );
    m.addStringArg( text );
    sender_.sendMessage( m, false );
}

string bitcherOSC::recieveText()
{
//    ofLogVerbose() << logInfo_ << "Recieving from adress: " << adressReciever_;
    string result = "";
    while ( reciever_.hasWaitingMessages() )
    {
        ofxOscMessage _message;
        reciever_.getNextMessage( _message );
        ofLogVerbose( "Server recieved message " + getOscMsgAsString( _message ) + " from " + _message.getRemoteIp() );

        // check the address of the incoming message
        if (    ( _message.getAddress() == adressReciever_ )
            &&  ( _message.getNumArgs() > 0 )
            &&  ( _message.getArgType( 0 ) == OFXOSC_TYPE_STRING ) )
         {
             result = _message.getArgAsString( 0 ); // TODO check all entries
             ofLogVerbose() << logInfo_ << "message recieved from " << adressReciever_;
         }
        else
        {
            ofLogWarning( "Server got weird message: " + _message.getAddress() );
        }
    }
    return result;
}

const string &bitcherOSC::getTextRecieved()
{
    return textRecieved_;
}

void bitcherOSC::setTextRecieved( const string &textRecieved_ )
{
    bitcherOSC::textRecieved_ = textRecieved_;
}

const string &bitcherOSC::getTextToSend()
{
    return textToSend_;
}

void bitcherOSC::setTextToSend( const string &textToSend_ )
{
    bitcherOSC::textToSend_ = textToSend_;
}

bool bitcherOSC::isRecievable()
{
    return recievable_;
}

bool bitcherOSC::isSendable()
{
    return sendable_;
}

//--------------------------------------------------------------

string bitcherOSC::getOscMsgAsString( ofxOscMessage m )
{
    string msg_string;
    msg_string = m.getAddress();
    msg_string += ":";
    for ( int i = 0; i < m.getNumArgs(); i++ )
    {
        // get the argument type
        msg_string += " " + m.getArgTypeName( i );
        msg_string += ":";
        // display the argument - make sure we get the right type
        if ( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
        {
            msg_string += ofToString( m.getArgAsInt32( i ) );
        }
        else if ( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
        {
            msg_string += ofToString( m.getArgAsFloat( i ) );
        }
        else if ( m.getArgType( i ) == OFXOSC_TYPE_STRING )
        {
            msg_string += m.getArgAsString( i );
        }
        else
        {
            msg_string += "unknown";
        }
    }
    return msg_string;
}

void bitcherOSC::setAdressReciever( const string &adress )
{
    bitcherOSC::adressReciever_ = adress;
}

void bitcherOSC::setAdressSender( const string &adress )
{
    bitcherOSC::adressSender_ = adress;
}

void bitcherOSC::sendPicturePath()
{
    ofxOscMessage m;
    string  adressPicSent = "/recognize";
    string filePathPicSent = "/Users/nesa/Documents/Developer/bloke/pictureOutput/picFromNetwork.jpg";

    m.setAddress( adressPicSent );
    m.addStringArg( filePathPicSent );
    sender_.sendMessage( m, false );

    ofLogVerbose() << logInfo_ << "sent to adress: " << adressPicSent;
    ofLogVerbose() << logInfo_ << "sent message: " << m.getArgAsString( 0 );
}
