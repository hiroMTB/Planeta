#include "ofMain.h"
#include "Util.h"
#include "ofApp.h"

namespace mtb{
    
    void Util::drawInfo(){
        
        ofSetColor(100);
        ofFill();
        ofDrawRectangle(0, 0, 200, 60);
        ofSetColor(255);
        
        stringstream ss;
        ss << "fps       : " << ofGetFrameRate() << "\n";
        ss << "frame     : " << ofApp::get()->frame << "\n";
        //ss << "Expoprter : " << (ofApp::get()->recorder. ()?"ON" : "OFF") << "\n";
        ofDrawBitmapString(ss.str(), 10, 20);
    }
    
    void Util::drawLineAsRect( ofVec2f p1, ofVec2f p2, float thickness){
        
        ofFill();
        ofVec2f xAxis(1,0);
        ofVec2f dir = p2 -p1;
        float angle = xAxis.angle(dir);
        float dist = dir.length();
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofTranslate(p1.x, p1.y);
        ofRotate(angle);
        ofDrawRectangle(0,0, dist, thickness);
        ofPopMatrix();
    }
    
    void Util::drawLineAsRect( float x1, float y1, float x2, float y2, float thickness){
        drawLineAsRect( ofVec2f(x1, y1), ofVec2f(x2, y2), thickness);
    }
    
    void Util::drawCircle( float x, float y, float rad, float thickness){
        
        if(ofGetStyle().color.a>0 && 0<rad){
            ofPath circle;
            circle.setCircleResolution(120);
            circle.setColor(ofGetStyle().color);
            circle.arc(x,y,rad+thickness/2,rad+thickness/2, 0,360);
            circle.arc(x,y,rad-thickness/2,rad-thickness/2, 0,360);
            circle.draw();
        }
    }
    
    void Util::drawArc( float x, float y, float rad, float thickness, float startAngle, float endAngle){
        
        ofNoFill();
        
        if(ofGetStyle().color.a>0 && 0<rad){
            ofPath arc;
            arc.setColor(ofGetStyle().color);
            arc.setCircleResolution(120);
            
            ofPoint outerStartPoint;
            outerStartPoint.x = x + (rad+thickness/2)*cos(ofDegToRad(startAngle));
            outerStartPoint.y = y + (rad+thickness/2)*sin(ofDegToRad(startAngle));
            
            ofPoint innerEndPoint;
            innerEndPoint.x = x + (rad-thickness/2)*cos(ofDegToRad(endAngle));
            innerEndPoint.y = y + (rad-thickness/2)*sin(ofDegToRad(endAngle));
            
            arc.arc(ofPoint(x,y), rad+thickness/2,rad+thickness/2, startAngle, endAngle, true);
            arc.lineTo(innerEndPoint);
            arc.arc( ofPoint(x,y),rad-thickness/2,rad-thickness/2, endAngle, startAngle, false);
            //arc.lineTo(outerStartPoint);
            
            arc.close();
            
            arc.draw();
        }
    }
    
    void Util::replaceChar(string &text, char oldChar, char newChar){
        replace_if(text.begin(), text.end(), [=](char c){return c==oldChar;}, newChar ), text.end();
    }
    
    void Util::eraseChar(string &text, char eraseChar){
        text.erase( remove_if(text.begin(), text.end(), [=](char c){return c==eraseChar;} ), text.end() );
    }
    
    void Util::eraseLineBreak(string &text){
        eraseChar(text, '\n');
    }
    
    filesystem::path Util::getResFolder(){
        return filesystem::path("/Volumes/HrsPortable/projects/Planeta/code/res/");
    }
    
    string Util::replaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }
    
    double Util::myMap(double value, double inputMin, double inputMax, double outputMin, double outputMax, bool clamp){
        
        double outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
        
        if( clamp ){
            if(outputMax < outputMin){
                if( outVal < outputMax )outVal = outputMax;
                else if( outVal > outputMin )outVal = outputMin;
            }else{
                if( outVal > outputMax )outVal = outputMax;
                else if( outVal < outputMin )outVal = outputMin;
            }
        }
        return outVal;
    }
    
    void Util::drawOpenArc(){
        static ofVboMesh arc;
        
        arc.setMode(OF_PRIMITIVE_LINE_STRIP);
        if(arc.getNumVertices() == 0){
            int arcRes = 18;
            for(int i=0; i<arcRes+1; i++){
                float angle = i * 180.0/arcRes;
                float x = cos(ofDegToRad(angle));
                float y = sin(ofDegToRad(angle));
                arc.addVertex(glm::vec3(x, y, 0));
            }
        }
        
        arc.draw(OF_MESH_WIREFRAME);
    }
    
    void Util::drawGrid(float size=1){
        
        for(int i=0; i<11; i++){
            float x = i * size*0.1 - size*0.5;
            float z1 = -size/2;
            float z2 = +size/2;
            ofDrawLine(glm::vec3(x,0,z1), glm::vec3(x,0,z2));
        }
        
        for(int i=0; i<11; i++){
            float x1 = -size/2;
            float x2 = +size/2;
            float z = i*size*0.1 -size*0.5;
            ofDrawLine(glm::vec3(x1,0,z), glm::vec3(x2,0,z));
        }
    }
    
    void Util::drawAxis(float size = 1){
        ofSetColor(255, 0, 0);
        ofDrawLine(glm::vec3(0,0,0), glm::vec3(size,0,0) );
        
        ofSetColor(0, 255, 0);
        ofDrawLine(glm::vec3(0,0,0), glm::vec3( 0,size,0) );
        
        ofSetColor(0, 0, 255);
        ofDrawLine(glm::vec3(0,0,0), glm::vec3( 0,0,size) );
    }
    
}
