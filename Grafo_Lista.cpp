#include "GrafoLista.h"
#include "Vertice.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool GrafoLista::vertice_ponderado() {
    ///verifica se o vertice possui peso
    Vertice *v = raizVertice;
    while (v != nullptr) {
        if (v->getPeso() != 1) {
            return true;
        }
        v = v->getProx();
    }
    return false;
}

int GrafoLista::get_grau() {
    ///informa o grau do grafo para grafosnão direcionados
    if (!eh_direcionado()) {
        Vertice *v = raizVertice;
        int grauGrafo =0;
        int grau = 0;
        while (v != nullptr) {
            cout<<v->getId()<<endl;
            cout<<v->totalArestas()<<endl;
            grau = v->totalArestas();
            if (grau > grauGrafo) {
                grauGrafo = grau;
            }
            v = v->getProx();
        }
        return grauGrafo;
    }
    else {
        Vertice *v = raizVertice;
        int grauGrafo = 0;
        while (v != nullptr) {
            int grauSaida = v->totalArestasSaida();     // Função para calcular grau de saída
            if (grauSaida > grauGrafo) {
                grauGrafo = grauSaida;
            }
            v = v->getProx();
        }
        return grauGrafo;

    }
}

bool GrafoLista::eh_completo() {
    ///verifica se todos os nos possuem mesmo grau
    int grau = 0, grauGrafo = 0, aux = 0;
    Vertice *v = raizVertice;
    ///para grafos não direcionados
    if (!eh_direcionado()) {
        while (v != nullptr) {
            aux++;
            grau = v->totalArestas();
            if (aux == 1)
                grauGrafo = grau;
            if (grau != grauGrafo) {
                return false;
            }
            v = v->getProx();
        }
        if (grauGrafo == get_ordem()-1)
            return true;
    }
    ///para grafos direcionados
    else {
        while (v != nullptr) {
            aux++;
            grau = v->totalArestasSaida();
            if (aux == 1)
                grauGrafo = grau;
            if (grau != grauGrafo) {
                return false;
            }
            v = v->getProx();
        }
        if (grauGrafo == get_ordem()-1)
            return true;
    }

    return false;
}

bool GrafoLista::eh_bipartido() {
    // Verifica se o grafo é completo; grafos completos não podem ser bipartidos
    if (eh_completo())
        return false;

    int num = get_ordem(); // Número de vértices
    int cont = pow(2, num); // Total de combinações possíveis
    int* binario = new int[num]; // Vetor para armazenar a combinação binária

    // Testa todas as combinações possíveis de particionamento
    for (int i = 1; i < cont; i++) {
        int valor = i;
        int aux = 0;

        // Converte o número para binário e armazena no vetor
        while (valor > 0) {
            binario[aux++] = valor % 2; // Armazena o resto da divisão por 2
            valor /= 2;
        }

        // Preenche os espaços vazios com 0
        while (aux < num) {
            binario[aux++] = 0;
        }

        // Variável para verificar se a combinação atual é bipartida
        bool ehBipartido = true;
        

        // Verifica a combinação binária atual
        for (int j = 0; j < num; j++) {
            Vertice* v1 = buscaVertice(j + 1); // Obtém o vértice

            for (int k = j + 1; k < num; k++) {
                // Verifica se os vértices estão no mesmo conjunto na partição atual
                if (binario[j] == binario[k]) {
                    Vertice* v2 = buscaVertice(k + 1);

                    // Verifica se os vértices são adjacentes
                    int tam = v1->totalArestas();
                    for (int l = 0; l < tam; l++) {
                        if (v1->getAresta(l)->getFim() == v2) {
                            // Aresta entre vértices do mesmo conjunto; não é bipartido
                            ehBipartido = false;
                            break;
                        }
                    }

                    if (!ehBipartido) {
                        break; // Sai do loop interno
                    }
                }
            }
            if (!ehBipartido) {
                break; // Sai do loop externo
            }
        }
        // Se encontramos uma partição válida, o grafo é bipartido
        if (ehBipartido) {
            delete[] binario;
            return true;
        }
    }
    // Nenhuma partição válida encontrada; o grafo não é bipartido
    delete[] binario;
    return false;
}

bool GrafoLista::possui_articulacao() {
    ///definição: se retira um vertice, aumenta o numero de componentes conexas;
    if (eh_completo()) ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = n_conexo();
    ///laco para realizar a remoção de um no por vez no grafo
    GrafoLista* grafo = copiarGrafo();
    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
        int tam = v->totalArestas();
        Aresta** arestas = v->copiarVetorArestas();
        ///retira um vertice
        grafo->removerVertice(grafo->buscaVertice(v->getId()));
        ///verifica se o numero de componentes aumentou
        int componentes = grafo->n_conexo();
        if (componentes > componentesConexas) {
            delete grafo;
            delete [] arestas;
            return true;
        }
        ///reinsere o vertice no grafo
        grafo->inserirVertice(v->getId(), v->getPeso());
        ///reinsere as arestas
        for (int i = 0; i < tam; i++)
            grafo->inserirAresta(grafo->buscaVertice(arestas[i]->getInicio()->getId()), grafo->buscaVertice(arestas[i]->getFim()->getId()), arestas[i]->getPeso());
        delete [] arestas;
    }
    delete grafo;
    return false;
}

bool GrafoLista::possui_ponte() {
    ///definição: se retira uma aresta, aumenta o numero de componentes conexas;
    ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
    if (eh_completo())
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = n_conexo();
    ///laco para realizar a remoção de um no por vez no grafo
    GrafoLista* grafo = copiarGrafo();

    for (Aresta* a = raizAresta; a != nullptr; a = a->getProx()) {
        int inicio = a->getInicio()->getId();
        int fim = a->getFim()->getId();
        int peso = a->getPeso();
        // Remove Aresta
        grafo->removerAresta(grafo->buscaAresta(inicio, fim));
        // Verifica se o numero de componentes aumentou
        int componentes = grafo->n_conexo();
        if (componentes > componentesConexas) {
            delete grafo;
            return true;
        }
        // Reinsere aresta no grafo
        grafo->inserirAresta(grafo->buscaVertice(inicio), grafo->buscaVertice(fim), peso);
    }

    delete grafo;
    return false;
}

void GrafoLista::removerVertice(Vertice* v) {
    /// Remover arestas do vetor de arestas do vértice
    for (int i = v->totalArestas()-1; i >= 0; i--) {
        removerAresta(v->getAresta(i));
    }

    /// Remover vértice da lista de vértices do Grafo
    if (raizVertice == v) {
        raizVertice = v->getProx();
    } else {
        Vertice* ant = raizVertice;
        while (ant->getProx() != v) {
            ant = ant->getProx();
        }
        ant->setProx(v->getProx());
    }
    delete v;
}

void GrafoLista::removerAresta(Aresta* a) {
    /// Remove aresta dos Vetores
    Vertice* v = a->getInicio();
    v->removerAresta(a);
    v = a->getFim();
    v->removerAresta(a);

    /// Remove aresta da lista de arestas do Grafo
    if (raizAresta == a) {
        raizAresta = a->getProx();
    } else {
        Aresta* ant = raizAresta;
        while (ant->getProx() != a) {
            ant = ant->getProx();
        }
        ant->setProx(a->getProx());
    }
    delete a;
}

Aresta* GrafoLista::buscaAresta(int id_inicio, int id_fim){
    Vertice* p = buscaVertice(id_inicio);
    return p->getArestaPara(buscaVertice(id_fim));
}

Vertice* GrafoLista::buscaVertice(int id){
    Vertice* p = raizVertice;
    while(p != nullptr){
        if( p->getId() == id)
            return p;
        p = p->getProx();
    }
    return p;
}

GrafoLista* GrafoLista::copiarGrafo() {
    GrafoLista* grafo = new GrafoLista();
    ///Copia os vertices do grafo;
    Vertice* v = raizVertice;
    while (v != nullptr) {
        grafo->inserirVertice(v->getId(), v->getPeso()); ///chama a função para inserir os vertices
        v = v->getProx(); ///atualiza para o proximo vertice
    }
    //imprimirVertices();
    ///Copia as arestas do grafo;
    Aresta* a = raizAresta;

    while (a != nullptr) {///insere cada aresta
        grafo->inserirAresta(grafo->buscaVertice(a->getInicio()->getId()), grafo->buscaVertice(a->getFim()->getId()), a->getPeso());
        a = a->getProx();
    }
    return grafo;
}
