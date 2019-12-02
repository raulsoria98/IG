#include "luzPosicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & posicion)
{
    this->posicion(0) = posicion(0);
    this->posicion(1) = posicion(1);
    this->posicion(2) = posicion(2);
    this->posicion(3) = 1;
}