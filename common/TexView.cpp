#include "TexView.h"
#include "ScreenDef.h"
#include "Util.h"
#include "ofApp.h"

using namespace mikromedas;
using namespace ScreenDef;

TexView::TexView(int w, int h, string path) : Renderable(w, h, path){
    
}

void TexView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    
    gui.setup("Tex View", "TexViewSettings.xml");
    setupRenderGui();
    texPrms.setName("TexView Parameters");
    texPrms.add(bDrawGuide.set("drawGuide", true));
    gui.add(texPrms);
        gui.loadFromFile("DomeViewSettings.xml");
}

void TexView::update(){
    saveRenderFbo(ofApp::get()->frame);
}

void TexView::draw(){
    
    beginRenderFbo();
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(centerX, centerY);
    
    ofSetColor(255);
    ofFill();
    ofDrawCircle(0, 0, renderW/2);
    
    if(bDrawGuide.get()) drawGuide();
    
    ofPopMatrix();
    
    endRenderFbo();
    
    drawRenderFbo(ofGetWidth(), ofGetHeight());

    drawGui();
}

void TexView::drawGuide(){
    
    ofSetColor(0,0,255);
    ofSetLineWidth(1);
    ofNoFill();
    float rad = renderW/2;
    for(int i=0; i<10; i++){
        float r = rad/10.0f * i;
        ofDrawCircle(0, 0, r);
    }
    
    for(int i=0; i<18; i++){
        
        ofPushMatrix();
        ofRotateDeg(i*10);
        ofDrawLine(-rad, 0, rad, 0);
        ofPopMatrix();
    }   
}

void TexView::exit(){
    ofExit();
}
