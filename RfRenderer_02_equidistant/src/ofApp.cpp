#include "ofApp.h"
#include "ofAppNoWindow.h"
#include "Util.h"
#include "FontManager.h"
#include "Screen.h"

void ofApp::setup(){

    gui.setup("Control GUI");
    mainPrms.add(frame.set("frame", -1, -1, 1000));
    mainPrms.add(bStart.set("start", false));
    gui.add(mainPrms);
    
}

void ofApp::update(){
    if(bStart.get()){
        frame.set(frame);
        frame++;
    }
    
}

void ofApp::draw(){
    ofBackground(0);
    ofDisableDepthTest();
    gui.draw();
}

void ofApp::keyPressed(int key){

}

void ofApp::exit(){
    
}
