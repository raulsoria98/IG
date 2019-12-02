

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   // crear los objetos de la escena....
   dodge = new ObjPLY("./plys/big_dodge.ply");

   peon = new ObjRevolucion("./plys/peon.ply", 50);

   cilindro = new Cilindro(50, 50);
   cono = new Cono(50,50);
   esfera = new Esfera(50,50,50);

   Material morado(Tupla4f(0.5,0,1,1),Tupla4f(0.25,0,0.5,1),Tupla4f(0.1,0.005,0.05,1),128);
   Material azul(Tupla4f(0,0,1,1),Tupla4f(0.05,0,0.7,1),Tupla4f(0.05,0.005,0.5,1),128);
   Material verde(Tupla4f(0,1,0,1),Tupla4f(0.05,0.7,0,1),Tupla4f(0.05,0.5,0.005,1),128);
   
   peon->setMaterial(morado);
   cono->setMaterial(verde);
   dodge->setMaterial(morado);
   esfera->setMaterial(azul);
   cilindro->setMaterial(azul);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{

   LuzDireccional luz0(Tupla2f(STOR(alpha),STOR(beta)));
   luz0.setId(GL_LIGHT0);
   luz0.setDifuso(Tupla4f(0.8,0,0.4,1));
   luz0.setEspecular(Tupla4f(0.5,0.5,0.5,1));
   luz0.setAmbiente(Tupla4f(0.8,0.1,0.4,1));

   LuzPosicional luz1(Tupla3f(0,100,0));
   luz1.setId(GL_LIGHT1);
   luz1.setDifuso(Tupla4f(1,1,1,1));


   // Habilitar que solo colorea una cara
   glEnable(GL_CULL_FACE);
   
   // Evita alteraciones en el tamaño de las normales
   glEnable(GL_NORMALIZE);
   
   // Colorea un triangulo del color de su último vértice
   // glShadeModel(GL_FLAT);
   glShadeModel(GL_SMOOTH);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();
   // COMPLETAR
   //   Dibujar los diferentes elementos de la escena
   // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
   // y hacer 
   
   vector<Tupla3f> colores;
      Tupla3f c0(0,0,0);
      Tupla3f c1(0,0,1);
      Tupla3f c2(0,1,0);
      Tupla3f c3(0,1,1);
      Tupla3f c4(1,0,0);
      Tupla3f c5(1,0,1);
      Tupla3f c6(1,1,0);
      Tupla3f c7(1,1,1);
      // colores.push_back(c0);
      // colores.push_back(c1);
      // colores.push_back(c2);
      // colores.push_back(c3);
      // colores.push_back(c4);
      colores.push_back(c5);
      // colores.push_back(c6);
      // colores.push_back(c7);
   
   if(visSolido)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      luz0.activar();
      luz1.activar();
      glPushMatrix();
         glTranslatef(100,50,0);
         esfera->draw(colores, inmediato, visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-100);
         glScalef(0.5,0.5,0.5);
         cilindro->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-100,0,0);
         cono->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,1.4*30,0);
         glScalef(30,30,30);
         peon->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,3.22544*6,100);
         glScalef(6,6,6);
         dodge->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
   }
   glPointSize(4);
   if(visPuntos)
   {
      luz0.activar();
      luz1.activar();
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      glPushMatrix();
         glTranslatef(100,50,0);
         esfera->draw(colores, inmediato, visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-100);
         glScalef(0.5,0.5,0.5);
         cilindro->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-100,0,0);
         cono->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,1.4*30,0);
         glScalef(30,30,30);
         peon->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,3.22544*6,100);
         glScalef(6,6,6);
         dodge->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
   }
   if(visLineas)
   {
      luz0.activar();
      luz1.activar();
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      glPushMatrix();
         glTranslatef(100,50,0);
         esfera->draw(colores, inmediato, visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-100);
         glScalef(0.5,0.5,0.5);
         cilindro->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-100,0,0);
         cono->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,1.4*30,0);
         glScalef(30,30,30);
         peon->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,3.22544*6,100);
         glScalef(6,6,6);
         dodge->draw(colores,inmediato,visAjedrez, visIluminacion);
      glPopMatrix();
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
      case 'C' :
         if(modoMenu == SELOBJETO)
         {
            modoObjeto = CUBO;
         }
         break;
      case 'T' :
         if(modoMenu == SELOBJETO)
         {
            modoObjeto = TETRAEDRO;
         }
         break;
      case 'P' :
         if(modoMenu == SELVISUALIZACION)
         {
            visPuntos ? visPuntos = false : visPuntos = true;
         }
         break;
      case 'L' :
         if(modoMenu == SELVISUALIZACION)
         {
            visLineas ? visLineas = false : visLineas = true;
         }
         break;
      case 'S' :
         if(modoMenu == SELVISUALIZACION)
         {
            visSolido ? visSolido = false : visSolido = true;
         }
         break;
      case 'A' :
         if(modoMenu == SELVISUALIZACION)
         {
            visAjedrez ? visAjedrez = false : visAjedrez = true;
         }
         else
            ultimoAngulo = ALPHA;
         break;
      case 'B' :
         ultimoAngulo = BETA;
         break;
      case 'I' :
         if(modoMenu == SELVISUALIZACION)
         {
            visIluminacion ? visIluminacion = false : visIluminacion = true;
         }
         break;
      case '0' :
            glIsEnabled(GL_LIGHT0) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
         break;
      case '1' :
         if(modoMenu == SELDIBUJADO)
         {
            inmediato = false;
         }
         else
            glIsEnabled(GL_LIGHT1) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
         break;
      case '2' :
         if(modoMenu == SELDIBUJADO)
         {
            inmediato = true;
         }
         else
            glIsEnabled(GL_LIGHT2) ? glDisable(GL_LIGHT2) : glEnable(GL_LIGHT2);
         break;
      case '3' :
            glIsEnabled(GL_LIGHT3) ? glDisable(GL_LIGHT3) : glEnable(GL_LIGHT3);
         break;
      case '4' :
            glIsEnabled(GL_LIGHT4) ? glDisable(GL_LIGHT4) : glEnable(GL_LIGHT4);
         break;
      case '5' :
            glIsEnabled(GL_LIGHT5) ? glDisable(GL_LIGHT5) : glEnable(GL_LIGHT5);
         break;
      case '6' :
            glIsEnabled(GL_LIGHT6) ? glDisable(GL_LIGHT6) : glEnable(GL_LIGHT6);
         break;
      case '7' :
            glIsEnabled(GL_LIGHT7) ? glDisable(GL_LIGHT7) : glEnable(GL_LIGHT7);
         break;
      case '>' :
            if(ultimoAngulo == ALPHA)
            {
               alpha = (alpha + 10)%360;
               cout << "Nuevo alpha: " << alpha << endl;
            }
            else if(ultimoAngulo == BETA)
            {
               beta = (beta + 10)%360;
               cout << "Nuevo beta: " << beta << endl;
            }
         break;
      case '<' :
            if(ultimoAngulo == ALPHA)
            {
               alpha = (alpha - 10)%360;
               cout << "Nuevo alpha: " << alpha << endl;
            }
            else if(ultimoAngulo == BETA)
            {
               beta = (beta - 10)%360;
               cout << "Nuevo beta: " << beta << endl;
            }
         break;
   }
   // glutPostRedisplay();
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
