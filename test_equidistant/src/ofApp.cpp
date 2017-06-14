#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenDef.h"

using namespace ScreenDef;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    ofSetWindowPosition(0, 0);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    exporter.setup(renderW, renderH, fps, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    //exporter.startExport();
    
}

void ofApp::update(){
    
    frame++;
}

void ofApp::draw(){

    exporter.begin();
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(centerX, centerY);

    ofSetColor(255);
    ofFill();
    ofDrawCircle(0, 0, renderW/2);
    
    //if(!exporter.isExporting())
    {
        ofSetColor(0,0,255);
        ofSetLineWidth(3);
        ofNoFill();
        float rad = renderW/2;
        for(int i=0; i<10; i++){
            float r = rad/10.0f * i;
            ofDrawCircle(0, 0, r);
        }
        
        for(int i=0; i<18; i++){
            
            ofPushMatrix();
            ofRotate(i*10);
            ofDrawLine(-rad, 0, rad, 0);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    Util::drawInfo();
}

int main(){
    
    ofSetupOpenGL(1000, 1000, OF_WINDOW);
    ofRunApp(ofApp::get());
}

