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
    // Henrique
    // void carrega_grafo(string nomeArquivo) override; /// Função que lê um arquivo txt com um grafo e carrega ele
    void novo_grafo(string nomeArquivo) override; /// Função que lê um arquivo txt de configuração e gera um grafo aleatório
    bool aresta_ponderada() override; /// Função que informa se as arestas do grafo tem peso
    int get_ordem() override; /// Função que retorna a ordem do grafo
    bool eh_direcionado() override; /// Função que retorna se o grafo é direcionado ou não
    bool eh_arvore() override; /// Função que diz se o grafo é uma árvore
    // int n_conexo() override; /// Função que indica a quantidade de componentes conexas
    // Karine
    // bool eh_completo() override; /// Função que diz se o grafo é completo ou não
    int get_grau() override; /// Função que retorna o grau do grafo
    bool eh_bipartido() override; /// Função que diz se o grafo é bipartido ou não
    bool possui_articulacao() override; /// Função que diz se possui vertice de articulação
    bool possui_ponte() override; /// Função que diz se possui aresta ponte
    bool vertice_ponderado() override; /// Função que diz se o no possui peso

    void salvaGrafo(string nomeArquivo) override; // Metodo de comunicação com terminal
    // void imprimeGrafo(string nomeArquivo) override;

    /// 2ª Parte do Trabalho
    GrafoLista();
    ~GrafoLista() override;
    void inserirVertice(int id, float peso) override;
    void inserirAresta(int id_inicio, int id_fim, float peso) override;
    void removerVertice(int id) override;
    void removerAresta(int id_inicio, int id_fim) override;
    Vertice* getVertice(int id);
    Aresta* getAresta(int id_inicio, int id_fim);
    Aresta** getVizinhos(int id);

private:
    Vertice* raizVertice;
    Aresta* raizAresta;
    void imprimirVertices();
    void imprimirArestas();
    bool ehCiclico();
    bool auxEhCiclico(Vertice* v, bool* visitados, Vertice* pai);
    void auxNConexo(bool *visitados, Vertice *v);
    int sortearVertice(int n);
    int sortearPeso(int n);
    Aresta* inserirArestaAleatoria(int ordem, float peso);
    void dividirVertices(int* grupo1, int* grupo2, int ordem);
    GrafoLista* copiarGrafo();
};

#endif //GRAFO_LISTA_H
