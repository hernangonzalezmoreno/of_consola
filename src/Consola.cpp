#include "Consola.h"

void Consola::setup( Reloj *_reloj ){
  reloj = _reloj;
  debug = verFps = verDatos = verAlertas = true;
  colorTexto = ofColor( 0, 0, 0 );
}

void Consola::test(){
  //std::cout << "LEADIN" << '\n';
  //cout << LEADIN << endl;
  //cout << debug << endl;
  //cout << getFps() << endl;
  println( "deltaMillis: " + std::to_string( reloj->getDeltaMillis() ) );
  reloj->hola = "nuevo valor";
}

void Consola::println( string t ){
  texto += t + "\n";
}

void Consola::ejecutar(){
  if( !verDatos ) texto = "";
  if( verFps ) texto = "fps: " + ofToString(ofGetFrameRate(),2) + "\n" + texto;

  if( debug ) ejecutarDebug();
  else ejecutarNoDebug();
  texto = "";
}

//METODOS PRIVADOS
void Consola::ejecutarDebug(){
  //pushStyle();//heredado de Processing

  //noStroke();
  //rectMode( CORNER );

  //NUEVO rectangulo blanco de fondo

  ofSetColor( 255 );
  int desde = 0, hasta = 0, iteracion = 0;
  //cout << "tamano: " << texto.size() << endl;
  //cout << "longitud: " << texto.length() << endl;

  while( desde < texto.size() && texto.find( "\n", desde ) > 0 ){
    hasta = texto.find( "\n", desde );
    string aux = texto.substr( desde, hasta );

    ofRectangle boundingBox = getBitmapStringBoundingBox( aux );
    ofDrawRectangle( 0, iteracion * 14, boundingBox.getWidth() + 3, 14 );//14 definido literal, porque boundingBox.getHeight() no anda exactamente como lo esperado

    desde = hasta + 1;
    iteracion++;
  }

  //Opcion interesante
  //ofRectangle boundingBox = getBitmapStringBoundingBox( texto );
  //ofDrawRectangle( 0, 0, boundingBox.getWidth() + 3, boundingBox.getHeight() );

  ofSetColor( colorTexto );
  ofDrawBitmapString( texto, 0, 13 );
  if( !texto.empty() ) cout << texto << endl;

  //popStyle();//heredado de Processing
}

void Consola::ejecutarNoDebug(){
  //if( !texto.equals("") ) System.out.println( texto );
}

//Como no cargue ninguna fuente(tipografia) debo utilizar este metodo para saber el ancho de la cadena
ofRectangle Consola::getBitmapStringBoundingBox(string text){
  vector<string> lines = ofSplitString(text, "\n");
      int maxLineLength = 0;
      for(int i = 0; i < (int)lines.size(); i++) {
          // tabs are not rendered
          const string & line(lines[i]);
          int currentLineLength = 0;
          for(int j = 0; j < (int)line.size(); j++) {
              if (line[j] == '\t') {
                  currentLineLength += 8 - (currentLineLength % 8);
              } else {
                  currentLineLength++;
              }
          }
          maxLineLength = MAX(maxLineLength, currentLineLength);
      }

      int padding = 4;
      int fontSize = 8;
      float leading = 1.7;
      int height = lines.size() * fontSize * leading - 1;
      int width = maxLineLength * fontSize;
  return ofRectangle(0,0,width, height);
}

/*
private void ejecutarDebug(){
  pushStyle();

    textAlign( LEFT, TOP );
    textSize( tamanoTexto );
    textLeading( tamanoTexto * LEADIN );

    noStroke();
    rectMode( CORNER );

    //NUEVO rectangulo negro de fondo

    fill( 255 );
    int desde = 0, hasta = 0, iteracion = 0;
    while( texto.indexOf( "\n", desde ) > 0 ){

      hasta = texto.indexOf( "\n", desde );
      String aux = texto.substring( desde, hasta );

      rect( 0, iteracion * (tamanoTexto * LEADIN), textWidth( aux ) + 3, tamanoTexto * ( LEADIN * 1.1666666 ) );

      desde = hasta + 1;
      iteracion++;
    }

    //

    fill( colorTexto );
    text( texto, 0, 3 );
    if( !texto.equals("") ) System.out.println( texto );

    textAlign( RIGHT, BOTTOM );
    textSize( tamanoAlerta );
    imprimirAlertas( verAlertas );

  popStyle();
}

private void ejecutarNoDebug(){
  if( !texto.equals("") ) System.out.println( texto );
  imprimirAlertas( false );
}*/
