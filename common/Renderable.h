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
            parameters.add(render.set("render",false));
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
            texCopyTime.set( recorder.getAvgTimeTextureCopy());
            gpuDownTime.set( recorder.getAvgTimeGpuDownload());
            encodeTime.set( recorder.getAvgTimeEncode());
            fileSaveTime.set( recorder.getAvgTimeSave());
            gui.draw();
        }
        
        void save(int frame){
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
    protected:
        ofParameterGroup   parameters;
        ofxPanel gui;
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
