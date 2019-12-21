#include "giratorio.h"

Giratorio::Giratorio()
{
    techo = new Cono(70,170,30);
    centro = new Cilindro(110,95,30);
    plataforma = new Cilindro(3,170,30);
    columpios[0] = new Columpio(true);
    columpios[1] = new Columpio(false);

    Material morado(Tupla4f(0.5,0,0.5,1),Tupla4f(0.25,0,0.5,1),Tupla4f(0.1,0.005,0.05,1),128);
    Material azul(Tupla4f(0,0,1,1),Tupla4f(0.05,0,0.7,1),Tupla4f(0.05,0.005,0.5,1),128);
    Material verde(Tupla4f(0,1,0,1),Tupla4f(0.05,0.7,0,1),Tupla4f(0.05,0.5,0.005,1),128);

    techo->setMaterial(morado);
    centro->setMaterial(verde);
    plataforma->setMaterial(azul);
}

void Giratorio::cambiarAltura(float incremento)
{
    columpios[0]->cambiarAltura(incremento);
    columpios[1]->cambiarAltura(incremento);
}

void Giratorio::draw(const vector<Tupla3f> & colores, bool inmediato, bool visAjedrez, bool iluminacion)
{
    float rotacion = 360.0/6.0;

    plataforma->draw(colores,inmediato,visAjedrez,iluminacion);
    glPushMatrix();
        glTranslatef(0,113,0);
        techo->draw(colores,inmediato,visAjedrez,iluminacion);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,3,0);
        centro->draw(colores,inmediato,visAjedrez,iluminacion);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,3,0);
        glPushMatrix();
            glTranslatef(0,0,140);
            columpios[0]->draw(colores,inmediato,visAjedrez,iluminacion);
        glPopMatrix();
        glPushMatrix();
            glRotatef(rotacion,0,1,0);
            glTranslatef(0,0,140);
            columpios[1]->draw(colores,inmediato,visAjedrez,iluminacion);
        glPopMatrix();
        glPushMatrix();
            glRotatef(rotacion*2,0,1,0);
            glTranslatef(0,0,140);
            columpios[0]->draw(colores,inmediato,visAjedrez,iluminacion);
        glPopMatrix();
        glPushMatrix();
            glRotatef(rotacion*3,0,1,0);
            glTranslatef(0,0,140);
            columpios[1]->draw(colores,inmediato,visAjedrez,iluminacion);
        glPopMatrix();
        glPushMatrix();
            glRotatef(rotacion*4,0,1,0);
            glTranslatef(0,0,140);
            columpios[0]->draw(colores,inmediato,visAjedrez,iluminacion);
        glPopMatrix();
        glPushMatrix();
            glRotatef(rotacion*5,0,1,0);
            glTranslatef(0,0,140);
            columpios[1]->draw(colores,inmediato,visAjedrez,iluminacion);
        glPopMatrix();
    glPopMatrix();
}