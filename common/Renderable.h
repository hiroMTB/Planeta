#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "ofxGui.h"

namespace mikromedas{
    
    class Renderable{
        
    public:
        Renderable()=delete;
        Renderable(Renderable& x)=default;
        template<class T> Renderable(T& x)=delete;
        Renderable & operator=(Renderable const &)=default;
        template<class T> Renderable & operator=(T const &)=delete;
        
        Renderable( int w, int h, string path){
            
            ofSetVerticalSync(false);
            ofBackground(0);
            
            fbo.allocate(w, h, GL_RGB);
            ofxTextureRecorder::Settings settings(fbo.getTexture());
            settings.imageFormat = OF_IMAGE_FORMAT_PNG;
            settings.numThreads = 4;
            settings.maxMemoryUsage = 9000000000;
            settings.folderPath = path;            
            recorder.setup(settings);
            
            parameters.setName("render param");
            parameters.add(start.set("start",false));
            parameters.add(frameRate.set("frameRate", 0));
            parameters.add(texCopyTime.set("texCopyTime", 0));
            parameters.add(gpuDownTime.set("gpuDownTime", 0));
            parameters.add(encodeTime.set("encodeTime", 0));
            parameters.add(fileSaveTime.set("fileSaveTime", 0));
            gui.setup(parameters);
        }
        
        virtual ~Renderable(){
            recorder.stop();
        }
        
        void begin(){
            fbo.begin();
        }
        
        void end(){
            fbo.end();
        }
        
        void drawFbo(int w, int h){
            ofBackground(20);
            ofRectangle r(0, 0, fbo.getWidth(), fbo.getHeight());
            r.scaleTo( ofRectangle(0, 0, w, h) );
            fbo.draw(r);
        }
        void drawGui(){
            frameRate.set(ofGetFrameRate());
            
            gui.draw();
        }
        
        void save(){
            if(start.get())
                recorder.save(fbo.getTexture());
        }
 
        void startRender(){
            start.set(true);
        }
        
        void stopRender(){
            start.set(false);
            recorder.stop();
        }
        
    private:

        ofxTextureRecorder recorder;
        ofFbo fbo;
        ofParameterGroup   parameters;
        ofParameter<bool>  start;
        ofParameter<float> frameRate;
        ofParameter<float> texCopyTime;
        ofParameter<float> gpuDownTime;
        ofParameter<float> encodeTime;
        ofParameter<float> fileSaveTime;
        
        ofxPanel gui;

    };
    
}
