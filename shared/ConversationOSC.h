//
// Created by Peter A. Kolski on 05.02.17.
//

#ifndef ELISAKORA_CONVERSIONOSC_H
#define ELISAKORA_CONVERSIONOSC_H

#include "bitcherOSC.h"
#include "ofxOsc.h"

class ConversationOSC
{
public:
    ConversationOSC();
    void    setupPicturePath( string host, int portSender, string adressPath );
    void    setup( int id, string host, int portSender, int portReciever );
    void    next();
    void    doConversation();
    void    doConversation( string txt, int id );
    void    recieveMessages();
    void    sendPicturePath( string &filePathPicSent );
    void    sendSoundStartLeft( int length );
    void    sendSoundStartRight( int length );

    int     getTalkerCurrentID() const;
    string  getNameSpeaker();
    string  getNameListener();
    string  getName( int id );
    const string &getAnswerBefore();
    const string &getAnswerCurrent();
    const string &getAnswerFromID( int id );

private:
    void            setTalkerActive( int id );
    string          logInfo_       = "ConversationOSC | ";
    ofxOscSender    senderPictureAnalysis_;
    string          adressPicSent_;

    // --- SOUND
    void recieveSoundFinished();
    bool            isSoundPlayingLeft_     = false;
    bool            isSoundPlayingRight_  = false;
    ofxOscSender    senderSound_;
    ofxOscReceiver  recieverSound_;
    string          hostSound_ = "127.0.0.1";
    int             portSoundSender_ = 40000;
    int             portSoundReciever_ = 40001;
    string          adressSoundLeft_  = "/left";
    string          adressSoundRight_ = "/right";
    string          textSoundDone_ = "done";

    int     talkerMaxAmount_    = 2;
    int     idTalker_           = 0;
    int     idOther_         = 1;
    string  answerCurrent_      = "";
    string  answerBefore_       = "";

    vector< std::unique_ptr< bitcherOSC > >       talkerVec_;
    vector< string >            talkerNames_;
};


#endif //ELISAKORA_CONVERSIONOSC_H
