#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
   double lado = 50;
   const double pi = M_PI;
   double fac = pi/180;
   double z = (lado/2)*tan(30*fac);
   double y = z*sin(60*fac);

   // inicializar la tabla de vértices
   Tupla3f v1(-lado/2,-y,-z);
   Tupla3f v2(0,-y,((lado*sqrt(3))/2)-z);
   Tupla3f v3(lado/2,-y,-z);
   Tupla3f v4(0,((lado*sqrt(6))/3)-y,((lado*sqrt(3))/6)-z);

   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   Tupla3i f1(1,3,0);
   Tupla3i f2(1,2,3);
   Tupla3i f3(0,3,2);
   Tupla3i f4(0,2,1);

   f.push_back(f1);
   f.push_back(f2);
   f.push_back(f3);
   f.push_back(f4);
}

