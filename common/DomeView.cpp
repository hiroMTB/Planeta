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
    cam.setDistance(100);
    
    string fileName = "dome-low.obj";
    filesystem::path path = Util::getResFolder()/"3dModel"/fileName;
    model.setScaleNormalization(false);
    model.loadModel(path.string());
    model.setRotation(0, 180, 1, 0, 0);
    model.setPosition(0, 2, 0);
    model.setScale(1, 1, 1);

    parameters2.setName("dome param");
    parameters2.add(drawModel.set("drawModel", true));
    gui2.setup(parameters2, "domeView", 200, 10);

}

void DomeView::update(){
    save(ofApp::get()->frame);
}

void DomeView::draw(){
    begin();
    ofEnableDepthTest();
    cam.begin();
   ofPushMatrix();
    ofBackground(0);
    
    ofNoFill();
    ofSetColor(255);
    
    if(drawModel.get()) model.drawWireframe();

    ofRotateXDeg(90);
    ofDrawCircle(0, 0, 24);
    ofTranslate(0,0,-2);
    ofDrawCircle(0, 0, 24);

    ofPopMatrix();
    
  	cam.end();
    
    end();
    
    drawFbo(ofGetWidth(), ofGetHeight());

    ofDisableDepthTest();
    drawGui();
    
    gui2.draw();
}

void DomeView::exit(){

}
