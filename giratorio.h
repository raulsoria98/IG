#ifndef GIRATORIO_H_INCLUDED
#define GIRATORIO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "columpio.h"
#include "cilindro.h"
#include "cono.h"

class Giratorio
{
public:
    Giratorio();
    void draw(const vector<Tupla3f> & colores, bool inmediato, bool visAjedrez, bool iluminacion);
    void cambiarAltura(float incremento);

protected:
    Cono *techo = nullptr;
    Cilindro *plataforma = nullptr;
    Cilindro *centro = nullptr;
    Columpio *columpios[2] = {nullptr, nullptr};
};

#endif