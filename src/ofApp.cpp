//William Karges
//Landscape project created in-class as was required for the quiz on 5/6/15
#include "ofApp.h"

//-----------------------------------------------------------------------------------------
//
void ofApp::setup()
{
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
	
	// Give us a starting point for the camera
	camera.setNearClip(0.01f);
	camera.setPosition( 0, 4, 10 );
	camera.setMovementMaxSpeed( 0.1f );
    
    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {
            mesh.addVertex(ofPoint(x,y,0)) ;
        }
    }
    
    for(int x = 0; x< width-1; x++) {
        for(int y = 0 ; y<height-1; y++) {
            mesh.addTriangle(((x+1)+y*width), ((x+1)+(y+1)*width), (x+(y+1)*width)) ;
            mesh.addTriangle((x+y*width), ((x+1)+y*width), (x+(y+1)*width)) ;
        }
    }
    spacePressed = false ;
    colorPressed = false ;
    mesh.enableNormals() ;
	
}

//-----------------------------------------------------------------------------------------
//
void ofApp::update() {
    float time = ofGetElapsedTimef() ;
    for(int i = 0; i<mesh.getNumVertices(); i++) {
        vertex = mesh.getVertex(i) ; //set the values of ofPoint vertex to the values of the current vertex
//        vertex.z = ofSignedNoise(time) ;
        vertex.z = ofSignedNoise(vertex.x,vertex.y,time*2) ; //set the value of z between -1, 1
//        mesh.addColor(ofColor(255,ofRandom(255*vertex.z),255)) ;
        if(spacePressed) {
            vertex = ofPoint(vertex.x, vertex.y, ofMap(vertex.z, -1, 1, -3, 3)) ;
        }
        colors.push_back(vertex.z) ; //push the value of z onto the array of ofFloatColor
        mesh.addColors(colors) ; //add the array colors to the mesh
        
        if(colorPressed) {
            mesh.clearColors() ;
            if(keyType == 'r') {
                mesh.addColor(ofColor(255,0,0)) ;
            }
        }
//        mesh.setColor(i, ofFloatColor(0.0, 1.0, 1.0)) ;
        mesh.setVertex(i, vertex) ; //set the values of the vertex at position i
        colors.clear() ; //clear the array of colors

    }
    mesh.enableNormals() ;
}

//-----------------------------------------------------------------------------------------
//
void ofApp::draw()
{
	ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);	
	
	ofEnableDepthTest();
	
	camera.begin();
	
		// draw a grid on the floor
		ofSetColor( ofColor(60) );
		ofPushMatrix();
			ofRotate(90, 0, 0, -1);
			//ofDrawGrid(30,30,true,true,false,false);
            ofDrawGridPlane(10) ;
		ofPopMatrix();
    
    ofPushMatrix() ;
    ofRotate(90,0,0,0) ; //rotate the mesh horizontal
    ofTranslate(-15, -15) ; //translate the mesh
    mesh.draw(); //draw mesh
    ofPopMatrix() ;
	
	camera.end();

	ofSetColor( ofColor::white );
	ofDisableDepthTest();


	fontSmall.drawStringShadowed(ofToString(ofGetFrameRate(),2), ofGetWidth()-35, ofGetHeight() - 6, ofColor::whiteSmoke, ofColor::black );
}

//-----------------------------------------------------------------------------------------//
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}





void ofApp::keyPressed(int key)
{
	if( key == 'f' )
	{
		ofToggleFullscreen();
	}
    if( key == ' ') {
        spacePressed = !spacePressed ;
    }
//    if( key == 'r') {
//        colorPressed = !colorPressed ;
//        keyType = 'r' ;
//    }
//    if( key == 'g') {
//        
//    }
//    if( key == 'b') {
//        
//    }
}
void ofApp::mouseMoved(int x, int y ){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
}
