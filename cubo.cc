#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices
   Tupla3f a(-lado/2,-lado/2,-lado/2);
   Tupla3f b(-lado/2,-lado/2,lado/2);
   Tupla3f c(lado/2,-lado/2,lado/2);
   Tupla3f d(lado/2,-lado/2,-lado/2);
   Tupla3f e(-lado/2,lado/2,-lado/2);
   Tupla3f g(-lado/2,lado/2,lado/2);
   Tupla3f h(lado/2,lado/2,lado/2);
   Tupla3f i(lado/2,lado/2,-lado/2);
   
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);
   v.push_back(d);
   v.push_back(e);
   v.push_back(g);
   v.push_back(h);
   v.push_back(i);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   
   Tupla3i j(2,1,0);
   Tupla3i k(0,3,2);
   Tupla3i l(5,1,2);
   Tupla3i m(5,2,6);
   Tupla3i n(4,0,1);
   Tupla3i o(5,4,1);
   Tupla3i p(0,4,3);
   Tupla3i q(4,7,3);
   Tupla3i r(6,2,3);
   Tupla3i s(7,6,3);
   Tupla3i t(4,5,6);
   Tupla3i u(4,6,7);

   f.push_back(j);
   f.push_back(k);
   f.push_back(l);
   f.push_back(m);
   f.push_back(n);
   f.push_back(o);
   f.push_back(p);
   f.push_back(q);
   f.push_back(r);
   f.push_back(s);
   f.push_back(t);
   f.push_back(u);
}

