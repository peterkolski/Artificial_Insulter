//
// Created by Peter A. Kolski on 01.02.17.
//

#include "bitcherOSC.h"

void bitcherOSC::setup( string &hostSendingTo, int portSender, int portReciever )
{
    hostSendSendingTo_  = hostSendingTo;
    portSender_         = portSender;
    portReciever_       = portReciever;

    string adressRecieverTMP = "/answer";
    adressRecieverText_     = adressRecieverTMP + "_text";
    adressRecieverSending_  = adressRecieverTMP + "_sending";
    adressRecieverArrived_  = adressRecieverTMP + "_arrived";

    string adressSenderTMP  = "/original";
    adressSenderText_       = adressSenderTMP + "_text";
    adressSenderSending_    = adressSenderTMP + "_sending";
    adressSenderArrived_    = adressSenderTMP + "_arrived";

    ofLogVerbose() << logInfo_ << "Host: " << hostSendSendingTo_;
    ofLogVerbose() << logInfo_ << "Port Sending to: " << portSender_;
    ofLogVerbose() << logInfo_ << "Port Recieving from: " << portReciever_;
    ofLogVerbose() << logInfo_ << "Adress Sender: " << adressSenderText_;
    ofLogVerbose() << logInfo_ << "Adress Reciever: " << adressRecieverText_;

    sender_.setup( hostSendSendingTo_, portSender_ );
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
    m.setAddress( adressSenderText_ );
    m.addStringArg( text );
    sender_.sendMessage( m, false );
}

string bitcherOSC::recieveText()
{
    string result = "";
    while ( reciever_.hasWaitingMessages() )
    {
        ofxOscMessage _message;
        reciever_.getNextMessage( _message );
        ofLogVerbose( "Server recieved message " + getOscMsgAsString( _message ) + " from " + _message.getRemoteIp() );

        // check the address of the incoming message
        if (    ( _message.getAddress() == adressRecieverText_ )
            &&  ( _message.getNumArgs() > 0 ) )
         {
             for ( int i = 0; i < _message.getNumArgs() ; ++i )
             {
                 if ( _message.getArgType( i ) == OFXOSC_TYPE_STRING )
                 {
                     result = _message.getArgAsString( i );
                     ofLogVerbose() << logInfo_ << "message recieved from " << adressRecieverText_ << " => " << result;
                 }
             }
         }
        else
        {
            ofLogWarning() << logInfo_ << "Message did't contain anything: " << _message.getAddress();
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
    bitcherOSC::adressRecieverText_ = adress;
}

void bitcherOSC::setAdressSender( const string &adress )
{
    bitcherOSC::adressSenderText_ = adress;
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
