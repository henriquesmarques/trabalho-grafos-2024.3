#include "../include/GrafoLista.h"
#include "../include/Vertice.h"
#include <iostream>

using namespace std;

GrafoLista::GrafoLista() {
    raizVertice = nullptr;
    raizAresta = nullptr;
    direcionado = false;
}

GrafoLista::~GrafoLista() {
    while (raizVertice != nullptr) {
        Vertice* p = raizVertice->getProx();
        delete raizVertice;
        raizVertice = p;
    }

    while (raizAresta != nullptr) {
        Aresta* a = raizAresta->getProx();
        delete raizAresta;
        raizAresta = a;
    }
}

Vertice* GrafoLista::getVertice(int id) {
    Vertice* v = raizVertice;
    while (v != nullptr) {
        if (v->getId() == id) {
            return v;
        }
        v = v->getProx();
    }
    return nullptr;
}

Aresta* GrafoLista::getAresta(int id_inicio, int id_fim) {
    Vertice* v = getVertice(id_inicio);
    if (v == nullptr)
        return nullptr;
    for (int i = 0; i < v->getTotalVizinhos(); i++) {
        if (v->getVizinho(i)->getFim()->getId() == id_fim) {
            return v->getVizinho(i);
        }
    }
    return nullptr;
}

Aresta ** GrafoLista::getVizinhos(int id) {
    Vertice* v = getVertice(id);
    if (v != nullptr) {
        return v->getVetorVizinhos();
    }
    cout << "Erro: indice invalido no getVizinhos()." << endl;
    exit(1);
}

void GrafoLista::setDirecao(bool dir) {
    direcionado = dir;
}

void GrafoLista::inserirVertice(int id, float peso) {
    if (getVertice(id) == nullptr) {
        auto* v = new Vertice(id, peso);
        if (raizVertice != nullptr) {
            v->setProx(raizVertice);
        }
        raizVertice = v;
        ordem++;
    } else {
        cout << "Erro: existe um vertice com o mesmo indice." << endl;
    }
}

void GrafoLista::inserirAresta(int id_inicio, int id_fim, float peso) {
    if (id_inicio == id_fim) {
        cout << "Erro: não e possivel inserir laco." << endl;
    } else if (getAresta(id_inicio, id_fim) != nullptr) {
        cout << "Erro: não e possivel inserir aresta multipla." << endl;
    } else {
        Vertice* inicio = getVertice(id_inicio);
        Vertice* fim = getVertice(id_fim);
        if (inicio == nullptr || fim == nullptr) {
            cout << "Erro: o vertice nao foi encontrado." << endl;
        } else {
            // Criando aresta
            auto* a = new Aresta(inicio, fim, peso);

            // Adiciona aresta no vetor de vizinhos do vértice
            inicio->inserirVizinho(a);
            fim->inserirVizinho(a);

            // Adicionando aresta na lista de arestas
            if (raizAresta != nullptr) {
                a->setProx(raizAresta);
            }
            raizAresta = a;
        }
    }
}

void GrafoLista::removerVertice(int id) {
    imprimirArestas();
    Vertice *v = getVertice(id);
    if (v==nullptr) {
        cout<<"Erro: vertice nao encontrado."<<endl;
    }
    else {
        /// Remover arestas do vetor de arestas do vértice
        while (v->getTotalVizinhos() > 0) {
            Aresta *a = v->getVizinho(0);
            removerAresta(a->getInicio()->getId(), a->getFim()->getId());
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
        ordem--;
        for (int i=id; i<=ordem; i++) {
            getVertice(i+1)->setId(i);
        }
    }
}

void GrafoLista::removerAresta(int id_inicio, int id_fim) {
    Aresta *a = getAresta(id_inicio, id_fim);
    if (a == nullptr) {
        cout << "Erro: aresta nao encontrada." << endl;
    }
    else {
        /// Remove aresta dos Vetores
        Vertice* v = a->getInicio();
        v->removerVizinho(a);
        v = a->getFim();
        v->removerVizinho(a);
        cout<<"nada2"<<endl;
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
}

void GrafoLista::imprimirVertices() {
    cout << "Lista de vertices: " << endl;
    Vertice* v = raizVertice;
    while (v != nullptr) {
        cout << v->getId() << " ";
        v = v->getProx();
    }
    cout << endl;
}

void GrafoLista::imprimirArestas() {
    cout << "Lista de arestas: " << endl;
    Aresta* a = raizAresta;
    while (a != nullptr) {
        cout << a->getInicio()->getId() << " -> " << a->getFim()->getId() << " Peso: " << a->getPeso() << endl;
        a = a->getProx();
    }
}