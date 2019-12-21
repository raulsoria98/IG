#ifndef CARRUSEL_H_INCLUDED
#define CARRUSEL_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "giratorio.h"
#include "cilindro.h"

class Carrusel
{
public:
    Carrusel();
    void draw(const vector<Tupla3f> &colores, bool inmediato, bool visAjedrez, bool iluminacion);
    void cambiarRotacion(float incremento);
    void cambiarAltura(float incremento);
    void moverCaballo(float incremento);

protected:
    Giratorio *giratorio = nullptr;
    Cilindro *base = nullptr;
    Cilindro *subebaja = nullptr;
    float rotacion = 0;
    float altura = 0;
    bool estaSubiendo = true;
};

#endif