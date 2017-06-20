#define MAX_QUALITY 1
#define RENDER 1

#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenDef.h"

using namespace ScreenDef;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    ofSetWindowPosition(0, 0);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    fbo.allocate(renderW, renderH, GL_RGB);
    ofxTextureRecorder::Settings settings(fbo.getTexture());
    settings.imageFormat = OF_IMAGE_FORMAT_PNG;
    settings.numThreads = 4;
    settings.maxMemoryUsage = 9000000000;
    recorder.setup(settings);
    
}

void ofApp::update(){
    
    frame++;
    
#ifdef RENDER
    recorder.save(fbo.getTexture());
#endif
    
}

void ofApp::draw(){

    fbo.begin();
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(centerX, centerY);

    ofSetColor(255);
    ofFill();
    ofDrawCircle(0, 0, renderW/2);
    
    {
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
            ofRotate(i*10);
            ofDrawLine(-rad, 0, rad, 0);
            ofPopMatrix();
        }
    }
    
    ofPopMatrix();
    
    fbo.end();

    ofBackground(20);
    ofRectangle r(0, 0, fbo.getWidth(), fbo.getHeight());
    r.scaleTo( ofRectangle(0, 0, ofGetWidth(), ofGetHeight()) );
    fbo.draw(r);
    
    Util::drawInfo();
}

void ofApp::exit(){

    recorder.stop();
}

int main(){
    
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(ofApp::get());
}

