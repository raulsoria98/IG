#ifndef ESFERA_H_DEFINED
#define ESFERA_H_DEFINED

#include "aux.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion
{
    public:
        Esfera(const float radio = 1, const int num_instancias_perf = 20, const int num_vertices_perfil = 20);
};

#endif