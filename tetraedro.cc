#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
   double lado = 30;
   // inicializar la tabla de vértices
   Tupla3f v1(0,0,0);
   Tupla3f v2(lado/2,0,(lado*sqrt(3))/2);
   Tupla3f v3(lado,0,0);
   Tupla3f v4(lado/2,(lado*sqrt(6))/3,(lado*sqrt(3))/6);

   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   Tupla3i c1(0,1,3);
   Tupla3i c2(1,2,3);
   Tupla3i c3(0,3,2);
   Tupla3i c4(0,2,1);

   f.push_back(c1);
   f.push_back(c2);
   f.push_back(c3);
   f.push_back(c4);
}

