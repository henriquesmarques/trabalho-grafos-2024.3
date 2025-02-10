#include "../include/Aresta.h"
#include <iostream>

using namespace std;

Aresta::Aresta() {
    peso = 1;
    fim = nullptr;
    inicio = nullptr;
    prox = nullptr;
    visitado = false;
}

Aresta::Aresta(Vertice *_inicio, Vertice *_fim, float _peso) {
    peso = _peso;
    fim = _fim;
    inicio = _inicio;
    prox = nullptr;
    visitado = false;
}

Aresta::~Aresta() {
}

void Aresta::setPeso(float val) {
    peso = val;
}

float Aresta::getPeso() {
    return peso;
}

void Aresta::setInicio(Vertice *v) {
    inicio = v;
}

Vertice * Aresta::getInicio() {
    return inicio;
}

void Aresta::setFim(Vertice *v) {
    fim = v;
}

Vertice * Aresta::getFim() {
    return fim;
}

void Aresta::setProx(Aresta *a) {
    prox = a;
}

Aresta* Aresta::getProx() {
    return prox;
}

void Aresta::setVisitado(bool v) {
    visitado = v;
}

bool Aresta::getVisitado() {
    return visitado;
}
