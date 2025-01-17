#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include "Aresta.h"
#include "Vertice.h"

using namespace std;

class Grafo {
protected:
    bool direcionado;
    // bool verticesPonderados;
    // bool arestasPonderadas;
    // int numVertices;
    void auxNConexo(bool *visitados, Vertice *v);
public:
    Grafo();
    virtual ~Grafo();
    virtual bool eh_bipartido() = 0;
    int n_conexo(); /// Função que indica a quantidade de componentes conexas
    virtual int get_grau() = 0;
    virtual int get_ordem() = 0;
    virtual bool eh_direcionado() = 0;
    virtual bool vertice_ponderado() = 0;
    virtual bool aresta_ponderada() = 0;
    bool eh_completo(); /// Função que diz se o grafo é completo ou não
    virtual bool eh_arvore() = 0;
    virtual bool possui_articulacao() = 0;
    virtual bool possui_ponte() = 0;
    void carrega_grafo(string nomeArquivo); /// Função que lê um arquivo txt com um grafo e carrega ele
    virtual void novo_grafo(string nomeArquivo) = 0;

    // Comunicação com terminal
    virtual void salvaGrafo(string nomeArquivo) = 0;
    void imprimeGrafo(string nomeArquivo);
    // Funções para manipulação de grafos das classes filhas
    virtual void inserirVertice(int id, float peso) = 0;
    virtual void inserirAresta(int id_inicio, int id_fim, float peso) = 0;
    virtual void removerVertice(int id) = 0;
    virtual void removerAresta(int id_inicio, int id_fim) = 0;
    virtual Vertice* getVertice(int id) = 0;
    // virtual Aresta* getAresta(int id_inicio, int id_fim) = 0;
    // virtual Aresta** getVizinhos(int id) = 0;
};

#endif
