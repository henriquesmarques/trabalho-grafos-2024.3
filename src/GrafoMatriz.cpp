#include "../include/GrafoMatriz.h"
#include <iostream>
#include <cstdlib>

using namespace std;

GrafoMatriz::GrafoMatriz() {
    // Alocando matriz de arestas
    MAX_VERTICES = 100;
    matriz = new Aresta**[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        matriz[i] = new Aresta*[MAX_VERTICES];
    }
    // Inicializando matriz
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            matriz[i][j] = nullptr;
        }
    }
    // Alocando vetor de vértices
    vertices = new Vertice*[MAX_VERTICES];
    // Inicializando vetor
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = nullptr;
    }
}

GrafoMatriz::GrafoMatriz(int vert, bool dir) : Grafo() {
    // Alocando matriz de arestas
    MAX_VERTICES = 100;
    matriz = new Aresta**[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        matriz[i] = new Aresta*[MAX_VERTICES];
    }
    // Inicializando matriz
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            matriz[i][j] = nullptr;
        }
    }
    // Alocando vetor de vértices
    vertices = new Vertice*[MAX_VERTICES];
    // Inicializando vetor
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = nullptr;
    }
    // Inicializando outras variáveis
    ordem = vert;
    direcionado = dir;
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        delete [] matriz[i];
    }
    delete [] matriz;
    delete [] vertices;
}

void GrafoMatriz::aumentarMatriz() {
    // Alocando uma nova matriz com mais 100 vértices
    Aresta*** novaMatriz = new Aresta**[MAX_VERTICES + 100];
    for (int i = 0; i < MAX_VERTICES + 100; i++) {
        novaMatriz[i] = new Aresta*[MAX_VERTICES + 100];
    }
    // Inicializando nova matriz com zeros e copiando valores da antiga matriz
    for (int i = 0; i < MAX_VERTICES + 100; i ++) {
        for (int j = 0; j < MAX_VERTICES + 100; j++) {
            if (i < MAX_VERTICES && j < MAX_VERTICES) {
                novaMatriz[i][j] = matriz[i][j];
            } else {
                novaMatriz[i][j] = nullptr;
            }
        }
    }
    // Alocando novo vetor de vértices
    Vertice** novosVertices = new Vertice* [MAX_VERTICES + 100];
    // Inicializando novo vetor de pesos de vértices e copiando valores do antigo vetor
    for (int i = 0; i < MAX_VERTICES + 100; i++) {
        if (i < MAX_VERTICES) {
            novosVertices[i] = vertices [i];
        } else {
            novosVertices[i] = nullptr;
        }
    }
    // Desalocando memória
    for (int i = 0; i < MAX_VERTICES; i++) {
        delete [] matriz[i];
    }
    delete [] matriz;
    delete [] vertices;
    // Atualizando variáveis
    matriz = novaMatriz;
    vertices = novosVertices;
    MAX_VERTICES = MAX_VERTICES + 100;
}

void GrafoMatriz::inserirVertice(int id, float peso) {
    if (ordem + 1 > MAX_VERTICES) {
        aumentarMatriz();
    }
    //...
}

void GrafoMatriz::inserirAresta(int id_inicio, int id_fim, float peso) {
}

void GrafoMatriz::removerVertice(int id) {
}

void GrafoMatriz::removerAresta(int id_inicio, int id_fim) {
}

Vertice* GrafoMatriz::getVertice(int id) {
    return nullptr;
}

Aresta* GrafoMatriz::getAresta(int id_inicio, int id_fim) {
    return nullptr;
}
