#include "RfView.h"
#include "ofMain.h"
#include "Screen.h"
#include "Util.h"
#include "ofApp.h"
#include "RfTexView.h"
#include "ofxEquidistantProjection.h"

using namespace ofxequidistantprojection;

RfView::RfView(int w, int h, string path){
    renderer.setup(w, h, path);
}

void RfView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(mikromedas::Screen::fps);
    ofSetCircleResolution(160);
    
    setupModel();
    gui.setup("DomeView", "DomeViewSettings.xml");
    renderer.setupRenderGui(gui);
    setupCameraGui(gui);
    
    prms.add(rotAngle.set("Rotation Angle", 0, -360, 360));
    prms.add(rotAxis.set("Rotation Axis", glm::vec3(1,1,1), glm::vec3(-2,-2,-2), glm::vec3(2,2,2)));
    gui.add(prms);
    gui.loadFromFile("DomeViewSettings.xml");
    
    img.load(mtb::Util::getResFolder()/"img"/"test.png");
    
    points.setMode(OF_PRIMITIVE_POINTS);
    lines.setMode(OF_PRIMITIVE_LINES);
    
    sphere.setUseVbo(true);
    sphere.setRadius(1);
    sphere.setResolution(10);
    sphere.setOrientation(ofVec3f(90,0,0));
    sphere.getMesh().setMode(OF_PRIMITIVE_LINES);
    vector<glm::vec3> & vs = sphere.getMesh().getVertices();
    for(int i=0; i<vs.size(); i++){
        sphere.getMesh().addColor(ofFloatColor(1,1,1,1));
    }
    
}

void RfView::update(){
    bool bStart = ofApp::get()->bStart.get();
    int frame = ofApp::get()->frame.get();
    
    distance.set(cam.getDistance());
    renderer.update();

    if(bStart){
        renderer.saveRenderFbo(ofApp::get()->frame);
    }
    
}

void RfView::draw(){
    renderer.beginRenderFbo();
    ofEnableDepthTest();
    ofBackground(0);
    
    cam.begin();
    if(bDrawScene) drawScene();
    if(bDrawFaces) drawTexDome(ofApp::get()->texView->renderer.fbo.getTexture());
    cam.end();

    renderer.endRenderFbo();
    renderer.drawRenderFbo(ofGetWidth(), ofGetHeight());
    ofDisableDepthTest();
    gui.draw();
}

void RfView::drawScene(){
    
    ofDisableSmoothing();
    ofDisableAntiAliasing();

    mtb::Util::drawAxis(2);
    
    ofPushMatrix(); {
        ofSetColor(255);
        //Util::drawGrid(40);
        
        ofSetColor(255,100);
        drawWireDome(6, 12);
        
        ofSetColor(255);
        //drawTexDome(img.getTexture());
        
        ofPushMatrix();
        ofRotateDeg(rotAngle, rotAxis->x, rotAxis->y, rotAxis->z);
        ofDrawCircle(glm::vec3(0,0,0), 40);
        ofNoFill();
        ofRotateZDeg(ofGetFrameNum()*0.1);
        ofTranslate(40,0,0);
        sphere.drawWireframe();
        ofPopMatrix();
    
    }ofPopMatrix();
}
