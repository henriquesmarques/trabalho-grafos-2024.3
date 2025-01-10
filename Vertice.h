//
// Created by gomes on 25/12/2024.
//

#ifndef VERTICE_H
#define VERTICE_H
#include "Aresta.h"

class Aresta;

class Vertice {
public:
    Vertice(int _id);
    ~Vertice();
    void setPeso(int val);
    int getPeso();
    void setProx(Vertice* v);
    Vertice* getProx();
    int getId();
    void inserirAresta(Aresta* a);
    Aresta* getAresta(int i);
    int totalArestas();
    void removerAresta(Aresta* a);
    Aresta **copiarVetorArestas();
    Aresta* getArestaPara(Vertice* v);
    Aresta** getVetorArestas();
    int totalArestasSaida();


private:
    int id;
    int peso;
    Vertice* prox;
    Aresta** arestas; /// Vetor de ponteiros de Arestas
    int n; /// Total de arestas
    int tam; /// Tamanho do vetor
    void aumentarVetor();
};

#endif //VERTICE_H
