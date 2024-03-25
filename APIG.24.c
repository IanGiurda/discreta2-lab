#include <stdio.h>
#include <stdlib.h>
#include "APIG24.h"

void imprimirVecinos(Grafo grafo, u32 verticeId) {
    // Verificar si el grafo y el vértice son válidos
    if (grafo == NULL || verticeId >= grafo->num_vertices) {
        printf("Error: Grafo o vértice no válidos.\n");
        return;
    }

    // Obtener el vértice correspondiente al identificador
    Vertice *vertice = &(grafo->vertices[verticeId]);

    // Verificar si el vértice tiene vecinos
    if (vertice->vecinos == NULL) {
        printf("El vértice %u no tiene vecinos.\n", verticeId);
        return;
    }

    printf("Vecinos del vértice %u:\n", verticeId);
    for (u32 i = 0; i < vertice->grado; i++) {
        printf("%u ", vertice->vecinos[i]);
    }
    printf("\n");
}


Grafo ConstruirGrafo(const char* nombreArchivo) {

    // Abrimos el archivo
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        // Error al abrir el archivo
        printf("ERROR: al abrir el archivo");
        return NULL;
    }

    // Leemos y guardamos el nro de vertices y lados
    u32 num_vertices, num_lados;
    if (fscanf(archivo, "p edge %u %u\n", &num_vertices, &num_lados) != 2) {
        // Error al leer el número de vértices y lados
        printf("Error al leer el número de vértices y lados");
        fclose(archivo);
        return NULL;
    }

    Grafo nuevoGrafo = (Grafo)malloc(sizeof(GrafoSt)); // Asignar memoria para el grafo
    if (nuevoGrafo == NULL) {
        // Error de asignación de memoria
        printf("Error de asignación de memoria");
        fclose(archivo);
        return NULL;
    }
    // Inicializacion de Grafo
    nuevoGrafo->num_vertices = num_vertices;
    nuevoGrafo->num_lados = num_lados;
    nuevoGrafo->vertices = malloc(sizeof(Vertice) * num_vertices);


    // Inicializar listas de vecinos para cada vértice
    for (u32 i = 0; i < num_vertices; i++) {
        nuevoGrafo->vertices[i].id = i;
        nuevoGrafo->vertices[i].grado = 0;
        nuevoGrafo->vertices[i].vecinos = NULL; // Inicializar la lista de vecinos como vacía
    }

    u32 v1, v2;
    while (fscanf(archivo, "e %u %u\n", &v1, &v2) == 2) {
        printf("e %u %u\n", v1, v2);
        // Incrementar el grado de cada vértice
        nuevoGrafo->vertices[v1].grado++;
        nuevoGrafo->vertices[v2].grado++;

        // Asignar memoria para el vecino v2 en el vértice v1
        nuevoGrafo->vertices[v1].vecinos = realloc(nuevoGrafo->vertices[v1].vecinos, sizeof(u32) * nuevoGrafo->vertices[v1].grado);
        // Asignar memoria para el vecino v1 en el vértice v2
        nuevoGrafo->vertices[v2].vecinos = realloc(nuevoGrafo->vertices[v2].vecinos, sizeof(u32) * nuevoGrafo->vertices[v2].grado);

        // Agregar v2 a los vecinos de v1
        nuevoGrafo->vertices[v1].vecinos[nuevoGrafo->vertices[v1].grado - 1] = v2;
        // Agregar v1 a los vecinos de v2
        nuevoGrafo->vertices[v2].vecinos[nuevoGrafo->vertices[v2].grado - 1] = v1;
    }

    imprimirVecinos(nuevoGrafo,0);
    imprimirVecinos(nuevoGrafo,1);
    imprimirVecinos(nuevoGrafo,2);
    imprimirVecinos(nuevoGrafo,3);
    imprimirVecinos(nuevoGrafo,4);


    fclose(archivo);
    return nuevoGrafo;
}


int main(){
    ConstruirGrafo("grafos/2gb.txt");
}