#ifndef _RELOJ
#define _RELOJ

#include "ofMain.h"

class Reloj{
  public:
    //metodos
    Reloj();//constructor
    void actualizar();
    int getDeltaMillis();

  private:
    //variables
    int millisActual, millisAnterior, deltaMillis;
};

#endif
