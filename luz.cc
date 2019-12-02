#include "luz.h"

void Luz::setId(GLenum id)
{
    this->id = id;
}

void Luz::setAmbiente(Tupla4f color)
{
    colorAmbiente = color;
}

void Luz::setDifuso(Tupla4f color)
{
    colorDifuso = color;
}

void Luz::setEspecular(Tupla4f color)
{
    colorEspecular = color;
}

void Luz::activar()
{   
    glLightfv(id, GL_AMBIENT, colorAmbiente);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);

    glLightfv(id, GL_POSITION, posicion);
}