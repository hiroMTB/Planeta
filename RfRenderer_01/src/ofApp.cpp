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

}

void ofApp::exit(){
    
}

int main(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    int size = 500;
    
    // main process
    ofGLFWWindowSettings settings;
    settings.width = size;
    settings.height = size;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    //settings.decorated = false;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings); //new ofAppNoWindow()
    shared_ptr<ofApp> mainApp = shared_ptr<ofApp>(ofApp::get());
    ofRunApp(mainWindow, mainApp);
    
    // 2D Circle TexView, Renderable
    settings.width = size;
    settings.height = size;
    settings.setPosition(ofVec2f(0,size+65));
    settings.resizable = true;
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> texWindow = ofCreateWindow(settings);
    shared_ptr<TexView> texApp(new TexView(renderW, renderH, "render/tex"));
    ofApp::get()->texView = texApp;
    ofRunApp(texWindow, texApp);
    
    // 3D Dome View, Renderable
    settings.width = 1920-size;
    settings.height = settings.width/(1920/1080.0);
    settings.setPosition(ofVec2f(size,0));
    settings.resizable = true;
    settings.shareContextWith = mainWindow;

    shared_ptr<ofAppBaseWindow> rfWindow = ofCreateWindow(settings);
    shared_ptr<RfView> rfApp(new RfView(settings.width, settings.height, "render/dome"));
    ofApp::get()->rfView = rfApp;
    ofRunApp(rfWindow, rfApp);

    ofRunMainLoop();

}
