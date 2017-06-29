#include "TexView.h"
#include "ScreenDef.h"
#include "Util.h"
#include "ofApp.h"

using namespace mikromedas;
using namespace ScreenDef;

void TexView::setupGui(ofxPanel & gui){
    texPrms.setName("TexView Parameters");
    texPrms.add(bDrawGuide.set("drawGuide", true));
    gui.add(texPrms);
}

void TexView::drawGuide(){
    
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
        ofRotateDeg(i*10);
        ofDrawLine(-rad, 0, rad, 0);
        ofPopMatrix();
    }   
}
