#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenDef.h"

//#define USE_OFX_TEXTURE_RECORDER 1

using namespace ScreenDef;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(fps);
    ofSetCircleResolution(160);
    ofSetWindowPosition(0, 0);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
#ifdef USE_OFX_TEXTURE_RECORDER
    fbo.allocate(renderW, renderH, GL_RGB);
    ofxTextureRecorder::Settings settings(fbo.getTexture());
    settings.imageFormat = OF_IMAGE_FORMAT_PNG;
    settings.numThreads = 4;
    settings.maxMemoryUsage = 9000000000;
    recorder.setup(settings);
#else
    exporter.setup(renderW, renderH, fps, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    exporter.startExport();
#endif
    
}

void ofApp::update(){
    
    frame++;
}

void ofApp::draw(){

#ifdef USE_OFX_TEXTURE_RECORDER
    fbo.begin();
#else
    exporter.begin();
#endif
    ofPushMatrix();
    ofBackground(0);
    ofTranslate(centerX, centerY);

    ofSetColor(255);
    ofFill();
    ofDrawCircle(0, 0, renderW/2);
    
    //if(!exporter.isExporting())
    {
        ofSetColor(0,0,255);
        ofSetLineWidth(3);
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
    
#ifdef USE_OFX_TEXTURE_RECORDER
    fbo.end();
    recorder.save(fbo.getTexture());
#else
    exporter.end();
#endif
    
    ofBackground(20);
    
#ifdef USE_OFX_TEXTURE_RECORDER
    fbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowWidth());
#else
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
#endif
}

int main(){
    
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(ofApp::get());
}

