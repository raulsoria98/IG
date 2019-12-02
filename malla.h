// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(const vector<Tupla3f> & colores, bool inmediato, bool visAjedrez, bool iluminacion) ;

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   inline void setMaterial(Material mat) { m = mat; };

   protected:


   GLuint crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram); // genera VBO
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;
   GLuint id_vbo_col = 0;
   GLuint id_vbo_nor = 0;

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> c;
   std::vector<Tupla3f> nv;

   Material m;
} ;


#endif
