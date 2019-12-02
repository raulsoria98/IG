#include "luzDireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f & orientacion)
{
    alpha = orientacion(0);
    beta = orientacion(1);

    posicion(0) = sin(alpha);
    posicion(1) = sin(beta);
    posicion(2) = cos(alpha)*cos(beta);
    posicion(3) = 0;
}

void LuzDireccional::variarAnguloAlpha(float incremento)
{
    alpha += incremento;

    posicion(0) = sin(alpha);
    posicion(2) = sin(alpha)*cos(beta);
}

void LuzDireccional::variarAnguloBeta(float incremento)
{
    beta += incremento;
    
    posicion(1) = sin(beta);
    posicion(2) = sin(alpha)*cos(beta);
}