#include <iostream>
#include "Vertice.h"

using namespace std;

Vertice::Vertice(int _id) {
    id = _id;
    peso = 1;
    prox = nullptr;
    arestas = nullptr;
    n = 0;
    tam = 10;
    arestas = new Aresta*[tam];
}


Vertice::~Vertice() {
    delete [] arestas;
}

void Vertice::setPeso(int val) {
    peso = val;
}

int Vertice::getPeso() {
    return peso;
}

void Vertice::setProx(Vertice *v) {
    prox = v;
}

Vertice * Vertice::getProx() {
    return prox;
}

int Vertice::getId() {
    return id;
}

Aresta* Vertice::getAresta(int i) {
    if (i >= 0 && i < n) {
        return arestas[i];
    }
    else {
        cout << "Erro get: indice invalido." << endl;
        exit(1);
    }
}

Aresta ** Vertice::getVetorArestas() {
    return arestas;
}

void Vertice::inserirAresta(Aresta *a) {
    if (n >= tam) {
        aumentarVetor();
    }
    arestas[n] = a;
    n++;
}

void Vertice::aumentarVetor() {
    Aresta **a = new Aresta*[tam+10];
    for (int i = 0; i < tam; i++) {
        a[i] = arestas[i];
    }
    delete [] arestas;
    arestas = a;
    tam += 10;
}

int Vertice::totalArestas() {
    return n;
}

void Vertice::removerAresta(Aresta* a)
{
    // Encontrar posição da aresta no vetor
    int i = 0;
    for (i = 0; i < n; i++) {
        if (arestas[i] == a) {
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
        arestas[j] = arestas[j+1];
    }
    n--;

    //cout << "Aresta removida." << endl;
}

Aresta** Vertice::copiarVetorArestas() {
    Aresta** a = new Aresta*[n];
    for (int i = 0; i < n; i++) {
        a[i] = getAresta(i);
    }
    return a;
}

Aresta* Vertice::getArestaPara(Vertice* destino) {
    for (int i = 0; i < totalArestas(); ++i) {
        Aresta* a = getAresta(i);
        if (a->getFim() == destino) {
            return a;
        }
    }
    return nullptr; // Retorna nullptr se nenhuma aresta conectar os dois vértices
}

int Vertice::totalArestasSaida() {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (arestas[i]->getInicio() == this) {
            total++;
        }
    }
    return total;
}
