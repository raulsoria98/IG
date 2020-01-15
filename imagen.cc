#include "imagen.h"

Imagen::Imagen()
{
    this->v = {Tupla3f(0,0,0), Tupla3f(1.777777,0,0), Tupla3f(0,1,0), Tupla3f(1.777777,1,0)};
    this->f = {Tupla3i(2,0,1), Tupla3i(1,3,2)};

    this->ct = {Tupla2f(0,1), Tupla2f(1,1), Tupla2f(0,0), Tupla2f(1,0)};

    this->calcular_normales();
}