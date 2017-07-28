#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "ofxGui.h"

namespace mikromedas{
    
    class Renderer{
        
    public:
        
        Renderer(){}
        void setup(int w, int h, string path){
            
            fbo.allocate(w, h, GL_RGB);
            ofxTextureRecorder::Settings settings(fbo.getTexture());
            settings.imageFormat = OF_IMAGE_FORMAT_PNG;
            settings.numThreads = 4;
            settings.maxMemoryUsage = 9000000000;
            settings.folderPath = path;            
            recorder.setup(settings);
        }
        
        void setupRenderGui(ofxPanel & gui){
            renderPrms.setName("Render Parameters");
            renderPrms.add(render.set("render",false));
            renderPrms.add(frameRate.set("frameRate", 0));
            renderPrms.add(texCopyTime.set("texCopyTime", 0));
            renderPrms.add(gpuDownTime.set("gpuDownTime", 0));
            renderPrms.add(encodeTime.set("encodeTime", 0));
            renderPrms.add(fileSaveTime.set("fileSaveTime", 0));
            gui.add(renderPrms);
        }
        
        void beginRenderFbo(){
            fbo.begin();
        }
        
        void endRenderFbo(){
            fbo.end();
        }
        
        void drawRenderFbo(int w, int h){
            ofBackground(20);
            ofRectangle r(0, 0, fbo.getWidth(), fbo.getHeight());
            r.scaleTo( ofRectangle(0, 0, w, h) );
            ofSetColor(255);
            fbo.draw(r);
        }
        
        void update(){
            frameRate.set( (int)ofGetFrameRate());
            texCopyTime.set( recorder.getAvgTimeTextureCopy());
            gpuDownTime.set( recorder.getAvgTimeGpuDownload());
            encodeTime.set( recorder.getAvgTimeEncode());
            fileSaveTime.set( recorder.getAvgTimeSave());
        }
        
        void saveRenderFbo(int frame){
            if(render.get())
                recorder.save(fbo.getTexture(), frame);
        }
 
        void startRender(){
            render.set(true);
        }
        
        void stopRender(){
            render.set(false);
            recorder.stop();
        }
        
        int getWidth(){
            return fbo.getWidth();
        }
        
        int getHeight(){
            return fbo.getHeight();
        }

        ofParameterGroup   renderPrms;
        ofFbo fbo;
        ofxTextureRecorder recorder;
        
    private:
        ofParameter<bool>  render;
        ofParameter<float> frameRate;
        ofParameter<float> texCopyTime;
        ofParameter<float> gpuDownTime;
        ofParameter<float> encodeTime;
        ofParameter<float> fileSaveTime;
    };
}
