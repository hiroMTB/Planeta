#include "mikromedas/TexView.h"
#include "mikromedas/Screen.h"
#include "mtb/Util.h"
#include "ofApp.h"

namespace mikromedas{
    
    void TexView::setupGui(ofxPanel & gui){
        texPrms.setName("TexView Parameters");
        texPrms.add(bDrawGuide.set("drawGuide", true));
        gui.add(texPrms);
    }
    
    void TexView::drawGuide(){
        
        ofSetColor(0,0,255);
        ofSetLineWidth(1);
        ofNoFill();
        float rad = mikromedas::Screen::renderW/2;
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
}
