#include "../include/Vertice.h"
#include <iostream>

using namespace std;

Vertice::Vertice(int _id) {
    id = _id;
    peso = 1;
    prox = nullptr;
    n = 0;
    tam = 10;
    vizinhos = new Aresta*[tam];
}

Vertice::Vertice(int _id, float _peso) {
    id = _id;
    peso = _peso;
    prox = nullptr;
    n = 0;
    tam = 10;
    vizinhos = new Aresta*[tam];
}

Vertice::~Vertice() {
    delete [] vizinhos;
}

void Vertice::setPeso(float val) {
    peso = val;
}

float Vertice::getPeso() {
    return peso;
}

void Vertice::setProx(Vertice *v) {
    prox = v;
}

Vertice * Vertice::getProx() {
    return prox;
}

void Vertice::setId(int id) {
    this->id = id;
}
int Vertice::getId() {
    return id;
}

Aresta* Vertice::getVizinho(int id) {
    if (id >= 0 && id < n) {
        return vizinhos[id];
    }
    cout << "Erro get: indice invalido." << endl;
    exit(1);
}

Aresta ** Vertice::getVetorVizinhos() {
    return vizinhos;
}

void Vertice::inserirVizinho(Aresta *a) {
    if (n >= tam) {
        aumentarVetor();
    }
    vizinhos[n] = a;
    n++;
}

void Vertice::aumentarVetor() {
    Aresta **a = new Aresta*[tam+10];
    for (int i = 0; i < tam; i++) {
        a[i] = vizinhos[i];
    }
    delete [] vizinhos;
    vizinhos = a;
    tam += 10;
}

int Vertice::getTotalVizinhos() {
    return n;
}

void Vertice::removerVizinho(Aresta* a)
{
    // Encontrar posição da aresta no vetor
    int i = 0;
    for (i = 0; i < n; i++) {
        if (vizinhos[i] == a) {
            break;
        }
    }
    // Verificar se a aresta foi encontrada
    if (i == n) {
        cout << "Erro: Aresta nao encontrada." << endl;
        exit(1);
    }

    // Reorganizando vetor
    for (int j = i; j < n-1; j++) {
        vizinhos[j] = vizinhos[j+1];
    }
    n--;

    //cout << "Aresta removida." << endl;
}

Aresta** Vertice::copiarVetorArestas() {
    Aresta** a = new Aresta*[n];
    for (int i = 0; i < n; i++) {
        a[i] = getVizinho(i);
    }
    return a;
}

Aresta* Vertice::getArestaPara(Vertice* destino) {
    for (int i = 0; i < getTotalVizinhos(); ++i) {
        Aresta* a = getVizinho(i);
        if (a->getFim() == destino) {
            return a;
        }
    }
    return nullptr; // Retorna nullptr se nenhuma aresta conectar os dois vértices
}

int Vertice::totalArestasSaida() {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (vizinhos[i]->getInicio() == this) {
            total++;
        }
    }
    return total;
}
