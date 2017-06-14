#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class Util{
    
public:
    static void drawInfo();
    static void drawLineAsRect( ofVec2f p1, ofVec2f p2, float thickness);
    static void drawLineAsRect( float x1, float y1, float x2, float y2, float thickness);
    
    static void drawCircle( float x, float y, float rad, float thickness);
    static void drawArc( float x, float y, float rad, float thickness, float startAngle, float endAngle);
    
    static void replaceChar(string &text, char oldChar, char newChar);
    static void eraseChar(string &text, char eraseChar);
    static void eraseLineBreak( string & text);
    
    static void stringFit(string & text, const ofTrueTypeFontCustom& font, float fitWidth);
    static filesystem::path getResFolder();
    
    static string replaceAll(std::string str, const std::string& from, const std::string& to);
    
    static double myMap(double value, double inputMin, double inputMax, double outputMin, double outputMax, bool clamp=false);

};
