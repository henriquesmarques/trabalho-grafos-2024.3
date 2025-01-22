#include "GrafoMatriz.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

GrafoMatriz::GrafoMatriz() {
    // Alocando matriz dinamicamente
    MAX_VERTICES = 100;
    matriz = new int*[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        matriz[i] = new int[MAX_VERTICES];
    }
    // Preenchendo a matriz com zeros
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            matriz[i][j] = 0; //inicializa a matriz de adjacência
        }
    }
    // Alocando vetor de vértices
    vertices = new int[MAX_VERTICES];
    // Inicializando vetor de pesos dos vértices
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = 1;
    }
    // Inicializando outras variáveis
    ordem = 0;
    direcionado = false;
}

GrafoMatriz::GrafoMatriz(int vert, bool dir) : Grafo() {
    // Alocando matriz dinamicamente
    MAX_VERTICES = 100;
    matriz = new int*[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        matriz[i] = new int[MAX_VERTICES];
    }
    // Preenchendo a matriz com zeros
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            matriz[i][j] = 0; //inicializa a matriz de adjacência
        }
    }
    // Alocando vetor de vértices
    vertices = new int[MAX_VERTICES];
    // Inicializando vetor de pesos dos vértices
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = 1;
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
    int **novaMatriz = new int *[MAX_VERTICES + 100];
    for (int i = 0; i < MAX_VERTICES + 100; i++) {
        novaMatriz[i] = new int[MAX_VERTICES + 100];
    }
    // Inicializando nova matriz com zeros e copiando valores da antiga matriz
    for (int i = 0; i < MAX_VERTICES + 100; i ++) {
        for (int j = 0; j < MAX_VERTICES + 100; j++) {
            if (i < MAX_VERTICES && j < MAX_VERTICES) {
                novaMatriz[i][j] = matriz[i][j];
            } else {
                novaMatriz[i][j] = 0;
            }
        }
    }
    // Alocando novo vetor de vértices
    int *novosVertices = new int [MAX_VERTICES + 100];
    // Inicializando novo vetor de pesos de vértices e copiando valores do antigo vetor
    for (int i = 0; i < MAX_VERTICES + 100; i++) {
        if (i < MAX_VERTICES) {
            novosVertices[i] = vertices [i];
        } else {
            novosVertices[i] = 1;
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
