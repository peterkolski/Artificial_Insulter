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
