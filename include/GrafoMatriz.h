#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H
#include "Grafo.h"
#include "Aresta.h"

class Grafo;
class Vertice;

class GrafoLista : public Grafo {
public:
    /// 1ª Parte do Trabalho
    GrafoLista();
    ~GrafoLista() override;
    void setDirecao(bool dir) override;
    Vertice* getVertice(int id) override;
    Aresta* getAresta(int id_inicio, int id_fim) override;
    /// 2ª Parte do Trabalho
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;
    void imprimirVertices();
    void imprimirArestas();
private:
    Vertice* raizVertice;
    Aresta* raizAresta;
};

#endif //GRAFO_LISTA_H
