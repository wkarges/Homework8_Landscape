#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Math/MathUtils.h"

#include "Utils/ofTrueTypeFontExt.h"
#include "Utils/Cameras/ofxWalkingFirstPersonCamera.h"

class ofApp : public ofBaseApp
{
	public:
		
		void setup();
		void update();
		void draw();
		void setNormals(ofMesh &mesh);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
		void keyPressed(int key);
	
		ofxFirstPersonCamera	camera;
		ofTrueTypeFontExt		fontSmall;
        int height = 30 ;
        int width = 30 ;
        ofMesh mesh;
        ofPoint vertex ;
    bool spacePressed ;
    bool colorPressed ;
    char keyType = 'a' ;
    vector <ofFloatColor> colors ;
};
