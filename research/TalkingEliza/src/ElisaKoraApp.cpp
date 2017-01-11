#include "ElisaKoraApp.h"

//--------------------------------------------------------------
void ElisaKoraApp::setup(){
    voice = "Tom";
    
    eliza.load();
    elizaResponse = eliza.start();

}

//--------------------------------------------------------------
void ElisaKoraApp::update(){


//    std::getline(std::cin, userSays);

}

//--------------------------------------------------------------
void ElisaKoraApp::draw(){

    ofDrawBitmapStringHighlight( elizaResponse, 100, 100);

    ofDrawBitmapStringHighlight( textInput, 100, 200);

//    speak( );
}

void ElisaKoraApp::speak()
{
    if ( shouldSpeak )
    {
        string cmd = "say -v " + voice + " " + elizaResponse + " ";   // create the command
        system(cmd.c_str());
        shouldSpeak = false;
        textInput = "";
    }
}

//--------------------------------------------------------------
void ElisaKoraApp::keyPressed(int key){
    textInput += key;

    if ( key == OF_KEY_RETURN )
    {
        elizaResponse = eliza.ask( textInput );
        shouldSpeak = true;
    }
}

//--------------------------------------------------------------
void ElisaKoraApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ElisaKoraApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ElisaKoraApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ElisaKoraApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ElisaKoraApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ElisaKoraApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ElisaKoraApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ElisaKoraApp::dragEvent(ofDragInfo dragInfo){

}
