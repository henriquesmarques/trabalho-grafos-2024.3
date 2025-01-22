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
public:
    /// 2ª Parte do Trabalho
    Grafo();
    virtual ~Grafo();
    bool eh_completo();
    bool eh_direcionado() const;
    bool vertice_ponderado() const;
    bool aresta_ponderada() const;
    int get_ordem() const;
    void carrega_grafo(string nomeArquivo);
    /// Funções das classes filhas
    virtual void inserirVertice(int id, float peso) = 0;
    virtual void inserirAresta(int id_inicio, int id_fim, float peso) = 0;
    virtual void removerVertice(int id) = 0;
    virtual void removerAresta(int id_inicio, int id_fim) = 0;
    virtual Vertice* getVertice(int id) = 0;
    virtual Aresta* getAresta(int id_inicio, int id_fim) = 0;
    // virtual Aresta** getVizinhos(int id) = 0;
    /// Comunicação com terminal
    virtual void salvaGrafo(string nomeArquivo) = 0;
    void imprimeGrafo(string nomeArquivo);
};

#endif
