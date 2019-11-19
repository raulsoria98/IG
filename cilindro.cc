#include "cilindro.h"
#include "aux.h"

Cilindro::Cilindro(const float altura, const float radio, const int num_instancias_perf)
{
    Tupla3f v1(radio, 0, 0);
    Tupla3f v2(radio, altura, 0);

    vector<Tupla3f> perfil;
    perfil.push_back(v1);
    perfil.push_back(v2);
    this->crearMalla(perfil, num_instancias_perf);
}