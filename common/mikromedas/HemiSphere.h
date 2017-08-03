#pragma once

#include "ofMain.h"

namespace mikromedas{

class ofHemiSpherePrimitive : public of3dPrimitive {
public:
    ofHemiSpherePrimitive();
    ofHemiSpherePrimitive( float radius, int res,
                      ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP );
    ~ofHemiSpherePrimitive();
    
    void set( float radius, int resolution,
             ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP );
    void setResolution( int res );
    void setRadius(float radius);
    void setMode( ofPrimitiveMode mode );
    
    float getRadius() const;
    int getResolution() const;

    static ofMesh hemiSphere( float radius, int res, ofPrimitiveMode mode );
    
protected:
    float radius;
    int resolution;
};

}   // namespace mikromedas
