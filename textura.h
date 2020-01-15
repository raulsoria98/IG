#ifndef TEXTURA_H
#define TEXURA_H

#include "aux.h"

class Textura
{
protected:
    GLuint textura_id = 0;
    vector<unsigned char> data;
    int width, height;

public:
    Textura(string archivo);
    void activar();
};

#endif