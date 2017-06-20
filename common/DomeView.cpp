#include "DomeView.h"
#include "ScreenDef.h"
#include "Util.h"

using namespace mikromedas;
using namespace ScreenDef;

DomeView::DomeView(int w, int h, string path) : Renderable(w, h, path){
    
}

void DomeView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
}

void DomeView::update(){
    save();
}

void DomeView::draw(){
    
    begin();
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofDrawSphere(0, 0, 150);
    
    ofPopMatrix();
    
    end();
    
    drawFbo(ofGetWidth(), ofGetHeight());
    
    drawGui();
}

void DomeView::exit(){

}
