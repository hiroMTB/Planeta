#include "RfTexView.h"
#include "ScreenDef.h"
#include "Util.h"
#include "ofApp.h"

using namespace mikromedas;
using namespace ScreenDef;

RfTexView::RfTexView(int w, int h, string path){   
    renderer.setup(w, h, path);
}

void RfTexView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    
    gui.setup("Tex View", "TexViewSettings.xml");
    renderer.setupRenderGui(gui);
    setupGui(gui);
    gui.loadFromFile("TexViewSettings.xml");
}

void RfTexView::update(){
    bool bStart = ofApp::get()->bStart.get();
    int frame = ofApp::get()->frame.get();
    
    renderer.update();
    
    if(bStart){        
        renderer.saveRenderFbo(ofApp::get()->frame);
    }
}

void RfTexView::draw(){
    
    renderer.beginRenderFbo();
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(centerX, centerY);
    
    ofSetColor(255);
    ofFill();
    ofDrawCircle(0, 0, renderW/2);
    
    if(bDrawGuide.get()) drawGuide();
    
    ofPopMatrix();
    
    renderer.endRenderFbo();
    renderer.drawRenderFbo(ofGetWidth(), ofGetHeight());
    
    ofDisableDepthTest();
    gui.draw();
}

void RfTexView::exit(){
    //ofExit();
}
