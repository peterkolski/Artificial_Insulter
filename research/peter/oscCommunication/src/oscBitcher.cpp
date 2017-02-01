//
// Created by Peter A. Kolski on 01.02.17.
//

#include "oscBitcher.h"

void oscBitcher::setup( string &hostSender, int portSender, int portReciever )
{
    hostSenderToOther_  = hostSender;
    portSender_         = portSender;
    portReciever_       = portReciever;

    sender_.setup( hostSenderToOther_, portSender_ );
    reciever_.setup( portReciever_ );
}

const string &oscBitcher::getTextRecieved()
{
    return textRecieved_;
}

void oscBitcher::setTextRecieved( const string &textRecieved_ )
{
    oscBitcher::textRecieved_ = textRecieved_;
}

const string &oscBitcher::getTextToSend()
{
    return textToSend_;
}

void oscBitcher::setTextToSend( const string &textToSend_ )
{
    oscBitcher::textToSend_ = textToSend_;
}

bool oscBitcher::isRecievable()
{
    return recievable_;
}

bool oscBitcher::isSendable()
{
    return sendable_;
}
