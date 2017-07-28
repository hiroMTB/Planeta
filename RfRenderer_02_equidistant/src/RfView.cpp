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
    
    rfPrms.add(numParticles.set("num particles", 0, 0, 1000000));
    gui.add(rfPrms);
    gui.loadFromFile("DomeViewSettings.xml");
    
    img.load(mtb::Util::getResFolder()/"img"/"test.png");
    
    points.setMode(OF_PRIMITIVE_POINTS);
    lines.setMode(OF_PRIMITIVE_LINES);
}

void RfView::update(){
    bool bStart = ofApp::get()->bStart.get();
    int frame = ofApp::get()->frame.get();
    
    distance.set(cam.getDistance());
    renderer.update();

    if(bStart){
        renderer.saveRenderFbo(ofApp::get()->frame);
    }
    
    char m[255];
    sprintf(m, "sim_%05d.bin", frame);
    string fileName(m);
    filesystem::path p = ofToDataPath("")/mtb::Util::getResFolder()/"sim"/"particle_rain_01"/fileName;
    p = filesystem::absolute(p);
    ofFile f(p);
    if(f.exists()){
        
        rf.load( p.string() );
        
        points.clearVertices();
        lines.clearVertices();
        
        glm::vec3 topPoint(0,23,0);
        
        float yLimit = 10;
        
        for(int i=0; i<rf.pPosition.size()/3; i++){
            
            if(i%10==1){
                float x = rf.pPosition[i*3+0];
                float y = rf.pPosition[i*3+1];
                float z = rf.pPosition[i*3+2];
                float scale = 23*2/40.0;
                glm::vec3 pos(x,y,z);
                pos *= scale;

                if( yLimit > pos.y )
                    continue;
                
                float dist = glm::distance(pos, topPoint);
                float alpha = ofMap(dist, 5, (23*1.414), 0, 255);

                points.addVertex(pos);
                points.addColor(ofColor(255, alpha));
                
                // add line from top point
                if( yLimit<=pos.y && pos.y<yLimit+1 ){
                    
                    glm::vec3 dir = pos-topPoint;
                    glm::normalize(dir);
                    lines.addVertex(pos);
                    lines.addVertex(pos+dir*20);
                    
                    float lineAlpha = 100 + ofRandom(10,40);
                    lines.addColor(ofColor(255, lineAlpha));
                    lines.addColor(ofColor(255, lineAlpha));
                }
            }
        }
        
        numParticles.set(rf.pPosition.size()/3);
    }
}

void RfView::draw(){
    renderer.beginRenderFbo();
    ofEnableDepthTest();
    ofBackground(0);
    
    cam.begin();
    drawScene();
    
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
        drawTexDome(img.getTexture());
        
        // draw rf
        ofPushMatrix(); {
            ofSetColor(255);
            //ofTranslate(0, 2, 0);
            glPointSize(1);
            ofSetColor(255);
            points.drawVertices();
            
            ofSetLineWidth(1);
            lines.draw();
        }ofPopMatrix();
    
    }ofPopMatrix();
}

void RfView::exit(){
    //ofExit();
}
