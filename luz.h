#ifndef LUZ
#define LUZ

#include "aux.h"

class Luz
{
    protected:
        GLenum id;
        Tupla4f posicion;
        Tupla4f colorAmbiente = Tupla4f(0,0,0,1);
        Tupla4f colorDifuso = Tupla4f(1,1,1,1);
        Tupla4f colorEspecular = Tupla4f(1,1,1,1);

    public:
        void activar();
        void setId(GLenum id);
        void setAmbiente(Tupla4f color);
        void setDifuso(Tupla4f color);
        void setEspecular(Tupla4f color);
};

#endif