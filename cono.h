#ifndef CONO_H_DEFINED
#define CONO_H_DEFINED

#include "aux.h"
#include "objrevolucion.h"

class Cono : public ObjRevolucion
{
    public:
        Cono(const float altura = 1, const float radio = 1, const int num_instancias_perf = 20);
};

#endif