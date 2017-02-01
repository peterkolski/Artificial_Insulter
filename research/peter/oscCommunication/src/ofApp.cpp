#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 4 );

    bitchElisa.setTextRecieved( "WRONG" );
    bitchKora.setTextRecieved( "WRONG" );
    bitchElisa.setTextToSend( "Fuck off - from Elisa" );
    bitchKora.setTextToSend( "Lick my ass - from Kora" );

    string host         = "localhost";
    string adressONE    = "/python_here";
    string adressTWO    = "/transform";

    auto portONE  = 9000;
    auto portTWO  = 9001;

    bitchElisa.setup( host, portONE, portTWO, adressONE, adressTWO );
    bitchKora.setup( host, portTWO, portONE, adressTWO, adressONE );
}

//--------------------------------------------------------------
void ofApp::update()
{
    bitchElisa.update();
    bitchKora.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapStringHighlight( "Elisa: " + bitchElisa.getTextRecieved(), 100, 100 );
    ofDrawBitmapStringHighlight( "Kora: " + bitchKora.getTextRecieved(), 100, 200 );

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
