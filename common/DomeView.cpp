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
    
    string fileName = "dome.obj";
    filesystem::path path = Util::getResFolder()/"3dModel"/fileName;
    model.setScaleNormalization(false);
    model.loadModel(path.string());
    model.setRotation(0, 180, 1, 0, 0);
    model.setPosition(0, 2, 0);
    model.setScale(1, 1, 1);
 
    gui.setup("DomeView", "DomeViewSettings.xml");
    setupRenderGui();
    domePrms.setName("DomeView Prameters");
    
    domePrms.add(bDrawWireFrame.set("drawWireFrame", true));
    domePrms.add(bDrawFaces.set("drawFaces", true));

    domePrms.add(nearClip.set("nearClip", 10, 0.0001, 20));
    domePrms.add(farClip.set("farClip", 500, 100, 1000));
    domePrms.add(fov.set("fov", 60, 0, 180));
    domePrms.add(distance.set("distance", 60, 0, 150));
    domePrms.add(pan.set("pan", 0, -180, 180));
    domePrms.add(tilt.set("tilt", 0, -90, 90));
    domePrms.add(roll.set("roll", 0, -90, 90));

    domePrms.add(lensOffset.set("lensOffset", glm::vec2(0,0), glm::vec2(-50,-50), glm::vec2(50,50)));
    domePrms.add(resetCameraBtn.set("resetCamera"));
    
    gui.add(domePrms);
    
    farClip.addListener(this, &DomeView::floatCb);
    nearClip.addListener(this, &DomeView::floatCb);
    fov.addListener(this, &DomeView::floatCb);
    distance.addListener(this, &DomeView::floatCb);
    pan.addListener(this, &DomeView::floatCb);
    tilt.addListener(this, &DomeView::floatCb);
    roll.addListener(this, &DomeView::floatCb);

    lensOffset.addListener(this, &DomeView::vec2Cb);
    resetCameraBtn.addListener(this, &DomeView::resetCamera);
    gui.loadFromFile("DomeViewSettings.xml");

    updateCameraSettings();
    
    
    img.load( Util::getResFolder()/"img"/"test.png");
}

void DomeView::update(){
    distance.set(cam.getDistance());
    saveRenderFbo(ofApp::get()->frame);
}

void DomeView::floatCb(float & fake){
    updateCameraSettings();
}

void DomeView::vec2Cb(glm::vec2 & fake){
    updateCameraSettings();
}

void DomeView::vec3Cb(glm::vec3 & fake){
    updateCameraSettings();
}

void DomeView::resetCamera(){
    cam.reset();
    gui.loadFromFile("DomeViewSettings.xml");
    updateCameraSettings();
}

void DomeView::updateCameraSettings(){
    cam.setNearClip(nearClip.get());
    cam.setFarClip(farClip.get());
    cam.setFov(fov.get());
    cam.setDistance(distance.get());
    cam.rotateAroundDeg(prevPan-pan.get(), cam.getUpDir(), glm::vec3(0,0,0));
    cam.rotateAroundDeg(prevTilt-tilt.get(), cam.getSideDir(), glm::vec3(0,0,0));
    cam.rotateAroundDeg(prevRoll-roll.get(), cam.getLookAtDir(), glm::vec3(0,0,0));
    
    cam.setLensOffset(lensOffset.get());
    cam.lookAt(cam.getTarget(), cam.getUpDir());
    
    prevPan = pan.get();
    prevTilt = tilt.get();
    prevRoll = roll.get();
                   
}

void DomeView::draw(){
    beginRenderFbo();
    
    ofEnableDepthTest();
    cam.begin();
    ofPushMatrix();

    ofBackground(0);
    
    
    if(bDrawFaces.get()){
        ofNoFill();
        ofSetColor(255);
        bindMyTexture();
        model.draw(OF_MESH_FILL);
        unbindMyTexture();
    }
    
    if(bDrawWireFrame.get()){
        ofNoFill();
        ofSetColor(255);
        model.drawWireframe();
    }

    ofRotateXDeg(90);
    ofDrawCircle(0, 0, 23);
    //ofTranslate(0,0,-2);
    //ofDrawCircle(0, 0, 23);

    ofPopMatrix();
    
  	cam.end();
    
    endRenderFbo();
    
    drawRenderFbo(ofGetWidth(), ofGetHeight());

    ofDisableDepthTest();
    drawGui();
    
}

void DomeView::exit(){

}


void DomeView::bindMyTexture() {
    ofTexture &tex = img.getTexture();
    tex.bind();
    
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    
    ofTextureData texData = tex.getTextureData();
    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
    } else {
        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void DomeView::unbindMyTexture() {
    img.getTexture().unbind();
    
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
