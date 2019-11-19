#include "esfera.h"
#include "aux.h"

Esfera::Esfera(const float radio, const int num_instancias_perf, const int num_vertices_perfil)
{
    const float factor = M_PI/180,   // Factor para transformar sexagesimales a radianes
               gradosPorcion = 180.0 / num_vertices_perfil;  // Grados entre cada perfil
    float gradosPorcionActual = gradosPorcion;

    Tupla3f nuevoVertice;
    vector<Tupla3f> perfil;

    nuevoVertice(0) = 0;
    nuevoVertice(1) = radio;
    nuevoVertice(2) = 0;
    perfil.push_back(nuevoVertice);

    for(int i = 0; i < num_vertices_perfil - 1; i++)
    {
        nuevoVertice(1) = radio * cos(gradosPorcionActual * factor);
        nuevoVertice(0) = radio * sin(gradosPorcionActual * factor);

        perfil.push_back(nuevoVertice);

        gradosPorcionActual += gradosPorcion;
    }

    this->crearMalla(perfil, num_instancias_perf);
}