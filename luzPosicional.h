#ifndef LUZ_POSICIONAL
#define LUZ_POSICIONAL

#include "luz.h"

class LuzPosicional : public Luz
{
    public:
        LuzPosicional(const Tupla3f & posicion);
};

#endif