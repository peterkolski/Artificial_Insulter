#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    voice = "Tom";
    
    eliza.load();
    elizaResponse = eliza.start();

}

//--------------------------------------------------------------
void testApp::update(){


//    std::getline(std::cin, userSays);

}

//--------------------------------------------------------------
void testApp::draw(){

    ofDrawBitmapStringHighlight( elizaResponse, 100, 100);

    if ( shouldSpeak )
    {
        string cmd = "say -v "+voice+" "+elizaResponse+" ";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == OF_KEY_RETURN )
    {
        elizaResponse = eliza.ask( textInput );
        shouldSpeak = true;

    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
