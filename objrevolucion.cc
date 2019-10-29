#include "aux.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf) {
   this->crearMalla(perfil, num_instancias);

   Tupla3f central_sup, central_inf;
   Tupla3i nuevaCara;
   int a, b;

   if(tapa_sup)
   {
      if(fabs(perfil.front()(0)) >= 0.0001 || fabs(perfil.front()(2)) >= 0.0001)
      {
         central_sup(0) = 0;
         central_sup(1) = perfil.front()(1);
         central_sup(2) = 0;

         v.push_back(central_sup);
      }
      else
         tapa_sup = false;
      
      if(tapa_sup)
      {
         for(int i = 0; i < num_instancias; i++)
         {
            a = i * perfil.size();
            b = (i + 1)%num_instancias * perfil.size();
            nuevaCara(0) = b;
            nuevaCara(1) = a;
            nuevaCara(2) = v.size()-1;
            
            f.push_back(nuevaCara);
         }
      }
   }

   if(tapa_inf)
   { 
      if(fabs(perfil.back()(0)) >= 0.0001 || fabs(perfil.back()(2)) >= 0.0001)
      {
         central_inf(0) = 0;
         central_inf(1) = perfil.back()(1);
         central_inf(2) = 0;

         v.push_back(central_inf);
      }
      else
         tapa_inf = false;
      
      if(tapa_inf)
      {
         for(int i = 0; i < num_instancias; i++)
         {
            a = i * perfil.size() + perfil.size() - 1;
            b = ((i + 1)%num_instancias) * perfil.size() + perfil.size() - 1;
            nuevaCara(0) = a;
            nuevaCara(1) = b;
            nuevaCara(2) = v.size()-1;
            
            f.push_back(nuevaCara);
         }
      }
   }
   

}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   if(!this->v.empty())
      this->v.clear();
   if(!this->f.empty())
      this->f.clear();

   const float factor = M_PI/180,   // Factor para transformar sexagesimales a radianes
               gradosPorcion = 360.0 / num_instancias;  // Grados entre cada perfil
   
   float gradosPerfilActual = gradosPorcion, // Grados del perfil actual respecto al original
         radio;
   
   Tupla3f nuevoVertice;

   // Metemos el perfil original en v
   for(int i = 0; i < perfil_original.size(); i++)
   {
      v.push_back(perfil_original[i]);
   }
   
   for(int i = 0; i < num_instancias - 1; i++)
   {
      for(int j = 0; j < perfil_original.size(); j++)
      {
         radio = perfil_original[j](0);
         nuevoVertice(0) = fabs(radio) * cos(gradosPerfilActual * factor);
         nuevoVertice(1) = perfil_original[j](1);
         nuevoVertice(2) = fabs(radio) * sin(gradosPerfilActual * factor);

         v.push_back(nuevoVertice);
      }
      gradosPerfilActual += gradosPorcion;
   }

   //////////////////////   CARAS   ///////////////////////////////////////////

   int a, b;
   Tupla3i nuevaCara;

   for(int i = 0; i < num_instancias; i++)
   {
      for(int j = 0; j < perfil_original.size() - 1; j++)
      {
         a = perfil_original.size() * i + j;
         b = perfil_original.size() * ((i + 1) % num_instancias) + j;

         nuevaCara(0) = a;
         nuevaCara(1) = b;
         nuevaCara(2) = b + 1;
         f.push_back(nuevaCara);

         nuevaCara(0) = a;
         nuevaCara(1) = b + 1;
         nuevaCara(2) = a + 1;
         f.push_back(nuevaCara);
      }
   }
}
