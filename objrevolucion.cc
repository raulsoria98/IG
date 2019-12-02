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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf)
{
   vector<Tupla3f> perfil;
   ply::read_vertices(archivo, perfil);
   this->tapa_inf = tapa_inf;
   this->tapa_sup = tapa_sup;
   this->crearMalla(perfil, num_instancias);
   this->calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf)
{   
   this->tapa_inf = tapa_inf;
   this->tapa_sup = tapa_sup;
   this->crearMalla(perfil, num_instancias);
   this->calcular_normales();
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

   if(perfil_original.front()(1) < perfil_original.back()(1)) // Por si nos dan el perfil_original de abajo hacia arriba
      reverse(perfil_original.begin(),perfil_original.end());

   // Localizamos si hay un polo Norte y/o un polo Sur y los eliminamos
   Tupla3f PN, PS;
   bool poloNorte = false, poloSur = false;
   if(fabs(perfil_original.front()(0)) < 0.0001 && fabs(perfil_original.front()(2)) < 0.0001)
   {
      poloNorte = true;
      PN = perfil_original.front();
      perfil_original.erase(perfil_original.begin());
   }

   if(fabs(perfil_original.back()(0)) < 0.0001 && fabs(perfil_original.back()(2)) < 0.0001)
   {
      poloSur = true;
      PS = perfil_original.back();
      perfil_original.erase(perfil_original.end()-1);
   }

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

   // Metemos los polos Norte y Sur si los había y los unimos con la figura, o en caso de haber tapas se crean
   Tupla3f central_sup, central_inf;

   // Tapa superior
   if(poloNorte)
      v.push_back(PN);
   if(tapa_sup || poloNorte)
   {
      if(!poloNorte)
      {
         central_sup(0) = 0;
         central_sup(1) = perfil_original.front()(1);
         central_sup(2) = 0;

         v.push_back(central_sup);
      }

      for(int i = 0; i < num_instancias; i++)
      {
         a = i * perfil_original.size();
         b = (i + 1)%num_instancias * perfil_original.size();
         nuevaCara(0) = b;
         nuevaCara(1) = a;
         nuevaCara(2) = v.size()-1;
         
         f.push_back(nuevaCara);
      }
   }

   // Tapa inferior
   if(poloSur)
      v.push_back(PS);
   if(tapa_inf || poloSur)
   { 
      if(!poloSur)
      {
         central_inf(0) = 0;
         central_inf(1) = perfil_original.back()(1);
         central_inf(2) = 0;

         v.push_back(central_inf);
      }
      
      for(int i = 0; i < num_instancias; i++)
      {
         a = i * perfil_original.size() + perfil_original.size() - 1;
         b = ((i + 1)%num_instancias) * perfil_original.size() + perfil_original.size() - 1;
         nuevaCara(0) = a;
         nuevaCara(1) = b;
         nuevaCara(2) = v.size()-1;
         
         f.push_back(nuevaCara);
      }
   }
}
