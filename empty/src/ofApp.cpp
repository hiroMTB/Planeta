#include "ofApp.h"
#include "Util.h"

//--------------------------------------------------------------
void ofApp::setup(){

    cam.setPosition(0,0,10);

    cout << "UP      " << cam.getUpDir() << endl;
    cout << "LookAt  " << cam.getLookAtDir() << endl;
    cout << cam.getModelViewMatrix() << endl;

    cam.lookAt(glm::vec3(0,0,0), glm::vec3(0,-1,0));

    cout << endl << "After lookAt" << endl;
    cout << "UP     " << cam.getUpDir() << endl;
    cout << "LookAt " << cam.getLookAtDir() << endl;
    cout << cam.getModelViewMatrix() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    
    Util::drawAxis(1);
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
