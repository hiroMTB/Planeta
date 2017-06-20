//#define MAX_QUALITY 1
#include "ofApp.h"
#include "ofAppNoWindow.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenDef.h"

using namespace ScreenDef;

void ofApp::setup(){
    
}

void ofApp::update(){
    frame++;
}

void ofApp::draw(){
}

void ofApp::keyPressed(int key){

    switch(key){
        case '1': texView->startRender(); break;
        case '2': domeView->startRender(); break;
    }
}

void ofApp::exit(){

}

int main(){
    
    int size = 500;
    
    {
        // main process
        ofGLFWWindowSettings settings;
        settings.width = size;
        settings.height = size;
        settings.setPosition(ofVec2f(0,0));
        settings.resizable = true;
        //settings.decorated = false;
        shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings); //new ofAppNoWindow()
        shared_ptr<ofApp> app = shared_ptr<ofApp>(ofApp::get());
        ofRunApp(window, app);
    }
    
    {
        // 2D Circle TexView, Renderable
        ofGLFWWindowSettings settings;
        settings.width = size;
        settings.height = size;
        settings.setPosition(ofVec2f(0,size+65));
        settings.resizable = true;
        shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
        shared_ptr<TexView> app(new TexView(renderW, renderH, "render/tex"));
        ofApp::get()->texView = app;
        ofRunApp(window, app);
    }

    {
        // 3D Dome View, Renderable
        ofGLFWWindowSettings settings;
        settings.width = 1920-size;
        settings.height = 1080-60;
        settings.setPosition(ofVec2f(size,0));
        settings.resizable = true;
        shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
        shared_ptr<DomeView> app(new DomeView(settings.width, settings.height, "render/dome"));
        ofApp::get()->domeView = app;
        ofRunApp(window, app);
    }
    
    ofRunMainLoop();

}
