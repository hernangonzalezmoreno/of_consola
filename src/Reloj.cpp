#include "Reloj.h"

Reloj::Reloj(){}

void Reloj::actualizar(){
  millisAnterior = millisActual;
  millisActual = ofGetElapsedTimeMillis();
  deltaMillis = millisActual - millisAnterior;
}

int Reloj::getDeltaMillis(){
  return deltaMillis;
}
