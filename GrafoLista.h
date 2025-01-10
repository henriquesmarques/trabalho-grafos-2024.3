#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include <fstream>

#include "Grafo.h"
#include "Aresta.h"

class Vertice;

class GrafoLista : public Grafo {
public:
    // Henrique
    GrafoLista();
    ~GrafoLista();
    void carrega_grafo(std::string nomeArquivo) override; /// Função que lê um arquivo txt com um grafo e carrega ele
    void novo_grafo(std::string nomeArquivo) override; /// Função que lê um arquivo txt de configuração e gera um grafo aleatório
    bool aresta_ponderada() override; /// Função que informa se as arestas do grafo tem peso
    int get_ordem() override; /// Função que retorna a ordem do grafo
    bool eh_direcionado() override; /// Função que retorna se o grafo é direcionado ou não
    bool eh_arvore() override; /// Função que diz se o grafo é uma árvore
    int n_conexo() override; /// Função que indica a quantidade de componentes conexas
    // Karine
    bool eh_completo() override; /// Função que diz se o grafo é completo ou não
    int get_grau() override; /// Função que retorna o grau do grafo
    bool eh_bipartido() override; /// Função que diz se o grafo é bipartido ou não
    bool possui_articulacao() override; /// Função que diz se possui vertice de articulação
    bool possui_ponte() override; /// Função que diz se possui aresta ponte
    bool vertice_ponderado() override; /// Função que diz se o no possui peso
    // Gabriel
    void salvaGrafoLista(std::string nomeArquivo);
    void imprimeGrafo(std::string nomeArquivo);
private:
    // Henrique
    Vertice* raizVertice;
    Aresta* raizAresta;
    bool direcionado;
    void inserirVertice(int id, int peso);
    void inserirAresta(Vertice* inicio, Vertice* fim, int peso);
    void inserirPonteiroAresta(Aresta *a);
    void imprimirVertices();
    void imprimirArestas();
    bool ehCiclico();
    bool auxEhCiclico(Vertice* v, bool* visitados, Vertice* pai);
    void auxNConexo(bool *visitados, Vertice *v);
    int sortearVertice(int n);
    int sortearPeso(int n);
    Aresta* inserirArestaAleatoria(int ordem, int peso);
    void dividirVertices(Vertice **grupo1, Vertice **grupo2);
    // Karine
    Aresta* buscaAresta(int id, int peso);
    Vertice* buscaVertice(int id);
    GrafoLista* copiarGrafo();
    void removerVertice(Vertice* v);
    void removerAresta(Aresta* aresta);
};

#endif //GRAFO_LISTA_H
