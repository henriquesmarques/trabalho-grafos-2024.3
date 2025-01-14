#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include "Grafo.h"
#include <string>

using namespace std;

class GrafoMatriz : public Grafo {
public:
    GrafoMatriz();
    GrafoMatriz(int vert, bool dir);
    ~GrafoMatriz() override;
    void carrega_grafo(string nomeArquivo) override;
    bool eh_bipartido() override;
    int n_conexo() override;
    int get_grau() override;
    int get_ordem() override;
    bool eh_direcionado() override;
    bool eh_completo() override;
    bool eh_arvore() override;
    bool vertice_ponderado() override;
    bool aresta_ponderada() override;
    bool possui_articulacao() override;
    bool possui_ponte() override;
    void novo_grafo(string nomeArquivo) override;
    // Métodos de comunicação com terminal
    void salvaGrafoMatriz(string nomeArquivo);
    void imprimeGrafo(string nomeArquivo);
    void imprimir_descricao();
private:
    int MAX_VERTICES;
    int **matriz; // Matriz de adjacência de arestas
    int numVertices;
    int *vertices; // Vetor que armazena o peso dos vértices
    //bool direcionado; // Declarado na classe abstrata
    void aumentarMatriz(); // Aumenta a matriz de adjacência quando ultrapassado MAX_VERTICES
    int contarArestas();
    void buscaProfundidade(int u, bool visitado[]);
    void adicionaAresta(int u, int v, int peso);
    void adicionarVertice(int peso);
};

#endif