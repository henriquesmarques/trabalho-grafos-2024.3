#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include "Grafo.h"
#include <string>

using namespace std;

class Grafo;

class GrafoMatriz : public Grafo {
public:

    // void carrega_grafo(string nomeArquivo);
    bool eh_bipartido() override;
    // int n_conexo() override;
    int get_grau() override;
    int get_ordem() override;
    bool eh_direcionado() override;
    // bool eh_completo() override;
    bool eh_arvore() override;
    bool vertice_ponderado() override;
    bool aresta_ponderada() override;
    bool possui_articulacao() override;
    bool possui_ponte() override;
    void novo_grafo(string nomeArquivo) override;
    void salvaGrafo(string nomeArquivo) override; // Metodo de comunicação com terminal
    // void imprimeGrafo(string nomeArquivo) override;

    /// 2ª Parte do Trabalho
    GrafoMatriz();
    GrafoMatriz(int vert, bool dir);
    ~GrafoMatriz() override;
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;

private:
    int MAX_VERTICES;
    int **matriz; // Matriz de adjacência de arestas
    int numVertices;
    int *vertices; // Vetor peso dos vértices

    void aumentarMatriz(); // Aumenta a matriz de adjacência quando ultrapassado MAX_VERTICES
    void imprimir_descricao();
    int contarArestas();
    void buscaProfundidade(int u, bool visitado[]);
    void adicionaAresta(int u, int v, int peso);
    void adicionarVertice(int peso);
};

#endif