#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include "Grafo.h"
#include <string>

using namespace std;

class GrafoMatriz : public Grafo {
public:
    GrafoMatriz();
    GrafoMatriz(int vertices, bool dir);
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
    void salvaGrafoMatriz(string nomeArquivo);
    void imprimeGrafo(string nomeArquivo);
private:
    static const int MAX_VERTICES = 100;
    int matriz[MAX_VERTICES][MAX_VERTICES]{};
    int numVertices;
    //bool direcionado;

    void imprimir_descricao();
    int contarArestas();
    void buscaProfundidade(int u, bool visitado[]);
    void adicionaAresta(int u, int v, int peso);
};

#endif