#include "../include/Grafo.h"
#include <fstream>
#include <iostream>

using namespace std;

Grafo::Grafo() {
    direcionado = false;
    verticesPonderados = false;
    arestasPonderadas = false;
    ordem = 0;
}

Grafo::~Grafo() = default;

void Grafo::carrega_grafo(string nomeArquivo) {
    ifstream arquivo;
    arquivo.open("entradas/"+nomeArquivo, ios::in);
    //arquivo.open("entradas/Grafo.txt", ios::out);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int numVertices, direcionado, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcionado >> ponderado_nos >> ponderado_arestas;

    this->direcionado = direcionado;
    this->verticesPonderados = ponderado_nos;
    this->arestasPonderadas = ponderado_arestas;

    // Criar vértices
    if (ponderado_nos == 1) {
        float peso;
        for (int i = 0; i < numVertices; i++) {
            arquivo >> peso;
            inserirVertice(i+1, peso);
        }
    } else {
        for (int i = 0; i < numVertices; ++i) {
            inserirVertice(i+1, 1);
        }
    }

    // Criar arestas
    int origem, destino;
    float peso;
    while (arquivo >> origem >> destino) {
        if (ponderado_arestas == 1) {
            arquivo >> peso;
            inserirAresta(origem, destino, peso);
        } else {
            inserirAresta(origem, destino, 1);
        }
    }

    arquivo.close();
}

void Grafo::imprimeGrafo(string nomeArquivo) {
    cout<<nomeArquivo<<"\n";

    cout << "Grau: " << get_grau() << endl;

    cout<<"Ordem: "<<get_ordem()<<"\n";

    if(eh_direcionado())
    {cout<<"Direcionado: "<<"Sim"<<"\n";}
    else{cout<<"Direcionado: "<<"Nao"<<"\n";}

    //cout<<"Componentes conexas: "<<n_conexo()<<"\n";

    if(vertice_ponderado())
    {cout<<"Vertices ponderados: "<<"Sim"<<"\n";}
    else{cout<<"Vertices ponderados: "<<"Nao"<<"\n";}

    if(aresta_ponderada())
    {cout<<"Arestas ponderadas: "<<"Sim"<<"\n";}
    else{cout<<"Arestas ponderadas: "<<"Nao"<<"\n";}

    if(eh_completo())
    {cout<<"Completo: "<<"Sim"<<"\n";}
    else{cout<<"Completo: "<<"Nao"<<"\n";}
}

bool Grafo::eh_completo() {
    if (get_ordem() == 0)
        return false;
    ///verifica se todos os nos possuem mesmo grau
    int grau = 0, grauGrafo = 0, aux = 0;
    for (int i = 1; i <= get_ordem(); i++) {
        aux++;
        grau = eh_direcionado() ? getVertice(i)->totalArestasSaida() : getVertice(i)->getTotalVizinhos();
        if (aux == 1)
            grauGrafo = grau;
        if (grau != grauGrafo) {
            return false;
        }
    }
    if (grauGrafo == get_ordem()-1)
        return true;
    return false;
}

bool Grafo::eh_direcionado() const {
    return direcionado;
}

bool Grafo::vertice_ponderado() const {
    return verticesPonderados;
}

bool Grafo::aresta_ponderada() const {
    return arestasPonderadas;
}

int Grafo::get_ordem() const {
    return ordem;
}

int Grafo::n_conexo() {
    int numVertices = get_ordem();
    if (numVertices == 0) return 0;

    bool *visitados = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitados[i] = false;
    }

    int componentesConexas = 0;
    for (int i = 1; i <= get_ordem(); i++) {
        if (!visitados[getVertice(i)->getId() - 1]) {
            auxNConexo(visitados, getVertice(i));
            componentesConexas++;
        }
    }

    delete[] visitados;
    return componentesConexas;
}

void Grafo::auxNConexo(bool *visitados, Vertice *v) {
    visitados[v->getId() - 1] = true;
    for (int i = 0; i < v->getTotalVizinhos(); ++i) {
        Aresta* a = v->getVizinho(i);
        Vertice* adj = a->getFim();
        if (!visitados[adj->getId() - 1]) {
            auxNConexo(visitados, adj);
        }
        adj = a->getInicio();
        if (!visitados[adj->getId() - 1]) {
            auxNConexo(visitados, adj);
        }
    }
}

int Grafo::get_grau() {
    return 0;
}
