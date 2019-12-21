#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices
   Tupla3f v0(-lado/2,-lado/2,-lado/2);
   Tupla3f v1(-lado/2,-lado/2,lado/2);
   Tupla3f v2(lado/2,-lado/2,lado/2);
   Tupla3f v3(lado/2,-lado/2,-lado/2);
   Tupla3f v4(-lado/2,lado/2,-lado/2);
   Tupla3f v5(-lado/2,lado/2,lado/2);
   Tupla3f v6(lado/2,lado/2,lado/2);
   Tupla3f v7(lado/2,lado/2,-lado/2);
   
   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);
   v.push_back(v5);
   v.push_back(v6);
   v.push_back(v7);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   
   Tupla3i f0(2,1,0);
   Tupla3i f1(3,2,0);
   Tupla3i f2(5,1,2);
   Tupla3i f3(6,5,2);
   Tupla3i f4(4,0,1);
   Tupla3i f5(5,4,1);
   Tupla3i f6(0,4,3);
   Tupla3i f7(4,7,3);
   Tupla3i f8(2,3,6);
   Tupla3i f9(3,7,6);
   Tupla3i f10(5,6,4);
   Tupla3i f11(6,7,4);

   f.push_back(f0);
   f.push_back(f1);
   f.push_back(f2);
   f.push_back(f3);
   f.push_back(f4);
   f.push_back(f5);
   f.push_back(f6);
   f.push_back(f7);
   f.push_back(f8);
   f.push_back(f9);
   f.push_back(f10);
   f.push_back(f11);

   this->calcular_normales();
}

