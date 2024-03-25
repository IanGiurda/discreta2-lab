#ifndef STRUCT_GRAFO_24
#define STRUCT_GRAFO_24


#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef u32 color;


typedef struct {
    u32 id;
    u32 grado;
    color color;
    u32 *vecinos; // array con todos los vecinos de este vertice

}Vertice;

//typedef VerticeSt Vertice;

typedef struct {
    u32 num_vertices;
    u32 num_lados;
    u32 delta; // el grado del vertice con mas lados
    Vertice *vertices; // arreglo con todos los vertices del grafo


}GrafoSt;



#endif