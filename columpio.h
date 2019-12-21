#ifndef COLUMPIO_H_INCLUDED
#define COLUMPIO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "caballo.h"
#include "cilindro.h"

class Columpio
{
public:
    Columpio(bool arriba = false);
    void draw(const vector<Tupla3f> &colores, bool inmediato, bool visAjedrez, bool iluminacion);
    void cambiarAltura(float incremento);

protected:
    Caballo *caballo = nullptr;
    Cilindro *cilindro = nullptr;
    float altura;
    bool estaSubiendo;
};

#endif