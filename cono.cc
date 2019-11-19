#include "cono.h"
#include "aux.h"

Cono::Cono(const float altura, const float radio, const int num_instancias_perf)
{
    Tupla3f v1(0, altura, 0);
    Tupla3f v2(radio, 0, 0);

    vector<Tupla3f> perfil;
    perfil.push_back(v1);
    perfil.push_back(v2);
    this->crearMalla(perfil, num_instancias_perf);
}