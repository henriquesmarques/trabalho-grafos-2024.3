#include "../include/GrafoMatriz.h"
#include <iostream>
#include <cstdlib>

using namespace std;

GrafoMatriz::GrafoMatriz() {
    MAX_VERTICES = 10;
    // Alocando matriz de arestas
    matriz = new Aresta*[MAX_VERTICES];
    // Alocando vetor de vértices
    vertices = new Vertice*[MAX_VERTICES];
    // Inicializando vetor de vértices e matriz de arestas
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = nullptr;
        matriz[i] = nullptr;
    }
}

GrafoMatriz::GrafoMatriz(bool dir) {
    MAX_VERTICES = 10;
    // Alocando matriz de arestas
    matriz = new Aresta*[MAX_VERTICES];
    // Alocando vetor de vértices
    vertices = new Vertice*[MAX_VERTICES];
    // Inicializando vetor de vértices e matriz de arestas
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = nullptr;
        matriz[i] = nullptr;
    }
    // Inicializando outras variáveis
    direcionado = dir;
}

GrafoMatriz::~GrafoMatriz() {
    delete [] matriz;
    delete [] vertices;
}

void GrafoMatriz::aumentarMatriz() {
    // Alocando uma nova matriz com o dobro de tamanho
    Aresta** novaMatriz = new Aresta*[MAX_VERTICES*2];
    // Inicializando nova matriz e copiando valores da antiga
    for (int i = 0; i < MAX_VERTICES*2; i ++) {
        if (i < MAX_VERTICES) {
            novaMatriz[i] = matriz[i];
        } else {
            novaMatriz[i] = nullptr;
        }
    }
    // Alocando novo vetor de vértices
    Vertice** novosVertices = new Vertice* [MAX_VERTICES*2];
    // Inicializando novo vetor de pesos de vértices e copiando valores do antigo
    for (int i = 0; i < MAX_VERTICES*2; i++) {
        if (i < MAX_VERTICES) {
            novosVertices[i] = vertices[i];
        } else {
            novosVertices[i] = nullptr;
        }
    }
    // Desalocando memória
    delete [] matriz;
    delete [] vertices;
    // Atualizando variáveis
    matriz = novaMatriz;
    vertices = novosVertices;
    MAX_VERTICES = MAX_VERTICES*2;
}

int GrafoMatriz::detIndice(int i, int j) {
    if (direcionado) {
        if (i < j && i < MAX_VERTICES && j > i && j < MAX_VERTICES) {
            return (j+1)*j/2+i; // caso especifico para matriz superior
        }
    } else {
        if (i >= 0 && i < MAX_VERTICES && j >= 0 && j < MAX_VERTICES) {
            return MAX_VERTICES * i + j;
        }
    }
    return -1;
}

Vertice* GrafoMatriz::getVertice(int id) {
    return vertices[id-1];
}

Aresta* GrafoMatriz::getAresta(int id_inicio, int id_fim) {
    int k = detIndice(id_inicio-1, id_fim-1);
    return matriz[k];
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
