#include "../include/Grafo.h"
#include <fstream>
#include <iostream>
#include <cmath>

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

    int numVertices, direcao, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcao >> ponderado_nos >> ponderado_arestas;

    setDirecao(direcao);
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

void Grafo::caminhoMinino(int id_inicio, int id_fim) {
    Vertice* inicio = getVertice(id_inicio);
    Vertice* fim = getVertice(id_fim);
    ///Verifica se os vertices existem
    if (inicio == nullptr || fim == nullptr)
        cout << "Erro: Vertices nao encontrados." << endl;

    else {
        ///Verifica se as arestas possuem peso e verifica se tem algum peso negativo
        float neg = 0;
        if (aresta_ponderada()) {
            ///verifica se existe algum peso negativo
            for(int i = 1; i <= get_ordem(); i++) {
                Vertice *v = getVertice(i);
                Aresta **a = v->getVetorVizinhos();
                for (int j = 0; j < v->getTotalVizinhos(); j++) {
                    if (a[j]->getPeso() < neg)
                        neg = a[j]->getPeso();
                }
            }
            ///passa o valor absoluto do menor peso negativo para a variavel neg
            neg = abs(neg)+1;
            ///caso exista peso negativo, é adicionado o valor absoluto do menor peso negativo
            if (neg > 1) {
                for(int i = 1; i <= get_ordem(); i++) {
                    Vertice *v = getVertice(i);
                    Aresta **a = v->getVetorVizinhos();
                    for (int j = 0; j < v->getTotalVizinhos(); j++){
                        ///se a aresta ainda não foi visitada, é adicionado o valor absoluto do menor peso negativo
                        if(!a[j]->getVisitado()){
                            a[j]->setPeso(a[j]->getPeso() + neg);
                            a[j]->setVisitado(true);
                        }
                    }
                }
            }
        }
        cout<<"neg: "<<neg<<endl;;
        // Inicialização de variáveis
        float max = 100;
        float dist[ordem];
        bool visitados[ordem];
        for (int i = 0; i < ordem; i++) {
            dist[i] = max;
            visitados[i] = false;
        }
        dist[id_inicio-1] = 0;
        ///caso para grafos direcionados
        if (eh_direcionado()) {
            for (int count = 0; count < ordem - 1; count++) {
                int u = minDistance(dist, visitados);
                visitados[u] = true;
                for (int v = 0; v < ordem; v++) {
                    if (!visitados[v] && getAresta(u+1,v+1) != nullptr
                    && dist[u] != max && dist[u] + getAresta(u+1,v+1)->getPeso() < dist[v])
                        dist[v] = dist[u] + getAresta(u+1,v+1)->getPeso();
                }
            }
        }
        ///caso para grafos não direcionados
        else {
            for (int m = 0; m < ordem - 1; m++) {
                int u = minDistance(dist, visitados);
                visitados[u] = true;
                for (int v = 0; v < ordem; v++) {
                    if ((!visitados[v] && getAresta(u+1,v+1) != nullptr
                    && dist[u] != max && dist[u] + getAresta(u+1,v+1)->getPeso() < dist[v]) ||(
                    !visitados[u] && getAresta(v+1,u+1) != nullptr && dist[v] != max && dist[v] + getAresta(v+1,u+1)->getPeso()<dist[u])) {
                        dist[v] = dist[u] + getAresta(u+1,v+1)->getPeso();
                    }
                }
            }
        }

        // Impressão
        if (dist[id_fim-1] == 100)
            cout<<"Nao existe caminho entre os vertices."<<endl;
        else
            cout << "Maior menor distancia:(" << id_inicio << "-" << id_fim << ") " << dist[id_fim-1] << endl;

        ///restaurar pesos
        if (aresta_ponderada()) {
            for(int i = 1; i <= get_ordem(); i++) {
                Vertice *v = getVertice(i);
                Aresta **a = v->getVetorVizinhos();
                for (int j = 0; j < v->getTotalVizinhos(); j++){
                    ///se a aresta ainda não foi visitada, é adicionado o valor absoluto do menor peso negativo
                    if(a[j]->getVisitado()){
                        a[j]->setPeso(a[j]->getPeso() - neg);
                        a[j]->setVisitado(false);
                    }
                }
            }
        }
    }
}

int Grafo::minDistance(float dist[], bool visitados[]) {
        float min = 100;
        int min_index = 0;

        for (int i = 0; i < ordem; i++) {
            if (visitados[i] == false && dist[i] <= min) {
                min = dist[i];
                min_index = i;
            }
        }
        return min_index;
}
