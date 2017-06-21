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
 
    gui.setup("DomeView", "DomeViewSettings.xml");
    setupRenderGui();
    domePrms.setName("DomeView Prameters");
    
    domePrms.add(drawModel.set("drawModel", true));
    domePrms.add(nearClip.set("nearClip", 10, 0.0001, 20));
    domePrms.add(farClip.set("farClip", 500, 100, 1000));
    domePrms.add(fov.set("fov", 60, 0, 180));
    
    gui.add(domePrms);
    farClip.addListener(this, &DomeView::updateCameraSettings);
    nearClip.addListener(this, &DomeView::updateCameraSettings);
    fov.addListener(this, &DomeView::updateCameraSettings);

    
    gui.loadFromFile("DomeViewSettings.xml");

    float fake;
    updateCameraSettings(fake);
}

void DomeView::update(){
    saveRenderFbo(ofApp::get()->frame);
}

void DomeView::updateCameraSettings(float & fake){
    cam.setNearClip(nearClip.get());
    cam.setFarClip(farClip.get());
    cam.setFov(fov.get());
    //cam.setPosition(<#float px#>, <#float py#>, <#float pz#>)
    cam.lookAt(cam.getTarget());
                   
}

void DomeView::draw(){
    beginRenderFbo();
    
    ofEnableDepthTest();
    cam.begin();
    ofPushMatrix();
    //ofBackgroundGradient(ofColor(0), ofColor(255), OF_GRADIENT_LINEAR);
    ofBackground(0);
    
    ofNoFill();
    ofSetColor(255);
    
    if(drawModel.get()) model.drawWireframe();

    ofRotateXDeg(90);
    ofDrawCircle(0, 0, 23);
    ofTranslate(0,0,-2);
    ofDrawCircle(0, 0, 23);

    ofPopMatrix();
    
  	cam.end();
    
    endRenderFbo();
    
    drawRenderFbo(ofGetWidth(), ofGetHeight());

    ofDisableDepthTest();
    drawGui();
    
}

void DomeView::exit(){

}
