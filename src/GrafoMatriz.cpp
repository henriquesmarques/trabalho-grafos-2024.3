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
    delete [] arestas;
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
            return; // caso especifico para matriz triangular superior
        }
    } else {
        if (i >= 0 && i < MAX_VERTICES && j >= 0 && j < MAX_VERTICES) {
            return MAX_VERTICES * i + j;
        }
    }
    return -1;
}

Vertice* GrafoMatriz::getVertice(int id) {
    return vertices[id-1];
}

Aresta* GrafoMatriz::getAresta(int id_inicio, int id_fim) {
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

void GrafoMatriz::inserirVertice(int id, float peso) {
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
}

void GrafoMatriz::inserirAresta(int id_inicio, int id_fim, float peso) {
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
}
/*void GrafoMatriz::removerVertice(int id){
    //imprimirArestas();
    Vertice *v = getVertice(id);
    if (v==nullptr) {
        cout<<"Erro: vertice nao encontrado."<<endl;
    }
    else {
        /// Remover arestas do vetor de arestas
        while (v->getTotalVizinhos() > 0) {
            Aresta *a = v->getVizinho(0);
            int inicio = a->getInicio()->getId();
            int fim = a->getFim()->getId();
            arestas[(inicio,fim)] = nullptr; //
            v->removerVizinho(a);
        }
        //deslocando a matriz para remover o vertice
        /*for (int i = id; i < ordem; i++) {
            for (int j = 0; j < ordem; j++) {
                arestas[detIndice(i, j)] = arestas[detIndice(i + 1, j)]; // Mover linha para cima
            }
        }
        for (int j = id; j < ordem; j++) {
            for (int i = 0; i < ordem; i++) {
                arestas[detIndice(i, j)] = arestas[detIndice(i, j + 1)]; // Mover coluna para a esquerda
            }
        }*/
        
        
        //removendo o vertice do vetor de vertice
        /*for(int i=id; i< ordem; i++){
            vertices[i] = vertices[i+1];
            getVertice(i+1)->setId(i);
        }
        delete v;
        ordem --;
    }
}*/
void GrafoMatriz::removerVertice(int id) {
    cout << "Antes da Remover Vertice: " << endl
    for(int i =0; i<numVertices; i++){
            cout << "Vertices " << vertices[i];
        }
    cout << endl;
    for(int i=0; i<MAX_ARESTAS ; i++){
        cout << "Arestas " << arestas[i];
    }
    Vertice *v = getVertice(id);
    if (v == nullptr) {
        cout << "Erro: o vertice nao foi encontrado." << endl;
    } else {
        // Remover arestas do vetor de arestas do vértice
        for (int i = v->getTotalVizinhos()-1; i >= 0; i--) {
            removerAresta(v->getVizinho(i)->getInicio()->getId(), v->getVizinho(i)->getFim()->getId());
        }

        // Remover vértice da lista de vértices do Grafo
        vertices[id-1] = nullptr;

        // Organizando vértices
        for(int i = id; i < MAX_VERTICES-1; i++) {
            vertices[i] = vertices[i+1];
            vertices[i]->setId(id);
        }

        // Organizando arestas
        Vertice *p = getVertice(id+1);
        if (p != nullptr) {
            if (direcionado) {
                /*for(int i = id; i < MAX_VERTICES-1; i++) {;
                    for(int j = id; i < MAX_VERTICES-1; i++) {
                        arestas[detIndice(i,j)] = arestas[detIndice(i+1, j)];
                    }
                }*/
                
                for(int i = id; i < MAX_VERTICES-1; i++) {
                    for(int j = i+1; j < MAX_VERTICES-1; j++) {
                        arestas[detIndice(i,j)] = arestas[detIndice(i,j)+MAX_VERTICES-1-i]; //Mover a linha para cima
                    }
                }
                for(int i=id; i<MAX_ARESTAS; i++){
                    arestas[i] = arestas[i+1]; //Mover a coluna entao mover todos a partir do primeiro da coluna
                }

            } else {
                for(int i = id; i < MAX_VERTICES-1; i++) {;
                    for(int j = 0; i < MAX_VERTICES-1; i++) {
                        arestas[detIndice(i,j)] = arestas[detIndice(i+1, j)]; //Mover a coluna para cima
                    }
                }
                for (int j = id; j < MAX_VERTICES-1; j++) {
                    for (int i = 0; i < MAX_VERTICES-1; i++) {
                        arestas[detIndice(i, j)] = arestas[detIndice(i, j + 1)]; // Mover coluna para a esquerda
                    }
                }
            }
        }

        ordem--;
        delete v;
    }

    cout << "Depois da Remover Vertice: " << endl;
    for(int i =0; i<numVertices; i++){
        cout << "Vertices " << vertices[i];
    }
    cout << endl;
    for(int i=0; i<MAX_ARESTAS ; i++){
        cout << "arestas " << arestas[i];
    }
}

