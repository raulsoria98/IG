#ifndef MATERIAL
#define MATERIAL

#include "aux.h"

class Material
{
    private:
        Tupla4f ambiente;
        Tupla4f difuso;
        Tupla4f especular;
        float brillo = 0.0;

    public:
        Material() {};
        Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo);
        void aplicar();
};

#endif