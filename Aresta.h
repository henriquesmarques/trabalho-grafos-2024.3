#ifndef ARESTA_H
#define ARESTA_H
#include "Vertice.h"

class Vertice;

class Aresta {
public:
    Aresta();
    Aresta(Vertice* _inicio, Vertice* _fim, float _peso);
    ~Aresta();
    void setPeso(float val);
    float getPeso();
    void setInicio(Vertice* v);
    Vertice* getInicio();
    void setFim(Vertice* v);
    Vertice* getFim();
    void setProx(Aresta* a);
    Aresta* getProx();
private:
    float peso;
    Vertice* inicio;
    Vertice* fim;
    Aresta* prox;
};

#endif //ARESTA_H
