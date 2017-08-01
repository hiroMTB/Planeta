#pragma once

#include "ofMesh.h"

class ofHemiSpherePrimitive : public ofSpherePrimitive {
public:
    
    // override
    void set( float _radius, int _res,
             ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP ){
        
        radius     = _radius;
        resolution = _res;
        
        getMesh() = ofMesh::sphere( getRadius(), getResolution(), mode );
        
        normalizeAndApplySavedTexCoords();
        
    }
};

