#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bitchElisa.setTextRecieved( "reciever" );
    bitchElisa.setTextToSend( "sender" );

    ofLogNotice() << bitchElisa.isRecievable();
    ofLogNotice() << bitchElisa.isSendable();
    ofLogNotice() << bitchElisa.getTextRecieved();
    ofLogNotice() << bitchElisa.getTextToSend();

    string host         = "localhost";
    string adrSender    = "/transform";
    string adrReciever  = "/python_here";   //TODO adress can be the same

    auto portONE  = 9000;
    auto portTWO  = 9001;

    bitchElisa.setup( host, portONE, portTWO );
    bitchKora.setup( host, portTWO, portONE );
}

//--------------------------------------------------------------
void ofApp::update()
{
    bitchElisa.update();
    bitchKora.update();
}

//--------------------------------------------------------------
void ofApp::draw(){


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	// if we didn't hit return, add the key to our string
//	if(key != OF_KEY_RETURN){
//		// some trickery: ignore the backspace key
//		if(key != OF_KEY_BACKSPACE){
//			clientTyping += key;
//		}
//		else{
//			if(clientTyping.size() > 0){
//				clientTyping.erase(clientTyping.end() - 1);
//			}
//		}
//	}
//	// hit Return, time to send the osc message
//	else{
//		// to send a string, create an ofxOscMessage object, give it an address
//		// and add a string argument to the object
//		ofxOscMessage m;
//		m.setAddress("/typing");
//		m.addStringArg(clientTyping);
//		clientSender.sendMessage(m, false);
//
//		// clear out "typing"
//		clientTyping = "";
//	}
}
