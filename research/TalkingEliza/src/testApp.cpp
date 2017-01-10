#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    voice = "Tom";
    
    eliza.load();
    eliza.start();

}

//--------------------------------------------------------------
void testApp::update(){

    
    string userSays;
    std::getline(std::cin, userSays);

    elizaResponse = eliza.ask(userSays);
    cout << elizaResponse;

    
    string cmd = "say -v "+voice+" "+elizaResponse+" ";   // create the command
    system(cmd.c_str());

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    textInput += key;
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
