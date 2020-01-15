#ifndef CUADRO_H
#define CUADRO_H

#include "aux.h"
#include "cubo.h"
#include "imagen.h"

class Cuadro
{
    protected:
        Cubo * marco = nullptr;
        Imagen * imagen = nullptr;
    
    public:
        Cuadro();
        void draw(const vector<Tupla3f> &colores, bool inmediato, bool visAjedrez, bool iluminacion);
        void asignarTextura(string archivo);
};

#endif