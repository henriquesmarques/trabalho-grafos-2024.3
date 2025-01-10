#ifndef ARESTA_H
#define ARESTA_H
#include "Vertice.h"

class Vertice;

class Aresta {
public:
    Aresta();
    Aresta(Vertice* _inicio, Vertice* _fim, int _peso);
    ~Aresta();
    void setPeso(int val);
    int getPeso();
    void setInicio(Vertice* v);
    Vertice* getInicio();
    void setFim(Vertice* v);
    Vertice* getFim();
    void setProx(Aresta* a);
    Aresta* getProx();
private:
    int peso;
    Vertice* inicio;
    Vertice* fim;
    Aresta* prox;
};

#endif //ARESTA_H
