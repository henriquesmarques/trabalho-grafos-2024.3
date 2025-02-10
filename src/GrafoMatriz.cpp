#include "../include/GrafoMatriz.h"

GrafoMatriz::GrafoMatriz() {
    MAX_VERTICES = 10;
    MAX_ARESTAS = (MAX_VERTICES+1)*MAX_VERTICES/2;
    // Alocando matriz de arestas
    arestas = new Aresta*[MAX_ARESTAS];
    // Alocando vetor de vértices
    vertices = new Vertice*[MAX_VERTICES];
    // Inicializando vetor de vértices e matriz de arestas
    for (int i = 0; i < MAX_ARESTAS; i++) {
        if (i < MAX_VERTICES) {
            vertices[i] = nullptr;
        }
        arestas[i] = nullptr;
    }
}

GrafoMatriz::GrafoMatriz(bool dir) {
    MAX_VERTICES = 10;
    if (!dir) {
        MAX_ARESTAS = (MAX_VERTICES+1)*MAX_VERTICES/2;
    } else {
        MAX_ARESTAS = MAX_VERTICES*MAX_VERTICES;
    }
    // Alocando matriz de arestas
    arestas = new Aresta*[MAX_ARESTAS];
    // Alocando vetor de vértices
    vertices = new Vertice*[MAX_VERTICES];
    // Inicializando vetor de vértices e matriz de arestas
    for (int i = 0; i < MAX_ARESTAS; i++) {
        if (i < MAX_VERTICES) {
            vertices[i] = nullptr;
        }
        arestas[i] = nullptr;
    }
    // Atualizando variáveis
    direcionado = dir;
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < MAX_ARESTAS; i++) {
        if (arestas[i] != nullptr) {
            delete arestas[i];
        }
    }
    delete [] arestas;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (vertices[i] != nullptr) {
            delete vertices[i];
        }
    }
    delete [] vertices;
}

void GrafoMatriz::setDirecao(bool dir) {
    direcionado = dir;
    // Alterando tamanho da matriz
    if (direcionado) {
        MAX_ARESTAS = MAX_VERTICES*MAX_VERTICES;
        auto** novaMatriz = new Aresta*[MAX_ARESTAS];
        for (int i = 0; i < MAX_ARESTAS; i++) {
            novaMatriz[i] = nullptr;
        }
        delete [] arestas;
        arestas = novaMatriz;
    }
}

void GrafoMatriz::aumentarMatriz() {
    MAX_VERTICES = MAX_VERTICES*2;
    int total_arestas = MAX_ARESTAS;
    if (!direcionado) {
        MAX_ARESTAS = (MAX_VERTICES+1)*MAX_VERTICES/2;
    } else {
        MAX_ARESTAS = MAX_VERTICES*MAX_VERTICES;
    }
    // Alocando uma nova matriz com o dobro de tamanho
    auto** novaMatriz = new Aresta*[MAX_ARESTAS];
    // Inicializando nova matriz
    for (int i = 0; i < MAX_ARESTAS; i ++) {
        novaMatriz[i] = nullptr;
    }
    // Copiando valores da antiga
    if (!direcionado) {
        for (int i = 0; i < total_arestas; i++) {
            for (int j = i; j < total_arestas; j++) {
                novaMatriz[detIndice(i,j)] = arestas[(j+1)*j/2+i];
            }
        }
    } else {
        for (int i = 0; i < total_arestas; i++) {
            for (int j = 0; j < total_arestas; j++) {
                novaMatriz[detIndice(i,j)] = arestas[MAX_VERTICES/2*i+j]; // nc * i +j
            }
        }
    }
    // Alocando novo vetor de vértices
    auto** novosVertices = new Vertice* [MAX_VERTICES];
    // Inicializando novo vetor de pesos de vértices e copiando valores do antigo
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (i < MAX_VERTICES/2) {
            novosVertices[i] = vertices[i];
        } else {
            novosVertices[i] = nullptr;
        }
    }
    // Desalocando memória
    delete [] arestas;
    delete [] vertices;
    // Atualizando variáveis
    arestas = novaMatriz;
    vertices = novosVertices;
}

int GrafoMatriz::detIndice(int i, int j) {
    if (!direcionado) {
        if (i <= j && i >= 0 && j < MAX_VERTICES) {
            return (j+1)*j/2+i; // caso especifico para matriz triangular superior
        }
    } else {
        if (i >= 0 && i < MAX_VERTICES && j >= 0 && j < MAX_VERTICES) {
            return MAX_VERTICES * i + j;
        }
    }
    return -1;
}

Vertice* GrafoMatriz::getVertice(int id) {
    if (verificaIndice(id)) {
        return vertices[id-1];
    }
    cout << "Erro: indice invalido." << endl;
    exit(1);
}

Aresta* GrafoMatriz::getAresta(int id_inicio, int id_fim) {
    if (verificaIndice(id_inicio) && verificaIndice(id_fim)) {
        if (!direcionado && id_inicio > id_fim) {
            int aux = id_inicio;
            id_inicio = id_fim;
            id_fim = aux;
        }
        int k = detIndice(id_inicio-1, id_fim-1);
        if (k == -1) {
            cout << "Erro: indice invalido" << endl;
            exit(-1);
        }
        return arestas[k];
    }
    cout << "Erro: indice invalido." << endl;
    exit(1);
}

void GrafoMatriz::inserirVertice(int id, float peso) {
    if (verificaIndice(id)) {
        if (ordem + 1 > MAX_VERTICES) {
            aumentarMatriz();
        }
        if (getVertice(id) == nullptr) {
            auto* v = new Vertice(id, peso);
            vertices[id-1] = v;
            ordem++;
        } else {
            cout << "Erro: existe um vertice com o mesmo indice." << endl;
        }
    } else {
        cout << "Erro: indice invalido." << endl;
    }
}

void GrafoMatriz::inserirAresta(int id_inicio, int id_fim, float peso) {
    if (verificaIndice(id_inicio) && verificaIndice(id_fim)) {
        if (id_inicio == id_fim) {
            cout << "Erro: nao e possivel inserir laco." << endl;
        } else if (getAresta(id_inicio, id_fim) != nullptr) {
            cout << "Erro: nao e possivel inserir aresta multipla." << endl;
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
                int k = detIndice(id_inicio-1, id_fim-1);
                arestas[k] = a;
            }
        }
    } else {
        cout << "Erro: indice invalido." << endl;
    }
}

void GrafoMatriz::removerVertice(int id) {
    Vertice *v = getVertice(id);
    if (v == nullptr) {
        cout << "Erro: o vertice nao foi encontrado." << endl;
    } else {
        // Remover arestas do vetor de arestas do vértice
        for (int i = v->getTotalVizinhos()-1; i >= 0; i--) {
            removerAresta(v->getVizinho(i)->getInicio()->getId(), v->getVizinho(i)->getFim()->getId());
        }

        // Removendo vértice e organizando o vetor
        for(int i = id-1; i < MAX_VERTICES-1; i++) {
            vertices[i] = vertices[i+1];
            if (vertices[i] != nullptr) {
                vertices[i]->setId(i+1);
            }
        }
        //imprimirArestas();
        // Organizando matriz de arestas
        if (direcionado) {
            for(int i = id-1; i < MAX_VERTICES-1; i++) {;
                for(int j = id-1; j < MAX_VERTICES-1; j++) {
                    arestas[detIndice(i,j)] = arestas[detIndice(i+1, j+1)];
                }
            }
        } else {
            for(int i = id-1; i < MAX_VERTICES-1; i++) {;
                for(int j = i; j < MAX_VERTICES-1; j++) {
                    arestas[detIndice(i,j)] = arestas[detIndice(i+1, j+1)];
                }
            }
        }
        //imprimirArestas();

        ordem--;
        delete v;
        cout << "Excluindo no " << id << "..." << endl;
    }
}


void GrafoMatriz::removerAresta(int id_inicio, int id_fim) {
    if (verificaIndice(id_inicio) && verificaIndice(id_fim)) {
        Aresta *a = getAresta(id_inicio, id_fim);
        if (a == nullptr) {
            cout << "Erro: aresta nao encontrada." << endl;
        }
        else {
            cout << "Removendo aresta: " << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
            /// Remove aresta dos Vetores
            Vertice* v = a->getInicio();
            v->removerVizinho(a);
            v = a->getFim();
            v->removerVizinho(a);

            /// Remove aresta da matriz
            arestas[detIndice(id_inicio-1, id_fim-1)] = nullptr;

            delete a;
        }
    } else {
        cout << "Erro: indice invalido." << endl;
    }
}

bool GrafoMatriz::verificaIndice(int id) {
    if (id > 0 && id <= MAX_VERTICES) {
        return true;
    }
    return false;
}

void GrafoMatriz::imprimirArestas() {
    if (direcionado) {
        for (int i = 1; i <= MAX_VERTICES; i++) {
            for (int j = 1; j <= MAX_VERTICES; j++) {
                Aresta* a = getAresta(i,j);
                if (a != nullptr) {
                    // cout << "(" << i << ", " << j << ") ";
                    // cout << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
                    cout << a->getPeso() << " ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
        cout << endl;
    } else {
        for (int i = 1; i <= MAX_VERTICES; i++) {
            for (int j = i; j <= MAX_VERTICES; j++) {
                Aresta* a = getAresta(i,j);
                if (a != nullptr) {
                    // cout << "(" << i << ", " << j << ") ";
                    // cout << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
                    cout << a->getPeso() << " ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
}

void GrafoMatriz::imprimirVertices() {
    for (int i = 1; i <= MAX_VERTICES; i++) {
        Vertice* v = getVertice(i);
        if (v != nullptr) {
            cout << v->getId() << " ";
        } else {
            cout << "0 ";
        }
    }
    cout << endl;
}