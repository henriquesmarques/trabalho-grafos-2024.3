#include "../include/GrafoMatriz.h"

GrafoMatriz::GrafoMatriz() {
    MAX_VERTICES = 10;
    MAX_ARESTAS = MAX_VERTICES*MAX_VERTICES;
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
    if (dir) {
        MAX_ARESTAS = (MAX_VERTICES+1)*MAX_VERTICES/2-MAX_VERTICES;
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
        MAX_ARESTAS = (MAX_VERTICES+1)*MAX_VERTICES/2-MAX_VERTICES;
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
    if (direcionado) {
        MAX_ARESTAS = (MAX_VERTICES+1)*MAX_VERTICES/2-MAX_VERTICES;
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
    if (direcionado) {
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
    if (direcionado) {
        if (i < j && i < MAX_VERTICES && j > i && j < MAX_VERTICES) {
            return (j+1)*j/2+i; // caso especifico para matriz superior
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
void GrafoMatriz::removerVertice(int id){
    imprimirArestas();
    Vertice *v = getVertice(id);
    if (v==nullptr) {
        cout<<"Erro: vertice nao encontrado."<<endl;
    }
    else {
        for (int i = id; i < numVertices - 1; i++) {
            // Desloca linhas para cima
            for (int j = 0; j < numVertices; j++) {
                novaMatriz[i][j] = novaMatriz[i + 1][j];
            }
        }

        for (int j = id; j < numVertices - 1; j++) {
            // Desloca colunas para a esquerda
            for (int i = 0; i < numVertices; i++) {
                novaMatriz[i][j] = novaMatriz[i][j + 1];
            }
        }
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
/*void GrafoMatriz::removerVertice(int id) {
    if(v == 0){
        cout << "Vertice não encontrado";
    }else{
        for(int i = 0; i<getOrdem(); i++{
            if(novaMatriz[i][v]){
                removerAresta(i, v)
            }
            if(novaMatriz[v][i])~{
                removerAresta(v,i);
            }
        }
    }
    novosVertices[id] = 0;
    for(int i = id; i<getOrdem; i++){
        novosVertices[i] = novosVertices[i+1];
    }
    ordem--;
}*/

void GrafoMatriz::removerAresta(int id_inicio, int id_fim) {
}
