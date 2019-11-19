#ifndef CILINDRO_H_DEFINED
#define CILINDRO_H_DEFINED

#include "aux.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
    public:
        Cilindro(const float altura = 1, const float radio = 1, const int num_instancias_perf = 20);
};

#endif