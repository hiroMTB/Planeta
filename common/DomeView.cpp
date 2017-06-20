#include "DomeView.h"
#include "ScreenDef.h"
#include "Util.h"
#include "ofApp.h"

using namespace mikromedas;
using namespace ScreenDef;

DomeView::DomeView(int w, int h, string path) : Renderable(w, h, path){
    
}

void DomeView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    ofEnableDepthTest();
    cam.setDistance(100);

}

void DomeView::update(){
    save(ofApp::get()->frame);
}

void DomeView::draw(){
    
    begin();
    
    cam.begin();
    ofRotateXRad(.5);
    ofRotateYRad(-.5);

    ofPushMatrix();
    ofBackground(0);
    
    ofNoFill();
    ofSetColor(255);
    ofDrawSphere(0, 0, 150);
    
    ofPopMatrix();
    
  	cam.end();
    
    end();
    
    drawFbo(ofGetWidth(), ofGetHeight());
    
    drawGui();
}

void DomeView::exit(){

}
