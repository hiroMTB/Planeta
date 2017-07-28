#include "RfTexView.h"
#include "Screen.h"
#include "Util.h"
#include "ofApp.h"
#include "RfView.h"

RfTexView::RfTexView(int w, int h, string path){   
    renderer.setup(w, h, path);
}

void RfTexView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(mikromedas::Screen::fps);
    ofSetCircleResolution(160);
    
    gui.setup("Tex View", "TexViewSettings.xml");
    renderer.setupRenderGui(gui);
    setupGui(gui);
    gui.loadFromFile("TexViewSettings.xml");
    
    domemaster.setup();
    domemaster.resize(mikromedas::Screen::renderW, mikromedas::Screen::renderH);
    domemaster.setCameraPosition(0,2,0);
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

    ofApp * app = ofApp::get();
    
    if(app->bStart.get()){
        ofEnableDepthTest();

        for (int i=0; i<domemaster.renderCount; i++){
            domemaster.begin(i);
            ofApp::get()->rfView->drawScene();
            domemaster.end(i);
        }
    }
    
    renderer.beginRenderFbo();
    ofBackground(0);
    domemaster.draw();
    
    if(bDrawGuide.get()){
        ofPushMatrix();
        ofTranslate(mikromedas::Screen::centerX, mikromedas::Screen::centerY);
        ofSetColor(0,255,0);
        glLineWidth(3);
        drawGuide();
        ofPopMatrix();
    }

    renderer.endRenderFbo();
    
    renderer.drawRenderFbo(ofGetWindowWidth(), ofGetWindowHeight());
    
    ofDisableDepthTest();
    gui.draw();
}

void RfTexView::exit(){
    //ofExit();
}

void RfTexView::mouseDragged(int x, int y, int button){
}
