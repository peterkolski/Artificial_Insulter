#include "testApp.h"

static string voices[24] = {"Agnes", "Albert", "Alex", "Bad News", "Bahh", "Bells", "Boing", "Bruce", "Bubbles", "Cellos", "Deranged", "Fred", "Good News", "Hysterical", "Junior", "Kathy", "Pipe Organ", "Princess", "Ralph", "Trinoids", "Vicki", "Victoria", "Whisper", "Zarvox"};

//--------------------------------------------------------------
void testApp::setup(){
    
    font.loadFont("verdana.ttf", 12);
    voice = "Vicki";
    
    eliza.load();
    eliza.start();

}

//--------------------------------------------------------------
void testApp::update(){

    
    string userSays;
    std::getline(std::cin, userSays);
    elizaResponse = eliza.ask(userSays);
    cout << elizaResponse;

    
#ifdef TARGET_OSX
    string cmd = "say -v "+voice+" "+elizaResponse+" ";   // create the command
    system(cmd.c_str());
#endif
#ifdef TARGET_WIN32
    string cmd = "data\\SayStatic.exe "+elizaResponse+" ";   // create the command
    cout << cmd << endl;
    system(cmd.c_str());
#endif
    
}

//--------------------------------------------------------------
void testApp::draw(){
    // center the word on the screen
    float x = (ofGetWidth() - font.stringWidth(elizaResponse)) / 2;
    float y = ofGetHeight() / 2;
    
    // draw the word
    ofSetColor(0);
    //font.drawString(words[step], x, y);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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