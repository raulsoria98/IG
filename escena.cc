

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
   cubo = new Cubo(50);
   caballo = new Caballo();
   carrusel = new Carrusel();
   cuadro = new Cuadro();

   // LUCES
   luz0 = new LuzDireccional(Tupla2f(0,0));
   luz0->setId(GL_LIGHT0);
   luz0->variarAnguloAlpha(-55);
   luz1 = new LuzPosicional(Tupla3f(0,100,0));
   luz1->setId(GL_LIGHT1);

   Material morado(Tupla4f(0.5,0,0.5,1),Tupla4f(0.25,0,0.5,1),Tupla4f(0.1,0.005,0.05,1),128);
   Material azul(Tupla4f(0,0,1,1),Tupla4f(0.05,0,0.7,1),Tupla4f(0.05,0.005,0.5,1),128);
   Material verde(Tupla4f(0,1,0,1),Tupla4f(0.05,0.7,0,1),Tupla4f(0.05,0.5,0.005,1),128);
   Material rojo(Tupla4f(1,0,0,1),Tupla4f(0.7,0.05,0,1),Tupla4f(0.5,0.05,0.005,1),128);
   
   peon->setMaterial(morado);
   cono->setMaterial(verde);
   caballo->setMaterial(morado);
   esfera->setMaterial(azul);
   cubo->setMaterial(azul);

   velocidadRotacion = velocidadCaballo = velocidadSubebaja = 0.2;
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

void Escena::girarCarrusel()
{
   if(girar)
   {
      carrusel->cambiarRotacion(velocidadRotacion);
      carrusel->moverCaballo(velocidadCaballo);
      carrusel->cambiarAltura(velocidadSubebaja);
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   // LuzDireccional luz0(Tupla2f(STOR(alpha),STOR(beta)));
   // luz0.setDifuso(Tupla4f(0.8,0,0.4,1));
   // luz0.setEspecular(Tupla4f(0.5,0.5,0.5,1));
   // luz0.setAmbiente(Tupla4f(0.8,0.1,0.4,1));

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

      luz0->activar();
      luz1->activar();
      
      glPushMatrix();
         carrusel->draw(colores,inmediato,visAjedrez,visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(200,55,0);
         glRotatef(90,0,1,0);
         cuadro->asignarTextura("./img/carrusel.jpg");
         cuadro->draw(colores,inmediato,visAjedrez,visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-300);
         glPushMatrix();
            glTranslatef(100,50,0);
            esfera->draw(colores, inmediato, visAjedrez, visIluminacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0,25,-100);
            cubo->draw(colores,inmediato,visAjedrez, visIluminacion);
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
            glTranslatef(0,20*2.23,100);
            glRotatef(-90,1,0,0);
            glScalef(20,20,20);
            caballo->draw(colores,inmediato,visAjedrez, visIluminacion);
         glPopMatrix();
      glPopMatrix();
   }
   glPointSize(4);
   if(visPuntos)
   {
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      luz0->activar();
      luz1->activar();

      glPushMatrix();
         carrusel->draw(colores,inmediato,visAjedrez,visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(200,55,0);
         glRotatef(90,0,1,0);
         cuadro->asignarTextura("./img/carrusel.jpg");
         cuadro->draw(colores,inmediato,visAjedrez,visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-300);
         glPushMatrix();
            glTranslatef(100,50,0);
            esfera->draw(colores, inmediato, visAjedrez, visIluminacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0,25,-100);
            cubo->draw(colores,inmediato,visAjedrez, visIluminacion);
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
            glTranslatef(0,20*2.23,100);
            glRotatef(-90,1,0,0);
            glScalef(20,20,20);
            caballo->draw(colores,inmediato,visAjedrez, visIluminacion);
         glPopMatrix();
      glPopMatrix();
   }
   if(visLineas)
   {
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      luz0->activar();
      luz1->activar();

      glPushMatrix();
         carrusel->draw(colores,inmediato,visAjedrez,visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(200,55,0);
         glRotatef(90,0,1,0);
         cuadro->asignarTextura("./img/carrusel.jpg");
         cuadro->draw(colores,inmediato,visAjedrez,visIluminacion);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-300);
         glPushMatrix();
            glTranslatef(100,50,0);
            esfera->draw(colores, inmediato, visAjedrez, visIluminacion);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0,25,-100);
            cubo->draw(colores,inmediato,visAjedrez, visIluminacion);
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
            glTranslatef(0,20*2.23,100);
            glRotatef(-90,1,0,0);
            glScalef(20,20,20);
            caballo->draw(colores,inmediato,visAjedrez, visIluminacion);
         glPopMatrix();
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
      case 'V' :
         if(modoMenu == SELVISUALIZACION)
            subMenu == GRADOS_LIBERTAD ? subMenu = NINGUN : subMenu = GRADOS_LIBERTAD;
         else
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            modoMenu=SELVISUALIZACION;
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
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
         else if(visIluminacion)
            ultimoAngulo = ALPHA;
         break;
      case 'B' :
         if(visIluminacion)
            ultimoAngulo = BETA;
         break;
      case 'I' :
         if(modoMenu == SELVISUALIZACION)
         {
            visIluminacion ? visIluminacion = false : visIluminacion = true;
         }
         break;
      case '0' :
         if(subMenu == GRADOS_LIBERTAD && grados != ROTACION)
            grados = ROTACION;
         else if(visIluminacion)
            glIsEnabled(GL_LIGHT0) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
         break;
      case '1' :
         if(modoMenu == SELDIBUJADO)
         {
            inmediato = false;
         }
         else if(subMenu == GRADOS_LIBERTAD && grados != CABALLOS)
            grados = CABALLOS;
         else if(visIluminacion)
            glIsEnabled(GL_LIGHT1) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
         break;
      case '2' :
         if(modoMenu == SELDIBUJADO)
         {
            inmediato = true;
         }
         else if(subMenu == GRADOS_LIBERTAD && grados != SUBEBAJA)
            grados = SUBEBAJA;
         else if(visIluminacion)
            glIsEnabled(GL_LIGHT2) ? glDisable(GL_LIGHT2) : glEnable(GL_LIGHT2);
         break;
      case '3' :
         if(visIluminacion)
            glIsEnabled(GL_LIGHT3) ? glDisable(GL_LIGHT3) : glEnable(GL_LIGHT3);
         break;
      case '4' :
         if(visIluminacion)
            glIsEnabled(GL_LIGHT4) ? glDisable(GL_LIGHT4) : glEnable(GL_LIGHT4);
         break;
      case '5' :
         if(visIluminacion)
            glIsEnabled(GL_LIGHT5) ? glDisable(GL_LIGHT5) : glEnable(GL_LIGHT5);
         break;
      case '6' :
         if(visIluminacion)
            glIsEnabled(GL_LIGHT6) ? glDisable(GL_LIGHT6) : glEnable(GL_LIGHT6);
         break;
      case '7' :
         if(visIluminacion)
            glIsEnabled(GL_LIGHT7) ? glDisable(GL_LIGHT7) : glEnable(GL_LIGHT7);
         break;
      case '>' :
         if(visIluminacion)
         {
            if(ultimoAngulo == ALPHA)
            {
               luz0->variarAnguloAlpha(10);
            }
            else if(ultimoAngulo == BETA)
            {
               luz0->variarAnguloBeta(10);
            }
         }
         break;
      case '<' :
         if(visIluminacion)
         {
            if(ultimoAngulo == ALPHA)
            {
               luz0->variarAnguloAlpha(-10);
            }
            else if(ultimoAngulo == BETA)
            {
               luz0->variarAnguloBeta(-10);
            }
         }
         break;
      case '+' :
            if(subMenu == JERARQUICO)
            {
               velocidadRotacion += 0.2;
               velocidadCaballo += 0.2;
               velocidadSubebaja += 0.2;
            }
            else if(subMenu == GRADOS_LIBERTAD)
            {
               if(grados == ROTACION)
                  velocidadRotacion += 0.2;
               else if(grados == CABALLOS)
                  velocidadCaballo += 0.2;
               else if(grados == SUBEBAJA)
                  velocidadSubebaja += 0.2;
            }
         break;
      case '-' :
            if(subMenu == JERARQUICO)
            {
               velocidadRotacion -= 0.2;
               velocidadCaballo -= 0.2;
               velocidadSubebaja -= 0.2;
            }
            else if(subMenu == GRADOS_LIBERTAD)
            {
               if(grados == ROTACION)
                  velocidadRotacion -= 0.2;
               else if(grados == CABALLOS)
                  velocidadCaballo -= 0.2;
               else if(grados == SUBEBAJA)
                  velocidadSubebaja -= 0.2;
            }
         break;
      case 'J' :
         if(modoMenu == SELVISUALIZACION)
         {
            girar ? girar = false : girar = true;
            subMenu == JERARQUICO ? subMenu = NINGUN : subMenu = JERARQUICO;
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
