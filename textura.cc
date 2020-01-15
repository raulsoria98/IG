#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(string archivo)
{
    jpg::Imagen *pimg = new jpg::Imagen(archivo);
    this->height = pimg->tamY();
    this->width = pimg->tamX();

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned char *rgb = pimg->leerPixel(j,i);
            data.push_back(rgb[0]);
            data.push_back(rgb[1]);
            data.push_back(rgb[2]);
        }
    }
    glGenTextures(1, &this->textura_id);
}

void Textura::activar()
{
    glBindTexture(GL_TEXTURE_2D, this->textura_id);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // TRASFIERE LOS DATOS A GPU
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, &this->data[0]);
}