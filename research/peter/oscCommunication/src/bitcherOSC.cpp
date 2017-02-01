//
// Created by Peter A. Kolski on 01.02.17.
//

#include "bitcherOSC.h"

void bitcherOSC::setup( string &hostSender, int portSender, int portReciever )
{
    hostSenderToOther_  = hostSender;
    portSender_         = portSender;
    portReciever_       = portReciever;

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
    m.setAddress( adress_ );
    m.addStringArg( text );
    sender_.sendMessage( m, false );
}

string bitcherOSC::recieveText()
{
    while ( reciever_.hasWaitingMessages() )
    {
        ofxOscMessage _message;
        reciever_.getNextMessage( &_message ); //TODO alternative code

        //Log received message for easier debugging of participants' messages:
        ofLogVerbose( "Server recvd msg " + getOscMsgAsString( _message ) + " from " + _message.getRemoteIp() );

        // check the address of the incoming message
        if ( _message.getAddress() == adress_ )
        {
            if ( _message.getNumArgs() > 0 )
            {
                if ( _message.getArgType( 0 ) == OFXOSC_TYPE_STRING )
                {
                    _message.getArgAsString( 0 );
                }
            }
        }
        else
        {
            ofLogWarning( "Server got weird message: " + _message.getAddress() );
        }
    }
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

void bitcherOSC::setAdress( const string &adress )
{
    bitcherOSC::adress_ = adress;
}
