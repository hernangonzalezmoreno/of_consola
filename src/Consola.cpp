#include "Consola.h"

void Consola::setup( Reloj *_reloj ){
  reloj = _reloj;
  debug = verFps = verDatos = verAlertas = true;
  colorTexto = ofColor( 0, 0, 0 );
  colorAlerta = ofColor( 204, 153, 0 );//0xCC9900 );
  tamanoTexto = 14;
  tamanoAlerta = 14;
}

void Consola::println( string _texto ){
  texto += _texto + "\n";
}

void Consola::printlnAlerta( string _alerta ){
  //Creo un Alerta y paso la referencia al vector alertas
  alertas.push_back( *new Alerta( _alerta ) );
  cout << _alerta << endl;
}

void Consola::printlnAlerta( string _alerta, ofColor col ){
  //Creo un Alerta y paso la referencia al vector alertas
  alertas.push_back( *new Alerta( _alerta, col ) );
  cout << _alerta << endl;
}

void Consola::printlnError( string _alerta ){
  //Creo un Alerta y paso la referencia al vector alertas
  alertas.push_back( *new Alerta( _alerta, ofColor( 255, 0, 0 ) ) );
  cout << _alerta << endl;
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
  ofPushStyle();

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

  // textAlign( RIGHT, BOTTOM );
  // textSize( tamanoAlerta );
  imprimirAlertas( verAlertas );

  ofPopStyle();
}

void Consola::ejecutarNoDebug(){
  if( !texto.empty() ) cout << texto << endl;
  imprimirAlertas( false );
}

void Consola::imprimirAlertas( bool _debugAlertas ){
  //float posY = tamanoAlerta + tamanoAlerta * (LEADIN * 0.16666666) ;//0.25
  //float posY = 14.0;
  float posY = (float) tamanoAlerta;

  cout << "cantidad de alertas: " << alertas.size() << endl;
  for( int i = alertas.size() - 1; i >= 0; i-- ){
    /*se puede acceder a los elementos de alerta mediante
      alertas.at( i ) -> esta formas es mas segura
      porque si accedemos a un elemento que no existe, devuelve una excepcion
      La otra formas es alertas[ i ], no devuelve excepcion
      Yo voy a usar esta ultima porque estoy seguro que voy a entrar
      a una posicion correcta
    */

    cout << "ALERTA: " << alertas[ i ].getAlerta() << endl;
    Alerta *a = &alertas[ i ];
    a->ejecutar( reloj );

    if( a->getEstado() == Alerta::ESTADO_ELIMINAR ){
      cout << "TENGO QUE ELIMINAR" << endl;
      //a->~Alerta();//Quisiera borrar la memoria antes de eliminarlo del vector, pero se cierra el programa, la cuestion es que tengo q preguntar en los foros
      alertas.erase( alertas.begin() + i );
    }else if( _debugAlertas ){

      //------ NUEVO rectangulo negro de fondo
      if( a->getEstado() == Alerta::ESTADO_MOSTRAR )
        ofSetColor( 0 );
      else
        ofSetColor( 0, ofMap( a->getTiempo(), 0, Alerta::TIEMPO_DESAPARECER, 255, 0 ) );

      ofRectangle boundingBox = getBitmapStringBoundingBox( a->getAlerta() );
      //ofDrawRectangle( ofGetWidth() - boundingBox.getWidth(), posY - tamanoAlerta, boundingBox.getWidth(), tamanoAlerta );// definido altura con tamanoAlerta, porque boundingBox.getHeight() no anda exactamente como lo esperado
      ofDrawRectangle( ofGetWidth() - boundingBox.getWidth() - 5, posY - tamanoAlerta * ( LEADIN * 0.875 ), boundingBox.getWidth() + 5, tamanoAlerta * LEADIN );
      //------

      ofColor auxColorAlerta = ( a->isPersonalizado() ) ? a->getColorPersonalizado() : colorAlerta ;
      if( a->getEstado() == Alerta::ESTADO_MOSTRAR )
        ofSetColor( auxColorAlerta );
      else
        ofSetColor( auxColorAlerta, ofMap( a->getTiempo(), 0, Alerta::TIEMPO_DESAPARECER, 255, 0 ) );

      ofDrawBitmapString( a->getAlerta(), ofGetWidth() - boundingBox.getWidth(), posY - 2 );
      // posY += tamanoAlerta;
      posY += tamanoAlerta * LEADIN;

      if( posY > ofGetHeight() && i - 1 >= 0 ){
        removerAlertasFueraDePantalla( i - 1 );
        return;
      }

    }

  }

  /*
  for( int i = alertas.size() - 1; i >= 0; i-- ){

      Alerta a = alertas.get( i );
      a.ejecutar();

      if( a.getEstado() == Alerta.ESTADO_ELIMINAR ){
        alertas.remove( i );
      }else if( debug ){

        //------ NUEVO rectangulo negro de fondo

        if( a.getEstado() == Alerta.ESTADO_MOSTRAR )
          fill( 0 );
        else
          fill( 0, map( a.getTiempo(), 0, Alerta.TIEMPO_DESAPARECER, 255, 0 ) );

        rect( width - textWidth( a.getAlerta() ) - 5, posY- tamanoAlerta * ( LEADIN * 0.875 ), textWidth( a.getAlerta() ) + 5, tamanoAlerta * LEADIN );

        //------

        color auxColorAlerta = a.isPersonalizado() ? a.getColorPersonalizado() : colorAlerta ;
        if( a.getEstado() == Alerta.ESTADO_MOSTRAR )
          fill( auxColorAlerta );
        else
          fill( auxColorAlerta, map( a.getTiempo(), 0, Alerta.TIEMPO_DESAPARECER, 255, 0 ) );

        text( a.getAlerta(), width, posY );
        posY += tamanoAlerta * LEADIN;

        if( posY > height && i - 1 >= 0 ){
          removerAlertasFueraDePantalla( i - 1 );
          return;
        }

      }

    }//end for
  */
}

void Consola::removerAlertasFueraDePantalla( int desde ){
  for( int i = desde; i >= 0; i-- )
    alertas.erase( alertas.begin() + i );
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

//ALERTA

Consola::Alerta::Alerta(){
  estado = ESTADO_MOSTRAR;
  tiempo = 0;
  personalizado = false;
}

Consola::Alerta::Alerta( string _alerta ) : Alerta(){
  alerta = _alerta;
}

Consola::Alerta::Alerta( string _alerta, ofColor _colorPersonalizado ) : Alerta( _alerta ){
  colorPersonalizado = _colorPersonalizado;
  personalizado = true;
}

Consola::Alerta::~Alerta(){}

string Consola::Alerta::getAlerta(){
  return alerta;
}

uint8_t Consola::Alerta::getEstado(){
  return estado;
}

int Consola::Alerta::getTiempo(){
  return tiempo;
}

bool Consola::Alerta::isPersonalizado(){
  return personalizado;
}

ofColor Consola::Alerta::getColorPersonalizado(){
  return colorPersonalizado;
}

void Consola::Alerta::ejecutar( Reloj *reloj){

  tiempo += reloj->getDeltaMillis();
  if( estado == ESTADO_MOSTRAR && tiempo > TIEMPO_MOSTRAR ){
    estado = ESTADO_DESAPARECER;
    tiempo = 0;
  }else if( estado == ESTADO_DESAPARECER && tiempo > TIEMPO_DESAPARECER ){
    estado = ESTADO_ELIMINAR;
  }

}
