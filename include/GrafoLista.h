#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H
#include "Grafo.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

class Vertice;
class Grafo;

class GrafoLista : public Grafo {
public:
    /// 2ª Parte do Trabalho
    GrafoLista();
    ~GrafoLista() override;
    Vertice* getVertice(int id) override;
    Aresta* getAresta(int id_inicio, int id_fim) override;
    Aresta** getVizinhos(int id);
    /// 3ª Parte do Trabalho
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;
private:
    Vertice* raizVertice;
    Aresta* raizAresta;
    void imprimirVertices();
    void imprimirArestas();
};

#endif //GRAFO_LISTA_H
