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
    cout << "Incremento de alpha: " << incremento << endl;
    alpha = STOR( (int)(RTOS(alpha) + incremento)%360 );
    cout << "Nuevo alpha: " << RTOS(alpha) << endl;

    posicion(0) = sin(alpha);
    posicion(2) = cos(alpha)*cos(beta);
}

void LuzDireccional::variarAnguloBeta(float incremento)
{
    cout << "Incremento de beta: " << incremento << endl;
    beta = STOR( (int)(RTOS(beta) + incremento)%360 );
    cout << "Nuevo beta: " << RTOS(beta) << endl;
    
    posicion(1) = sin(beta);
    posicion(2) = cos(alpha)*cos(beta);
}