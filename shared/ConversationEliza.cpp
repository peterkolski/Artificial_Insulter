//
// Created by Peter A. Kolski on 11.01.17.
//

#include "ConversationEliza.h"

arstu::ConversationEliza::ConversationEliza()
{
    talkerVec_.resize( talkerMaxAmount_ );
    talkerNames_.resize( talkerMaxAmount_ );
    talkerNames_[ 0 ] = "Elisa";
    talkerNames_[ 1 ] = "Kora";

    for ( auto &&talker : talkerVec_ )
    {
        talker.start();
    }
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
    return talkerCurrentID_;
}
