#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <string>

class GrafoMatriz : public Grafo {
private:
    static const int MAX_VERTICES = 100;
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
    bool direcionado;

public:
    GrafoMatriz(int vertices, bool dir);
    void imprimir_descricao();
    int contarArestas();
    void buscaProfundidade(int u, bool visitado[]);
    void adicionaAresta(int u, int v, int peso);
    void carrega_grafo(std::string nomeArquivo) override;
    virtual bool eh_bipartido() override;
    virtual int n_conexo() override;
    virtual int get_grau() override;
    virtual int get_ordem() override;
    virtual bool eh_direcionado() override;
    virtual bool eh_completo() override;
    virtual bool eh_arvore() override;
    virtual bool vertice_ponderado() override;
    virtual bool aresta_ponderada() override;
    virtual bool possui_articulacao() override;
    virtual bool possui_ponte() override;
    virtual void novo_grafo(std::string nomeArquivo) override;
    void salvaGrafoMatriz(std::string entrada, std::string nomeArquivo);
    //bool GrafoMatriz::possui_ponte() override;
    //bool GrafoMatriz::possui_articulacao() override;
};

#endif