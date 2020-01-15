#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzPosicional.h"
#include "luzDireccional.h"
#include "carrusel.h"
#include "cuadro.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
typedef enum {INMEDIATO, DIFERIDO} menuDibujado;
typedef enum {ALPHA, BETA} Angulos;
typedef enum {NINGUN, GRADOS_LIBERTAD, JERARQUICO} sub_menu;
typedef enum {CABALLOS, SUBEBAJA, ROTACION} grados_libertad;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu = NADA;
   sub_menu subMenu = NINGUN;
   grados_libertad grados = ROTACION;
   
   Angulos ultimoAngulo = ALPHA;

   bool inmediato = false,
        visPuntos = false,
        visLineas = false,
        visSolido = true,
        visAjedrez = false,
        visIluminacion = false,
        girar = false;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * dodge = nullptr;
   ObjRevolucion * peon = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   Caballo * caballo = nullptr;
   Columpio * columpio = nullptr;
   Giratorio * giratorio = nullptr;
   Carrusel * carrusel = nullptr;
   LuzDireccional * luz0 = nullptr;
   LuzPosicional * luz1 = nullptr;
   Cuadro * cuadro = nullptr;

    float velocidadRotacion, velocidadCaballo, velocidadSubebaja;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void girarCarrusel();

};
#endif
