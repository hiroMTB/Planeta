#include "HemiSphere.h"

namespace mikromedas{

ofHemiSpherePrimitive::ofHemiSpherePrimitive() {
    texCoords = {0.f, 0.f, 1.f, 1.f};
    radius = 20;
    setResolution( 16 );
}

//----------------------------------------------------------
ofHemiSpherePrimitive::ofHemiSpherePrimitive( float _radius, int res, ofPrimitiveMode mode ) {
    radius = _radius;
    texCoords = {0.f, 0.f, 1.f, 1.f};
    setResolution( res );
}

//----------------------------------------------------------
ofHemiSpherePrimitive::~ofHemiSpherePrimitive() {
    
}

//----------------------------------------------------------
void ofHemiSpherePrimitive::set( float _radius, int res, ofPrimitiveMode mode ) {
    radius     = _radius;
    resolution = res;
    
    getMesh() = hemiSphere( getRadius(), getResolution(), mode );
    
    normalizeAndApplySavedTexCoords();
}

//----------------------------------------------------------
void ofHemiSpherePrimitive::setResolution( int res ) {
    resolution             = res;
    ofPrimitiveMode mode   = getMesh().getMode();
    
    set(getRadius(), getResolution(), mode );
}

//----------------------------------------------------------
void ofHemiSpherePrimitive::setMode( ofPrimitiveMode mode ) {
    ofPrimitiveMode currMode = getMesh().getMode();
    if(currMode != mode)
        set(getRadius(), getResolution(), mode );
}

//----------------------------------------------------------
void ofHemiSpherePrimitive::setRadius(float _radius) {
    radius = _radius;
    setResolution( getResolution() );
}

//----------------------------------------------------------
float ofHemiSpherePrimitive::getRadius() const {
    return radius;
}

//----------------------------------------------------------
int ofHemiSpherePrimitive::getResolution() const {
    return resolution;
}

ofMesh ofHemiSpherePrimitive::hemiSphere( float radius, int res, ofPrimitiveMode mode ){
    
    ofMesh mesh;
    
    float doubleRes = res*2.f;
    float polarInc = HALF_PI/(res); // ringAngle
    float azimInc = TWO_PI/(doubleRes); // segAngle //
    
    if(mode != OF_PRIMITIVE_TRIANGLE_STRIP && mode != OF_PRIMITIVE_TRIANGLES) {
        mode = OF_PRIMITIVE_TRIANGLE_STRIP;
    }
    mesh.setMode(mode);
    
    ofDefaultVertexType vert;
    ofDefaultTexCoordType tcoord;
    
    for(float i = 0; i < res+1; i++) {
        
        float tr = sin( i * polarInc );
        float ny = cos( i * polarInc );
        
        float length = i/res * 0.5;
        //tcoord.y = i / res;
        
        for(float j = 0; j <= doubleRes; j++) {
            
            float nx = tr * sin(j * azimInc);   // clockwise
            float nz = tr * cos(j * azimInc);
            
            //tcoord.x = j / (doubleRes);
            
            vert = {nx, ny, nz};
            mesh.addNormal(vert);
            vert *= radius;
            mesh.addVertex(vert);
            
            glm::vec2 dir;
            dir.x = cos(-j * azimInc + HALF_PI);
            dir.y = sin(-j * azimInc + HALF_PI);
            glm::normalize(dir);    // just in case
            
            dir *= length;
            dir += glm::vec2(0.5, 0.5);
            tcoord.x = dir.x;
            tcoord.y = dir.y;
            
            mesh.addTexCoord(tcoord);
        }
    }
    
    int nr = doubleRes+1;
    if(mode == OF_PRIMITIVE_TRIANGLES) {
        
        ofIndexType index1, index2, index3;
        
        for(float iy = 0; iy < res; iy++) {
            for(float ix = 0; ix < doubleRes; ix++) {
                
                // first tri //
                if(iy > 0) {
                    index1 = (iy+0) * (nr) + (ix+0);
                    index2 = (iy+0) * (nr) + (ix+1);
                    index3 = (iy+1) * (nr) + (ix+0);
                    
                    mesh.addIndex(index1);
                    mesh.addIndex(index3);
                    mesh.addIndex(index2);
                }
                
                if(iy < res/*-1*/ ) {
                    // second tri //
                    index1 = (iy+0) * (nr) + (ix+1);
                    index2 = (iy+1) * (nr) + (ix+1);
                    index3 = (iy+1) * (nr) + (ix+0);
                    
                    mesh.addIndex(index1);
                    mesh.addIndex(index3);
                    mesh.addIndex(index2);
                    
                }
            }
        }
        
    } else {
        for(int y = 0; y < res; y++) {
            for(int x = 0; x <= doubleRes; x++) {
                mesh.addIndex( (y)*nr + x );
                mesh.addIndex( (y+1)*nr + x );
            }
        }
    }
    
    
    return mesh;

};

};
