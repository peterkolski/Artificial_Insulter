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
    void    setupPicturePath( string host, int portSender, int portReceiver, string adressPath );
    void    setup( int id, string host, int portSender, int portReciever );
    void    nextChatter();
    void    setIsMutantChatbot( bool isMutantChatbot ) { ConversationOSC::isMutantChatbot_ = isMutantChatbot; }
    void    doConversation();
    void    doConversation( string txt, int id );
    void    recieveOscMessages();
    void    sendPictureAnalyserFilePath( string &filePathPicSent );
    void    sendSoundStartLeft( float length );
    void    sendSoundStartRight( float length );
    void    sendStartMutant( string txt1, string txt2 );

    bool    isSoundPlayingLeft()    { return isSoundPlayingLeft_; }
    bool    isSoundPlayingRight()   { return isSoundPlayingRight_; }
    string  getNameSpeaker()        { return getName( idTalker_ ); }
    string  getName( int id );
    const string &getPictureRecievedText1() { return pictureRecievedText1_; }
    const string &getPictureRecievedText2() { return pictureRecievedText2_; }

    const string &getAnswerCurrent() { return answerCurrent_; }
    string getAnswerLeft();
    string getAnswerRight();
    
private:
    void            setTalkerActive( int id ) { idTalker_ = id; }
    string          logInfo_       = "ConversationOSC | ";

    // --- PICTURE
    ofxOscSender    senderPictureAnalysis_;
    ofxOscReceiver  receiverPictureAnalysis_;
    string          adressPicSent_;
    string          adressPicRecieved_ = "/result";
    string          pictureRecievedText1_ = "empty";
    string          pictureRecievedText2_ = "empty";

    // --- SOUND
    void            recieveSoundFinished();
    void            recievePictureFinished();
    bool            isSoundPlayingLeft_   = false;
    bool            isSoundPlayingRight_  = false;
    ofxOscSender    senderSoundConfirmation_;
    ofxOscReceiver  recieverSoundConfirmation_;
    string          hostSound_ = "127.0.0.1";
    int             portSoundSender_ = 40000;
    int             portSoundReciever_ = 40001;
    string          adressSoundLeft_  = "/left";
    string          adressSoundRight_ = "/right";
    string          textSoundDone_ = "done";

    int     talkerMaxAmount_    = 4;
    int     idTalker_           = 0;
    string  answerCurrent_      = "";
    string  answerBefore_       = "";
    bool    isMutantChatbot_    = false;

    vector< std::unique_ptr< bitcherOSC > >       chatterVec_;
    vector< string >            chatterNames_;
};


#endif //ELISAKORA_CONVERSIONOSC_H
