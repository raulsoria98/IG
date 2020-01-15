#include "columpio.h"

// Columpio::Columpio()
// {
//     Caballo caballo;
//     Cilindro cilindro;

//     for(unsigned i = 0; i < cilindro.get_v().size(); i++)
//     {
//         this->v.push_back(cilindro.get_v()[i]);
//     }

//     for(unsigned i = 0; i < caballo.get_v().size(); i++)
//     {
//         this->v.push_back(caballo.get_v()[i]);
//     }

//     for(unsigned i = 0; i < cilindro.get_f().size(); i++)
//     {
//         this->f.push_back(cilindro.get_f()[i]);
//     }

//     for(unsigned i = 0; i < caballo.get_f().size(); i++)
//     {
//         this->f.push_back(caballo.get_f()[i]);
//     }
// }

#define ALTURA_MAX 44
#define ALTURA_MIN 4

Columpio::Columpio(bool arriba)
{
    if(arriba)
    {
        altura = ALTURA_MAX;
        estaSubiendo = false;
    }
    else
    {
        altura = 3;
        estaSubiendo = true;
    }

    caballo = new Caballo();
    cilindro = new Cilindro(110,1.5,30);
    luz = new LuzPosicional(Tupla3f(0,110,0));
    luz->setId(GL_LIGHT2);

    Material madera(Tupla4f(0.85,0.45,0,1),Tupla4f(0.3,0.1,0,1),Tupla4f(0.85,0.3,0,1),40);
    Material hierro(Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.9,0.9,0.9,1),Tupla4f(0.9,0.9,0.9,1),128);

    caballo->setMaterial(madera);
    cilindro->setMaterial(hierro);
}

void Columpio::cambiarAltura(float incremento)
{
    if(altura >= ALTURA_MAX && estaSubiendo)
        estaSubiendo = false;
    if(altura <= ALTURA_MIN && !estaSubiendo)
        estaSubiendo = true;
    
    if(estaSubiendo)
        altura += incremento;
    else
        altura -= incremento;
}

void Columpio::draw(const vector<Tupla3f> & colores, bool inmediato, bool visAjedrez, bool iluminacion)
{
    // glEnable(GL_LIGHT2);
    luz->activar();

    glPushMatrix();
        glTranslatef(0,10*2.23+altura,0);
        glRotatef(-90,1,0,0);
        glScalef(10,10,10);
        caballo->draw(colores,inmediato,visAjedrez,iluminacion);
    glPopMatrix();
    glPushMatrix();
        cilindro->draw(colores,inmediato,visAjedrez,iluminacion);
    glPopMatrix();
}