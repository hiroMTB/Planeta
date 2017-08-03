#include "ofApp.h"
#include "mtb/Util.h"

using namespace mtb;

void ofApp::setup(){
    
    hemi.set(100, 12);
    //hemi.getMesh().save("hemi.ply");

    img.load("coord.png");
    
    bWire = true;
    
    vector<glm::vec2> t = hemi.getMesh().getTexCoords();
    vector<glm::vec3> v = hemi.getMesh().getVertices();
    vector<ofFloatColor> & c = hemi.getMesh().getColors();

    cout << "tex num " << t.size() << endl;
    cout << "v num " << v.size() << endl;
    cout << "c num " << c.size() << endl;
    
    for(int i=0; i<t.size(); i++){
        cout <<   i  << ", ";
        cout << v[i] << ", ";
        cout << t[i] << endl;
        if(i==25){
            hemi.getMesh().addColor(ofFloatColor(1,0,0,1));
        }else{
            hemi.getMesh().addColor(ofFloatColor(1,1,1,1));
        }
    }
}

void ofApp::update(){

}

void ofApp::bindMyTexture(const ofTexture & tex) {
    tex.bind();
    
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    
    ofTextureData texData = tex.getTextureData();
    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
    } else {
        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void ofApp::unbindMyTexture(const ofTexture & tex) {
    tex.unbind();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void ofApp::draw(){

    ofEnableDepthTest();
    ofBackground(100);
    cam.begin();
    
    Util::drawAxis(23);
    
    ofSetColor(255);
    if(bWire){
        bindMyTexture(img.getTexture());
        hemi.draw(OF_MESH_FILL);
        unbindMyTexture(img.getTexture());
    }else{
        glPointSize(3);
        hemi.draw(OF_MESH_WIREFRAME);
    }
    cam.end();
}

void ofApp::keyPressed(int key){
    
    if(key == 'w'){
        bWire = !bWire;
    }
    
}
