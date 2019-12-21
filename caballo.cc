#include "caballo.h"
#include "malla.h"
#include "ply_reader.h"

Caballo::Caballo()
{
    ply::read("./plys/caballo.ply", this->v, this->f);

    this->calcular_normales();
}
