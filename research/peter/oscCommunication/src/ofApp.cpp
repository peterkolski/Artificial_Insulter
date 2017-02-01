#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

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


//--------------------------------------------------------------
//string ofApp::getOscMsgAsString(ofxOscMessage m){
//	string msg_string;
//	msg_string = m.getAddress();
//	msg_string += ":";
//	for(int i = 0; i < m.getNumArgs(); i++){
//		// get the argument type
//		msg_string += " " + m.getArgTypeName(i);
//		msg_string += ":";
//		// display the argument - make sure we get the right type
//		if(m.getArgType(i) == OFXOSC_TYPE_INT32){
//			msg_string += ofToString(m.getArgAsInt32(i));
//		}
//		else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
//			msg_string += ofToString(m.getArgAsFloat(i));
//		}
//		else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
//			msg_string += m.getArgAsString(i);
//		}
//		else{
//			msg_string += "unknown";
//		}
//	}
//	return msg_string;
//}
//
//void ofApp::broadcastReceivedMessage(string chatmessage){
//
//	//create a new OSC message
//	ofxOscMessage m;
//	m.setAddress("/chatlog");
//	m.addStringArg(chatmessage);
//
//	//Send message to all known hosts
//	// use another port to avoid a localhost loop
//	for(unsigned int i = 0; i < knownClients.size(); i++){
//		serverSender.setup(knownClients[i], serverRecvPort + 1);
//		m.setRemoteEndpoint(knownClients[i], serverRecvPort + 1);
//		serverSender.sendMessage(m, false);
//		ofLogVerbose("Server broadcast message " + m.getArgAsString(0) + " to " + m.getRemoteIp()
//					 + ":" + ofToString(m.getRemotePort()));
//	}
//}
