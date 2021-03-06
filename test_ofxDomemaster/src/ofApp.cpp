#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetColor(255);
    
    sphere.setScale(.5);
    sphere.setResolution(50);
    sphere.setOrientation(ofVec3f(90,0,0));

    domemaster.setup();
    domemaster.setCameraPosition(0,0,10);
    domemaster.resize(500, 500);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i=0; i<domemaster.renderCount; i++){
        domemaster.begin(i);
            drawScene();
        domemaster.end(i);
    }
    
    domemaster.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene(){
    sphere.drawWireframe();
    
    ofSetColor(255, 0, 0);
    ofDrawLine(glm::vec3(0,0,0), glm::vec3(10,0,0) );
    
    ofSetColor(0, 255, 0);
    ofDrawLine(glm::vec3(0,0,0), glm::vec3( 0,10,0) );
    
    ofSetColor(0, 0, 255);
    ofDrawLine(glm::vec3(0,0,0), glm::vec3( 0,0,10) );
    
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
    sphere.setPosition(ofMap(x, 0, 1024, -25, 25), ofMap(y, 0, 1024, -25, 25), 5);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
