#include "carrusel.h"

Carrusel::Carrusel()
{
    giratorio = new Giratorio();
    base = new Cilindro(10,180,30);
    subebaja = new Cilindro(100,95,30);

    Material rojo(Tupla4f(1,0,0,1),Tupla4f(0.7,0.05,0,1),Tupla4f(0.5,0.05,0.005,1),128);
    Material verde(Tupla4f(0,1,0,1),Tupla4f(0.05,0.7,0,1),Tupla4f(0.05,0.5,0.005,1),128);

    base->setMaterial(rojo);
    subebaja->setMaterial(verde);
}

void Carrusel::cambiarRotacion(float incremento)
{
    if( (rotacion + incremento) >= 360)
        rotacion = 0;
    else
        rotacion = rotacion + incremento;
}

void Carrusel::moverCaballo(float incremento)
{
    giratorio->cambiarAltura(incremento);
}

void Carrusel::cambiarAltura(float incremento)
{
    if(altura + incremento >= 60 && estaSubiendo)
        estaSubiendo = false;
    else if(altura + incremento <= 0 && !estaSubiendo)
        estaSubiendo = true;
    
    if(estaSubiendo)
        altura += incremento;
    else
        altura -= incremento;
}

void Carrusel::draw(const vector<Tupla3f> &colores, bool inmediato, bool visAjedrez, bool iluminacion)
{
    subebaja->draw(colores,inmediato,visAjedrez,iluminacion);
    base->draw(colores,inmediato,visAjedrez,iluminacion);
    glTranslatef(0,10+altura,0);
    glRotatef(rotacion,0,1,0);
    giratorio->draw(colores,inmediato,visAjedrez,iluminacion);
}