#include "ofApp.h"

ofApp::ofApp(){
  //reloj = new Reloj();
  //consola = new Consola( reloj );
}

//--------------------------------------------------------------
void ofApp::setup(){
  consola.setup( &reloj );
}

//--------------------------------------------------------------
void ofApp::update(){
  reloj.actualizar();
  consola.println( "Hola mundo" );
}

//--------------------------------------------------------------
void ofApp::draw(){
  //cout << "reloj.getDeltaMillis() = " << reloj.getDeltaMillis() << endl;
  //ofSetColor( 0, 0, 255 );
  //ofDrawBitmapString( "deltaMillis: " + std::to_string( reloj.getDeltaMillis() ), 10, 30 );

  ofSetColor( 224, 50, 50 );
  ofDrawRectangle( ofGetMouseX(), ofGetMouseY(), 100, 100 );

  consola.test();
  consola.println( "Estoy en el draw" );
  consola.println( reloj.hola );
  consola.println( "mouseY: " + ofToString( ofGetMouseY() ) );
  consola.ejecutar();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  consola.printlnAlerta( "Jojo hello! " + ofToString( ofGetElapsedTimeMillis() ) );
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
