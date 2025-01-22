#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include "Grafo.h"
#include <string>

using namespace std;

class Grafo;

class GrafoMatriz : public Grafo {
public:
    /// 2ª Parte do Trabalho
    GrafoMatriz();
    GrafoMatriz(int vert, bool dir);
    ~GrafoMatriz() override;
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;
    Vertice* getVertice(int id) override;
    Aresta* getAresta(int id_inicio, int id_fim) override;
    /// Comunicação com terminal
    void salvaGrafo(string nomeArquivo) override;
private:
    int MAX_VERTICES;
    int **matriz; // Matriz de adjacência de arestas
    int *vertices; // Vetor peso dos vértices
    void aumentarMatriz(); // Aumenta a matriz de adjacência quando ultrapassado MAX_VERTICES
};

#endif
