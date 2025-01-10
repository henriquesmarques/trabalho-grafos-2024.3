#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>

using namespace std;

class Grafo {
protected:
    bool direcionado;
    // bool verticesPonderados;
    // bool arestasPonderadas;
    // int numVertices;

public:
    Grafo();
    virtual ~Grafo();
    //função força bruta que indica se o grafo é bipartido ou não
    virtual bool eh_bipartido() = 0;
    //- função que indica a quantidade de componentes conexas
    virtual int n_conexo() = 0;
    //- função que retorna o grau do grafo
    virtual int get_grau() = 0;
    //função que retorna a ordem do grafo
    virtual int get_ordem() = 0;
    //função que retorna se o grafo é direcionado ou não
    virtual bool eh_direcionado() = 0;
    //função que informa se os vertices do grafo tem peso
    virtual bool vertice_ponderado() = 0;
    //função que informa se as arestas do grafo tem peso
    virtual bool aresta_ponderada() = 0;
    //- função que diz se um grafo é completo ou não
    virtual bool eh_completo() = 0;
    //função que diz se o grafo é uma árvore
    virtual bool eh_arvore() = 0;
    //- função que diz se existe ao menos um vertice de articulação
    virtual bool possui_articulacao() = 0;
    //função que diz se existe ao menos uma aresta ponte
    virtual bool possui_ponte() = 0;
    //- função que lê um arquivo txt com um grafo e carrega ele
    virtual void carrega_grafo(string nomeArquivo) = 0;
    //- função que lê um arquivo txt de configuracao e gera um grafo aleatorio
    virtual void novo_grafo(string nomeArquivo) = 0;
};

#endif
