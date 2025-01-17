#include "GrafoLista.h"
#include "Vertice.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

GrafoLista::GrafoLista() {
    raizVertice = nullptr;
    raizAresta = nullptr;
    direcionado = false;
}

GrafoLista::~GrafoLista() {
    while (raizVertice != nullptr) {
        Vertice* p = raizVertice->getProx();
        delete raizVertice;
        raizVertice = p;
    }

    while (raizAresta != nullptr) {
        Aresta* a = raizAresta->getProx();
        delete raizAresta;
        raizAresta = a;
    }
}

Vertice* GrafoLista::getVertice(int id) {
    Vertice* v = raizVertice;
    while (v != nullptr) {
        if (v->getId() == id) {
            return v;
        }
        v = v->getProx();
    }
    return nullptr;
}

Aresta* GrafoLista::getAresta(int id_inicio, int id_fim) {
    Vertice* v = getVertice(id_inicio);
    Aresta** a = v->getVetorVizinhos();
    for (int i = 0; i < v->getTotalVizinhos(); i++) {
        if (v->getVizinho(i)->getFim()->getId() == id_fim) {
            return v->getVizinho(i);
        }
    }
    return nullptr;
}

Aresta ** GrafoLista::getVizinhos(int id) {
    Vertice* v = getVertice(id);
    if (v != nullptr) {
        return v->getVetorVizinhos();
    }
    cout << "Erro: indice invalido no getVizinhos()." << endl;
    exit(1);
}

void GrafoLista::inserirVertice(int id, float peso) {
    if (getVertice(id) == nullptr) {
        auto* v = new Vertice(id, peso);
        if (raizVertice != nullptr) {
            v->setProx(raizVertice);
        }
        raizVertice = v;
    }
    cout << "Erro: existe um vertice com o mesmo indice." << endl;
}

void GrafoLista::inserirAresta(int id_inicio, int id_fim, float peso) {
    if (id_inicio == id_fim) {
        cout << "Erro: não e possivel inserir laco." << endl;
    } else if (getAresta(id_inicio, id_fim) != nullptr) {
        cout << "Erro: não e possivel inserir aresta multipla." << endl;
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
            if (raizAresta != nullptr) {
                a->setProx(raizAresta);
            }
            raizAresta = a;

            //cout << "Aresta inserida: " << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
        }
    }
}

void GrafoLista::removerVertice(int id) {
    Vertice *v = getVertice(id);
    /// Remover arestas do vetor de arestas do vértice
    for (int i = v->getTotalVizinhos()-1; i >= 0; i--) {
        removerAresta(v->getVizinho(i)->getInicio()->getId(), v->getVizinho(i)->getFim()->getId());
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
}

void GrafoLista::removerAresta(int id_inicio, int id_fim) {
    Aresta *a = getAresta(id_inicio, id_fim);
    /// Remove aresta dos Vetores
    Vertice* v = a->getInicio();
    v->removerVizinho(a);
    v = a->getFim();
    v->removerVizinho(a);

    /// Remove aresta da lista de arestas do Grafo
    if (raizAresta == a) {
        raizAresta = a->getProx();
    } else {
        Aresta* ant = raizAresta;
        while (ant->getProx() != a) {
            ant = ant->getProx();
        }
        ant->setProx(a->getProx());
    }
    delete a;
}

// void GrafoLista::carrega_grafo(string nomeArquivo) {
//     ifstream arquivo;
//     arquivo.open(nomeArquivo, ios::in);
//
//     if (!arquivo.is_open()) {
//         cout << "Erro ao abrir o arquivo!" << endl;
//         exit(1);
//     }
//
//     int numVertices, direcionado, ponderado_nos, ponderado_arestas;
//     arquivo >> numVertices >> direcionado >> ponderado_nos >> ponderado_arestas;
//
//     this->direcionado = direcionado;
//
//     // Criar vértices
//     if (ponderado_nos == 1) {
//         float peso;
//         for (int i = 0; i < numVertices; ++i) {
//             arquivo >> peso;
//             inserirVertice(i+1, peso);
//         }
//     } else {
//         for (int i = 0; i < numVertices; ++i) {
//             inserirVertice(i+1, 1);
//         }
//     }
//
//     // Criar arestas
//     int origem, destino;
//     float peso;
//     while (arquivo >> origem >> destino) {
//         if (ponderado_arestas == 1) {
//             arquivo >> peso;
//             inserirAresta(origem, destino, peso);
//         } else {
//             inserirAresta(origem, destino, 1);
//         }
//     }
//
//     //imprimirVertices();
//     //imprimirArestas();
//     arquivo.close();
// }

void GrafoLista::imprimirVertices() {
    cout << "Lista de vertices: " << endl;
    Vertice* v = raizVertice;
    while (v != nullptr) {
        cout << v->getId() << " ";
        v = v->getProx();
    }
    cout << endl;
}

void GrafoLista::imprimirArestas() {
    cout << "Lista de arestas: " << endl;
    Aresta* a = raizAresta;
    while (a != nullptr) {
        cout << a->getInicio()->getId() << " -> " << a->getFim()->getId() << " Peso: " << a->getPeso() << endl;
        a = a->getProx();
    }
}

bool GrafoLista::aresta_ponderada() {
    Aresta *a = raizAresta;
    while (a != nullptr) {
        if (a->getPeso() != 1) {
            return true;
        }
        a = a->getProx();
    }
    return false;
}

int GrafoLista::get_ordem() {
    Vertice* v = raizVertice;
    int ordem = 0;
    while (v != nullptr) {
        ordem++;
        v = v->getProx();
    }
    return ordem;
}

bool GrafoLista::eh_direcionado() {
    return direcionado;
}

// int GrafoLista::n_conexo() {
//     int numVertices = get_ordem();
//     if (numVertices == 0) return 0;
//
//     bool *visitados = new bool[numVertices];
//     for (int i = 0; i < numVertices; ++i) {
//         visitados[i] = false;
//     }
//
//     int componentesConexas = 0;
//     for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
//         if (!visitados[v->getId() - 1]) {
//             auxNConexo(visitados, v);
//             componentesConexas++;
//         }
//     }
//
//     delete[] visitados;
//     return componentesConexas;
// }
//
// void GrafoLista::auxNConexo(bool *visitados, Vertice *v) {
//     visitados[v->getId() - 1] = true;
//     for (int i = 0; i < v->getTotalVizinhos(); ++i) {
//         Aresta* a = v->getVizinho(i);
//         Vertice* adj = a->getFim();
//         if (!visitados[adj->getId() - 1]) {
//             auxNConexo(visitados, adj);
//         }
//         adj = a->getInicio();
//         if (!visitados[adj->getId() - 1]) {
//             auxNConexo(visitados, adj);
//         }
//     }
// }

bool GrafoLista::ehCiclico() {
    int numVertices = get_ordem();
    if (numVertices == 0) return false;

    bool* visitados = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitados[i] = false;
    }

    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
        if (!visitados[v->getId() - 1]) {
            if (auxEhCiclico(v, visitados, nullptr)) {
                delete[] visitados;
                return true;
            }
        }
    }

    delete[] visitados;
    return false;
}

bool GrafoLista::auxEhCiclico(Vertice* v, bool* visitados, Vertice* pai) {
    visitados[v->getId() - 1] = true;
    for (int i = 0; i < v->getTotalVizinhos(); ++i) {
        Aresta* a = v->getVizinho(i);
        Vertice* adj = a->getFim();
        if (adj == v) {
            adj = a->getInicio();
        }
        if (!visitados[adj->getId() - 1]) {
            if (auxEhCiclico(adj, visitados, v)) {
                return true;
            }
        } else if (adj != pai) {
            return true;
        }
    }
    return false;
}

bool GrafoLista::eh_arvore() {
    if (n_conexo() == 1) {
        if (!ehCiclico())
            return true;
    }
    return false;
}

int GrafoLista::sortearVertice(int n) {
    return rand() % n + 1;
}

int GrafoLista::sortearPeso(int n) {
    return rand() % (2 * n + 1) - n;
}

Aresta* GrafoLista::inserirArestaAleatoria(int ordem, float peso) {
    int inicio = sortearVertice(ordem);
    int fim = sortearVertice(ordem);
    while (inicio == fim) {
        inicio = sortearVertice(ordem);
        fim = sortearVertice(ordem);
    }
    inserirAresta(inicio, fim, peso);
    return getAresta(inicio, fim);
}

void GrafoLista::dividirVertices(int* grupo1, int* grupo2, int ordem) {
    bool alternar = false;
    int i = 0, j = 0;
    for (int k = 1; k <= ordem; k++) {
        if (alternar) {
            grupo1[i] = k;
            i++;
        } else {
            grupo2[j] = k;
            j++;
        }
        alternar = !alternar;
    }
}

void GrafoLista::novo_grafo(string nomeArquivo) {
    srand(time(0));
    ifstream arquivo;

    arquivo.open(nomeArquivo, ios::in);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int _grau, ordem, _componentes;
    bool direcionado, verticesPonderados, arestasPonderadas, completo, bipartido, arvore, _ponte, _articulacao;

    arquivo >> _grau >> ordem >> direcionado >> _componentes >> verticesPonderados >> arestasPonderadas >> completo
            >> bipartido >> arvore >> _ponte >> _articulacao;

    arquivo.close();

    this->direcionado = direcionado;

    // Caso específico para vértice de articulação
    if (_articulacao && !bipartido && !arvore) {
        ordem--;
        _componentes++;
    }

    // Criando vértices
    for (int i = 0; i < ordem; i++) {
        int peso = verticesPonderados ? sortearPeso(20) : 1;
        inserirVertice(i+1, peso);
    }

    // Caso específico para grafo completo
    if (completo) {
        for (int i = 1; i <= ordem; i++) {
            for (int j = 1; j <= ordem; j++) {
                if (direcionado) {
                    if (i != j) {
                        arestasPonderadas ? inserirAresta(i, j, sortearPeso(20)) : inserirAresta(i, j, 1);
                    }
                } else {
                    if (i > j) {
                        arestasPonderadas ? inserirAresta(i, j, sortearPeso(20)) : inserirAresta(i, j, 1);
                    }
                }
            }
        }
    // Caso específico para grafos bipartidos
    } else if (bipartido) {
        // Dividindo vértices em dois grupos
        int tam1 = ordem / 2, tam2 = ordem - tam1;
        int* vetor1 = new int[tam1];
        int* vetor2 = new int[tam2];
        dividirVertices(vetor1, vetor2, ordem);

        // Criando arestas entre os dois grupos
        int componentes = ordem, grau = 0;
        while (componentes != _componentes || grau != _grau) {
            arestasPonderadas ? inserirAresta(vetor1[sortearVertice(tam1)-1], vetor2[sortearVertice(tam2)-1], sortearPeso(20)) : inserirAresta(vetor1[sortearVertice(tam1)-1], vetor2[sortearVertice(tam2)-1], 1);
            componentes = n_conexo();
            grau = get_grau();
            if (componentes < _componentes || grau > _grau) {
                removerAresta(raizAresta->getInicio()->getId(), raizAresta->getFim()->getId());
            }
        }

        // Verificação se possui vértice de articulação indevido
        bool articulacao = possui_articulacao();
        if (!_articulacao && articulacao) {
            while (articulacao != _articulacao || componentes != _componentes || grau != _grau) {
                arestasPonderadas ? inserirAresta(vetor1[sortearVertice(tam1)-1], vetor2[sortearVertice(tam2)-1], sortearPeso(20)) : inserirAresta(vetor1[sortearVertice(tam1)-1], vetor2[sortearVertice(tam2)-1], 1);
                componentes = n_conexo();
                grau = get_grau();
                articulacao = possui_articulacao();
                if (componentes < _componentes || grau > _grau) {
                    removerAresta(raizAresta->getInicio()->getId(), raizAresta->getFim()->getId());
                }
            }
        }
        delete [] vetor1;
        delete [] vetor2;

    // Caso específico para árvores
    } else if (arvore) {
        // Criando arestas acíclicas com uma componente conexa
        int componentes = ordem, grau = 0;
        bool ciclico = false;
        while (componentes != 1 || grau != _grau || ciclico) {
            Aresta *a = arestasPonderadas ? inserirArestaAleatoria(ordem, sortearPeso(20)) : inserirArestaAleatoria(ordem, 1);
            componentes = n_conexo();
            grau = get_grau();
            ciclico = ehCiclico();
            if (componentes < 1 || grau > _grau || ciclico) {
                removerAresta(a->getInicio()->getId(), a->getFim()->getId());
            }
        }

        // Verificação se possui vértice de articulação indevido
        bool articulacao = possui_articulacao();
        if (!_articulacao && articulacao) {
            while (articulacao != _articulacao || componentes != 1 || grau != _grau || ciclico) {
                Aresta *a = arestasPonderadas ? inserirArestaAleatoria(ordem, sortearPeso(20)) : inserirArestaAleatoria(ordem, 1);
                componentes = n_conexo();
                grau = get_grau();
                articulacao = possui_articulacao();
                ciclico = ehCiclico();
                if (componentes < 1 || grau > _grau || ciclico) {
                    removerAresta(a->getInicio()->getId(), a->getFim()->getId());
                }
            }
        }
    // Caso Geral
    } else {
        // Caso específico para aresta ponte
        if (_ponte) {
            _componentes++;
        }

        // Criando arestas
        int componentes = ordem, grau = 0;
        while (componentes != _componentes || grau != _grau) {
            Aresta *a = arestasPonderadas ? inserirArestaAleatoria(ordem, sortearPeso(20)) : inserirArestaAleatoria(ordem, 1);
            componentes = n_conexo();
            grau = get_grau();
            if (componentes < _componentes || grau > _grau) {
                removerAresta(a->getInicio()->getId(), a->getFim()->getId());
            }
        }

        // Verificação se possui vértice de articulação indevido
        bool articulacao = possui_articulacao();
        if (!_articulacao && articulacao) {
            while (articulacao != _articulacao || componentes != _componentes || grau != _grau) {
                Aresta *a = arestasPonderadas ? inserirArestaAleatoria(ordem, sortearPeso(20)) : inserirArestaAleatoria(ordem, 1);
                componentes = n_conexo();
                grau = get_grau();
                articulacao = possui_articulacao();
                if (componentes < _componentes || grau > _grau) {
                    removerAresta(a->getInicio()->getId(), a->getFim()->getId());
                }
            }
        }

        // Caso específico para vértice de articulação
        if (_articulacao) {
            ordem++;
            _componentes--;

            verticesPonderados ? inserirVertice(ordem, sortearPeso(20)) : inserirVertice(ordem, 1);

            while (articulacao != _articulacao || componentes != _componentes || grau != _grau) {
                int peso = arestasPonderadas ? sortearPeso(20) : 1;
                inserirAresta(ordem, sortearVertice(ordem - 1), peso);
                componentes = n_conexo();
                grau = get_grau();
                articulacao = possui_articulacao();
                if (componentes < _componentes || grau > _grau) {
                    removerAresta(raizAresta->getInicio()->getId(), raizAresta->getFim()->getId());
                }
            }
        }

        // Caso específico para aresta ponte
        if (_ponte) {
            _componentes--;

            while (componentes != _componentes || grau != _grau) {
                Aresta *a = arestasPonderadas ? inserirArestaAleatoria(ordem, sortearPeso(20)) : inserirArestaAleatoria(ordem, 1);
                componentes = n_conexo();
                grau = get_grau();
                if (componentes < _componentes || grau > _grau) {
                    removerAresta(a->getInicio()->getId(), a->getFim()->getId());
                }
            }

            // Verificação se possui vértice de articulação indevido
            articulacao = possui_articulacao();
            if (!_articulacao && articulacao) {
                bool ponte = true;
                while (articulacao != _articulacao || componentes != _componentes || grau != _grau || !ponte) {
                    Aresta *a = arestasPonderadas ? inserirArestaAleatoria(ordem, sortearPeso(20)) : inserirArestaAleatoria(ordem, 1);
                    componentes = n_conexo();
                    grau = get_grau();
                    articulacao = possui_articulacao();
                    ponte = possui_ponte();
                    imprimirArestas();
                    if (componentes < _componentes || grau > _grau || !ponte) {
                        removerAresta(a->getInicio()->getId(), a->getFim()->getId());
                    }
                }
            }
        }
    }

//     imprimirVertices();
//     imprimirArestas();

//     cout << "Grau: " << get_grau() << endl << "Ordem: " << get_ordem() << endl << "Direcionado: " << eh_direcionado() << endl <<
//         "Componentes conexas: " << n_conexo() << endl << "Vertices ponderados: " << vertice_ponderado() << endl <<
//         "Arestas ponderadas: " << aresta_ponderada() << endl << "Completo: " << eh_completo() << endl <<
//         "Bipartido: " << eh_bipartido() << endl << "Arvore: " << eh_arvore() << endl << "Aresta Ponte: " <<
//         possui_ponte() << endl << "Vertice de Articulacao: " << possui_articulacao() << endl;
}

void GrafoLista::salvaGrafo(string nomeArquivo) // para os casos de comando -l
{
    ofstream arquivoGrafo;
    arquivoGrafo.open(nomeArquivo, ios::out);

    if (!arquivoGrafo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }
    else{

        arquivoGrafo << nomeArquivo << "\n\n";
        arquivoGrafo << get_ordem() << " "<< eh_direcionado()<< " "<< vertice_ponderado()<<" "<< aresta_ponderada()<< "\n";

        if(vertice_ponderado()){

            Vertice* v = raizVertice;

            while (v != nullptr) {
                arquivoGrafo << v->getPeso() << " ";
                v = v->getProx();
            }

        }
        if(aresta_ponderada()){

            Aresta* a = raizAresta;

            while (a != nullptr) {
                arquivoGrafo << a->getInicio()->getId() << " " << a->getFim()->getId() << " " << a->getPeso() << "\n";
                a = a->getProx();
            }

        }
        else{
            Aresta* a = raizAresta;

            while (a != nullptr) {
                arquivoGrafo << a->getInicio()->getId() << " " << a->getFim()->getId() << "\n";
                a = a->getProx();
            }
        }
    }
    arquivoGrafo.close();
}