#include "cuadro.h"
#include "material.h"

Cuadro::Cuadro()
{
    imagen = new Imagen();
    marco = new Cubo(1);

    Material morado(Tupla4f(0.5,0,0.5,1),Tupla4f(0.25,0,0.5,1),Tupla4f(0.1,0.005,0.05,1),128);

    marco->setMaterial(morado);
}

void Cuadro::draw(const vector<Tupla3f> &colores, bool inmediato, bool visAjedrez, bool iluminacion)
{
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-70.8,-40,1);
        glScalef(80,80,80);
        imagen->draw({Tupla3f(1,1,1)},inmediato,visAjedrez,iluminacion);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.3,0.7,-3);
        glScalef(80,80,30);
        glScalef(2,1.4,0.2);
        marco->draw(colores,inmediato,visAjedrez,iluminacion);
    glPopMatrix();
}

void Cuadro::asignarTextura(string archivo)
{
    imagen->asignarTextura(archivo);
}