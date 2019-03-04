#ifndef _CONSOLA
#define _CONSOLA

#include "ofMain.h"
//#include "ofApp.h"
#include "Reloj.h"
#define LEADIN 1.5

class Consola{
  public:
    void setup( Reloj *_reloj );
    //geters and seters
    //proximamente..
    void println( string texto );
    void printlnAlerta( string );
    void printlnAlerta( string, ofColor );
    void printlnError( string alerta );
    void ejecutar();

  private:
    //variables
    //ofApp *app;
    Reloj *reloj;
    string texto;
    ofColor colorTexto, colorAlerta;
    int tamanoTexto, tamanoAlerta;
    bool debug;
    bool verFps, verDatos, verAlertas;
    //METODOS
    void ejecutarDebug();
    void ejecutarNoDebug();
    void imprimirAlertas( bool );
    void removerAlertasFueraDePantalla( int );
    ofRectangle getBitmapStringBoundingBox( string );

    class Alerta{
      public:
        Alerta();
        Alerta(string _alerta);
        Alerta( string _alerta, ofColor _colorPersonalizado );
        ~Alerta();
        string getAlerta();
        uint8_t getEstado();
        int getTiempo();
        bool isPersonalizado();
        ofColor getColorPersonalizado();
        void ejecutar( Reloj *reloj );
        static const uint8_t
        ESTADO_MOSTRAR = 0x00,
        ESTADO_DESAPARECER = 0x01,
        ESTADO_ELIMINAR = 0x02;
        static const int
        TIEMPO_MOSTRAR = 5000,
        TIEMPO_DESAPARECER = 2000;
      private:
        string alerta;
        ofColor colorPersonalizado;
        bool personalizado;
        uint8_t estado;
        int tiempo;
    };

    vector<Alerta> alertas;
    //private ArrayList<Alerta> alertas = new ArrayList<Alerta>();

};

#endif

/*variables privadas

private String texto;
private ArrayList<Alerta> alertas = new ArrayList<Alerta>();
private color colorTexto, colorAlerta;
private int tamanoTexto, tamanoAlerta;
private boolean debug;

private boolean verFps, verDatos, verAlertas;

private static final float LEADIN = 1.5; //--- NUEVO!

*/

/*
//--------------------------------------- METODOS PUBLICOS

  //GETERS AND SETERS
  public void setDebug( boolean debug ){
    this.debug = debug;
  }

  public void setVerFps( boolean verFps ){
    this.verFps = verFps;
  }

  public void setVerDatos( boolean verDatos ){
    this.verDatos = verDatos;
  }

  public void setVerAlertas( boolean verAlertas ){
    this.verAlertas = verAlertas;
  }

  public boolean getDebug(){
    return debug;
  }

  public boolean getVerFps(){
    return verFps;
  }

  public boolean getVerDatos(){
    return verDatos;
  }

  public boolean getVerAlertas(){
    return verAlertas;
  }
  //--------

  public void println( String texto ){
    this.texto += texto + "\n";
  }

  public void printlnAlerta( String alerta ){
    alertas.add( new Alerta( alerta ) );
    System.out.println( alerta );
  }

  public void printlnAlerta( String alerta, color colorPersonalizado ){
    alertas.add( new Alerta( alerta, colorPersonalizado ) );
    System.out.println( alerta );
  }

  public void printlnError( String alerta ){
    alertas.add( new Alerta( alerta, color( #FF0000 ) ) );
    System.err.println( alerta );
  }

  public void ejecutar(){

    if( !verDatos ) texto = "";
    if( verFps ) texto = "fps: " + nf( frameRate, 0, 2 ) + "\n" + texto;

    if( debug ) ejecutarDebug();
    else ejecutarNoDebug();
    texto = "";
  }
*/

/*
//--------------------------------------- METODOS PRIVADOS

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
  }

  private void imprimirAlertas( boolean debug ){

    float posY = tamanoAlerta + tamanoAlerta * (LEADIN * 0.16666666) ;//0.25

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

  }

  private void removerAlertasFueraDePantalla( int desde ){
    for( int i = desde; i >= 0; i-- )
      alertas.remove( i );
  }
*/
