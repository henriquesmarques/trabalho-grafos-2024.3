#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include "Grafo.h"

using namespace std;

class Grafo;

/// Grafo_matriz - uso de matriz de adjacência para representar arestas
/// (quando grafo não direcionado deve ser usado a representação linear de matriz triangular).

class GrafoMatriz : public Grafo {
public:
    /// 2ª Parte do Trabalho
    GrafoMatriz();
    GrafoMatriz(bool dir);
    ~GrafoMatriz() override;
    Vertice* getVertice(int id) override;
    Aresta* getAresta(int id_inicio, int id_fim) override;
    /// 3ª Parte do Trabalho
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;
private:
    int MAX_VERTICES;
    Aresta **matriz; // Matriz de adjacência de arestas
    Vertice **vertices; // Vetor peso dos vértices
    void aumentarMatriz(); // Aumenta a matriz de adjacência quando ultrapassado MAX_VERTICES
    int detIndice(int i, int j);
};

#endif
