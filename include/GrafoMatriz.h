#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include "Grafo.h"

class Grafo;

/// Grafo_matriz - uso de matriz de adjacência para representar arestas
/// (quando grafo não direcionado deve ser usado a representação linear de matriz triangular).

class GrafoMatriz : public Grafo {
public:
    /// 1ª Parte do Trabalho
    GrafoMatriz();
    GrafoMatriz(bool dir);
    ~GrafoMatriz() override;
    void setDirecao(bool dir) override;
    Vertice* getVertice(int id) override;
    Aresta* getAresta(int id_inicio, int id_fim) override;
    /// 2ª Parte do Trabalho
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;
private:
    int MAX_VERTICES;
    int MAX_ARESTAS;
    Aresta **arestas; // Matriz de arestas
    Vertice **vertices; // Vetor de vértices
    void aumentarMatriz(); // Aumenta a matriz de adjacência quando ultrapassado MAX_VERTICES
    int detIndice(int i, int j); // Calcula a posição na matriz linear
    int detIndiceRemove(int i, int j); // Retorna o indice se for direcionado para funcionar no removeVertice
};

#endif
