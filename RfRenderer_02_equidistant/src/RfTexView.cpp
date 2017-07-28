#include "RfTexView.h"
#include "Screen.h"
#include "Util.h"
#include "ofApp.h"
#include "RfView.h"
#include <cassert>

using namespace glm;

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
    
    if(!equi.setup()){ std::terminate();}
    
    equi.getCamera().setPosition(0,0,0);
    equi.getCamera().lookAt(vec3(0,10,0), vec3(0,0,1));
    
    mask.load(mtb::Util::getResFolder()/"img"/"mask.png");

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
    
    renderer.beginRenderFbo();
    ofBackground(0);
    
    ofEnableDepthTest();
    equi.begin(ShaderType::LINE_SHADER);
    ofApp::get()->rfView->drawScene();
    equi.end(ShaderType::LINE_SHADER);

    equi.begin(ShaderType::POINT_SHADER);
    ofApp::get()->rfView->drawScene();
    equi.end(ShaderType::POINT_SHADER);

    ofDisableDepthTest();
    mask.draw(0,0,renderer.getWidth(), renderer.getHeight());
    
    if(bDrawGuide.get()){
        ofPushMatrix();
        ofTranslate(mikromedas::Screen::centerX, mikromedas::Screen::centerY);
        ofSetColor(0,255,0);
        glLineWidth(1);
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
