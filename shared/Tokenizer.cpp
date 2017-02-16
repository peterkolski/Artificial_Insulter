//
// Created by Peter A. Kolski on 16.02.17.
//

#include "Tokenizer.h"

string tokenizer( string input, int maxChar )
{
    if (!input.size()) {
        return "";
    }
    stringstream sStream;
    sStream << input[0];
    for (int i = 1; i < input.size(); i++)
    {
//        if ( ( i > maxChar ) && ( input[i] == ' ' ) )
        if ( i % maxChar == 0 )
        {
            sStream << "\n" << input[i];
        }
        else
        {
            sStream << input[i];
        }
    }
    return ofToString( sStream.str() );
}

