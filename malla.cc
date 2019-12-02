#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
   // visualizar la malla usando glDrawElements,
   // completar (práctica 1)
   glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data() );
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   if(!nv.empty())
   {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT, 0, nv.data() );
   }
	glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
GLuint Malla3D::crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram)
{
   GLuint id_vbo;
   glGenBuffers(1, & id_vbo);
   glBindBuffer(tipo_vbo, id_vbo);
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo, 0);
   return id_vbo;
}

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   if(id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_nor == 0)
   {
      id_vbo_ver = crearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(GL_FLOAT), v.data());
      if(!nv.empty())
         id_vbo_nor = crearVBO(GL_ARRAY_BUFFER, 3*nv.size()*sizeof(GL_FLOAT), nv.data());
      id_vbo_tri = crearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(GL_FLOAT), f.data());
   }
      id_vbo_col = crearVBO(GL_ARRAY_BUFFER, 3*c.size()*sizeof(GL_FLOAT), c.data());

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col);
   glColorPointer(3, GL_FLOAT, 0, 0 );
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_COLOR_ARRAY);

   if(!nv.empty())
   {
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nor);
      glNormalPointer(GL_FLOAT, 0, 0 );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glEnableClientState(GL_NORMAL_ARRAY);
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(const vector<Tupla3f> & colores, bool inmediato, bool visAjedrez, bool iluminacion)
{
   if(visAjedrez)
   {
      glDisable(GL_LIGHTING);

      c.clear();

      Tupla3f ca1(0.5,0,1);
      Tupla3f ca2(1,1,0);
      for(int i = 0; i < v.size(); i++)
      {
         if(i % 2 == 0)
            c.push_back(ca1);
         else
            c.push_back(ca2);
      }
   }
   else
   {
      if(iluminacion)
      {
         glEnable(GL_LIGHTING);
         m.aplicar();
      }
      else
      {
         glDisable(GL_LIGHTING);

         c.clear();

         for(int i = 0; i < v.size(); i++)
         {
            c.push_back(colores[i%colores.size()]);
         }
      }
   }
   

   if(!inmediato)
      this->draw_ModoDiferido();
   else
      this->draw_ModoInmediato();
}

void Malla3D::calcular_normales()
{
   Tupla3f tupla_cero(0,0,0);
   Tupla3f vectorial, p, q, r, a, b;

   if(!nv.empty())
      nv.clear();

   for(int i = 0; i < v.size(); i++)
      nv.push_back(tupla_cero);

   for(int i = 0; i < f.size(); i++)
   {
      p = v[f[i](0)];
      q = v[f[i](1)];
      r = v[f[i](2)];

      a = Tupla3f(q(0)-p(0), q(1)-p(1), q(2)-p(2));
      b = Tupla3f(r(0)-p(0), r(1)-p(1), r(2)-p(2));
      
      vectorial = (a.cross(b)).normalized();

      nv[f[i](0)] = nv[f[i](0)] + vectorial;
      nv[f[i](1)] = nv[f[i](1)] + vectorial;
      nv[f[i](2)] = nv[f[i](2)] + vectorial;
   }
   
   for(int i = 0; i < nv.size(); i++)
      nv[i] = nv[i].normalized();
}