#include "ofMain.h"
#include "ofApp.h"
#include "Screen.h"
#include "RfTexView.h"
#include "RfView.h"

int main(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    int size = 512;
    ofGLFWWindowSettings settings;
    //settings.setGLVersion(4, 1);
    shared_ptr<ofAppBaseWindow> mainWindow;
    settings.width = size;
    settings.height = 280;
    settings.setPosition(ofVec2f(0,size+65));
    settings.resizable = true;
    mainWindow = ofCreateWindow(settings);
    shared_ptr<ofApp> mainApp = shared_ptr<ofApp>(ofApp::get());
    ofRunApp(mainWindow, mainApp);
    
    // 2D Circle TexView, Renderable
    settings.width = size;
    settings.height = size;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> texWindow = ofCreateWindow(settings);
    shared_ptr<RfTexView> texApp(new RfTexView(mikromedas::Screen::renderW, mikromedas::Screen::renderH, "render/tex"));
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
