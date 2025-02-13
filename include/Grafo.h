#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include "Aresta.h"
#include "Vertice.h"

using namespace std;

class Grafo {
protected:
    bool direcionado;
    bool verticesPonderados;
    bool arestasPonderadas;
    int ordem;
    void auxNConexo(bool *visitados, Vertice *v);
    //2ª Parte do Trabalho
    int minDistance(float dist[], bool visitados[]);
public:
    Grafo();
    virtual ~Grafo();
    /// 1ª Parte do Trabalho
    int n_conexo();
    int get_grau();
    int get_ordem() const;
    bool eh_direcionado() const;
    bool vertice_ponderado() const;
    bool aresta_ponderada() const;
    bool eh_completo();
    void carrega_grafo(string nomeArquivo);
    /// Impressão do Grafo
    void imprimeGrafo();
    /// Funções das classes filhas
    virtual void inserirVertice(int id, float peso) = 0;
    virtual void inserirAresta(int id_inicio, int id_fim, float peso) = 0;
    virtual void removerVertice(int id) = 0;
    virtual void removerAresta(int id_inicio, int id_fim) = 0;
    virtual Vertice* getVertice(int id) = 0;
    virtual Aresta* getAresta(int id_inicio, int id_fim) = 0;
    virtual void setDirecao(bool dir) = 0;
    /// 2ª Parte do Trabalho
    void caminhoMinino();
};

#endif
