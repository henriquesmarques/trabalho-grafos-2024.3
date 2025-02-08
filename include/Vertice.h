#ifndef VERTICE_H
#define VERTICE_H
#include "Aresta.h"

class Aresta;

class Vertice {
public:
    Vertice(int _id);
    Vertice(int _id, float _peso);
    ~Vertice();
    void setPeso(float val);
    float getPeso();
    void setProx(Vertice* v);
    Vertice* getProx();
    int getId();
    void setId(int id);
    void inserirVizinho(Aresta* a);
    void removerVizinho(Aresta* a);
    Aresta* getVizinho(int id);
    Aresta** getVetorVizinhos();
    int getTotalVizinhos();

    Aresta **copiarVetorArestas();
    Aresta* getArestaPara(Vertice* v);
    int totalArestasSaida();
private:
    int id;
    float peso;
    Vertice* prox;
    Aresta** vizinhos; /// Vetor de ponteiros de Arestas
    int n; /// Total de arestas
    int tam; /// Tamanho do vetor
    void aumentarVetor();
};

#endif //VERTICE_H
