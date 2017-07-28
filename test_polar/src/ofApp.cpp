#include "ofApp.h"
#include "Util.h"
#include "mikromedas/Screen.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(Screen::fps);
    ofSetCircleResolution(160);
    ofSetWindowPosition(0, 0);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    renderer.setup(Screen::renderW, Screen::renderH, "render");
    gui.setup();
    renderer.setupRenderGui(gui);
    
}

void ofApp::update(){
    
    frame++;
    renderer.update();
    renderer.saveRenderFbo(frame);
}

void ofApp::draw(){

    renderer.beginRenderFbo();
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(Screen::centerX, Screen::centerY);

    ofSetColor(255);
    ofFill();
    ofDrawCircle(0, 0, Screen::renderW/2);
    
    {
        ofSetColor(0,0,255);
        ofSetLineWidth(1);
        ofNoFill();
        float rad = Screen::renderW/2;
        for(int i=0; i<10; i++){
            float r = rad/10.0f * i;
            ofDrawCircle(0, 0, r);
        }
        
        for(int i=0; i<18; i++){
            
            ofPushMatrix();
            ofRotateZDeg(i*10);
            ofDrawLine(-rad, 0, rad, 0);
            ofPopMatrix();
        }
    }
    
    ofPopMatrix();
    
    renderer.endRenderFbo();
    renderer.drawRenderFbo(ofGetWidth(), ofGetHeight());

    ofDisableDepthTest();
    gui.draw();
    
}

void ofApp::exit(){
    renderer.stopRender();
}

int main(){
    
    ofSetupOpenGL(1024, 1024, OF_WINDOW);
    ofRunApp(ofApp::get());
}

