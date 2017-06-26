#include "RfView.h"
#include "ofMain.h"
#include "ScreenDef.h"
#include "Util.h"
#include "ofApp.h"

using namespace mikromedas;
using namespace ScreenDef;

RfView::RfView(int w, int h, string path) : DomeView(w,h,path){
}

void RfView::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    
    setupModel();
    gui.setup("DomeView", "DomeViewSettings.xml");
    setupRenderGui();
    setupCameraGui();
    
    rfPrms.add(bStart.set("start", true));
    rfPrms.add(simFrame.set("frame", 0, 0, 2500));
    rfPrms.add(numParticles.set("num particles", 0, 0, 1000000));
    gui.add(rfPrms);
    
}

void RfView::update(){
    
    distance.set(cam.getDistance());
    saveRenderFbo(ofApp::get()->frame);
    
    if(bStart){
        simFrame.set(simFrame.get()+1);
    }
    
    char m[255];
    sprintf(m, "sim_%05d.bin", simFrame.get());
    string fileName(m);
    filesystem::path p = ofToDataPath("")/Util::getResFolder()/"sim"/"particle_rain_01"/fileName;
    p = filesystem::absolute(p);
    ofFile f(p);
    if(f.exists()){
        
        rf.load( p.string() );
        
        mesh.clearVertices();
        for(int i=0; i<rf.pPosition.size()/3; i++){
            float x = rf.pPosition[i*3+0];
            float y = rf.pPosition[i*3+1];
            float z = rf.pPosition[i*3+2];
            
            float scale = 23*2/40.0;
            mesh.addVertex(glm::vec3(x,y,z)*scale);
        }
        
        numParticles.set(rf.pPosition.size()/3);
    }
    
}

void RfView::draw(){
    beginRenderFbo();
    
    ofEnableDepthTest();
    cam.begin();
    
    ofBackground(0);
    
    drawModelWireframe();
    
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(0, 2, 0);
    mesh.drawVertices();
    ofPopMatrix();
    
    
    cam.end();
    endRenderFbo();
    drawRenderFbo(ofGetWidth(), ofGetHeight());
    
    drawGui();
}
void RfView::exit(){
    
}
