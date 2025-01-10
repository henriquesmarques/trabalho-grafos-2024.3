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
    // ordem = 0;
    // vertice_ponderado = false;
    // aresta_ponderada = false;
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

void GrafoLista::carrega_grafo(string nomeArquivo) {
    ifstream arquivo;
    arquivo.open(nomeArquivo, ios::in);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int numVertices, direcionado, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcionado >> ponderado_nos >> ponderado_arestas;

    this->direcionado = direcionado;

    // Criar vértices
    if (ponderado_nos == 1) {
        int peso;
        for (int i = 0; i < numVertices; ++i) {
            arquivo >> peso;
            inserirVertice(i+1, peso);
        }
    } else {
        for (int i = 0; i < numVertices; ++i) {
            inserirVertice(i+1, 1);
        }
    }

    //imprimirVertices();

    // Criar arestas
    int origem, destino, peso;
    while (arquivo >> origem >> destino) {
        Vertice *v = raizVertice;
        Vertice *inicio = nullptr;
        Vertice *fim = nullptr;
        while (v != nullptr) {
            if (v->getId() == origem) {
                inicio = v;
            }
            if (v->getId() == destino) {
                fim = v;
            }
            v = v->getProx();
        }

        if (inicio != nullptr && fim != nullptr) {
            if (ponderado_arestas == 1) {
                arquivo >> peso;
                inserirAresta(inicio, fim, peso);
            } else {
                inserirAresta(inicio, fim, 1);
            }
        } else {
            cout << "Erro ao inserir arquivo" << endl;
        }
    }

    //imprimirArestas();
    arquivo.close();
}

void GrafoLista::inserirVertice(int id, int peso) {
    Vertice* v = new Vertice(id);
    v->setPeso(peso);
    if (raizVertice != nullptr) {
        v->setProx(raizVertice);
    }
    raizVertice = v;
}

void GrafoLista::inserirAresta(Vertice *inicio, Vertice *fim, int peso) {
    if (inicio == fim) {
        cout << "Erro: o grafo não permite inserir laço." << endl;
    } else {
        // Criando aresta
        Aresta* a = new Aresta();
        a->setPeso(peso);
        a->setInicio(inicio);
        a->setFim(fim);

        // Adiciona aresta nos Vértices
        inicio->inserirAresta(a);
        fim->inserirAresta(a);

        // Adicionando aresta na lista
        if (raizAresta != nullptr) {
            a->setProx(raizAresta);
        }
        raizAresta = a;

        //cout << "Aresta inserida: " << a->getInicio()->getId() << " -> " << a->getFim()->getId() << endl;
    }
}

void GrafoLista::inserirPonteiroAresta(Aresta* a) {
    // Adicionando ponteiro da aresta no vértice
    a->getInicio()->inserirAresta(a);
    a->getFim()->inserirAresta(a);

    // Adicionando aresta na lista
    if (raizAresta != nullptr) {
        a->setProx(raizAresta);
    }
    raizAresta = a;
}

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

int GrafoLista::n_conexo() {
    int numVertices = get_ordem();
    if (numVertices == 0) return 0;

    bool *visitados = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitados[i] = false;
    }

    int componentesConexas = 0;
    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
        if (!visitados[v->getId() - 1]) {
            auxNConexo(visitados, v);
            componentesConexas++;
        }
    }

    delete[] visitados;
    return componentesConexas;
}

void GrafoLista::auxNConexo(bool *visitados, Vertice *v) {
    visitados[v->getId() - 1] = true;
    for (int i = 0; i < v->totalArestas(); ++i) {
        Aresta* a = v->getAresta(i);
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
    for (int i = 0; i < v->totalArestas(); ++i) {
        Aresta* a = v->getAresta(i);
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

Aresta* GrafoLista::inserirArestaAleatoria(int ordem, int peso) {
    Aresta* a = new Aresta(buscaVertice(sortearVertice(ordem)),buscaVertice(sortearVertice(ordem)),peso);
    while (a->getInicio() == a->getFim()) {
        a->setInicio(buscaVertice(sortearVertice(ordem)));
        a->setFim(buscaVertice(sortearVertice(ordem)));
    }
    inserirPonteiroAresta(a);
    return a;
}

void GrafoLista::dividirVertices(Vertice** grupo1, Vertice** grupo2) {
    Vertice* v = raizVertice;
    bool alternar = false;
    int i = 0, j = 0;
    while (v != nullptr) {
        if (alternar) {
            grupo1[i] = v;
            i++;
        } else {
            grupo2[j] = v;
            j++;
        }
        alternar = !alternar;
        v = v->getProx();
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
                        arestasPonderadas ? inserirAresta(buscaVertice(i), buscaVertice(j), sortearPeso(20)) : inserirAresta(buscaVertice(i), buscaVertice(j), 1);
                    }
                } else {
                    if (i > j) {
                        arestasPonderadas ? inserirAresta(buscaVertice(i), buscaVertice(j), sortearPeso(20)) : inserirAresta(buscaVertice(i), buscaVertice(j), 1);
                    }
                }
            }
        }
    // Caso específico para grafos bipartidos
    } else if (bipartido) {
        // Dividindo vértices em dois grupos
        int tam1 = ordem / 2, tam2 = ordem - tam1;
        Vertice** vetor1 = new Vertice*[tam1];
        Vertice** vetor2 = new Vertice*[tam2];
        dividirVertices(vetor1, vetor2);

        // Criando arestas entre os dois grupos
        int componentes = ordem, grau = 0;
        while (componentes != _componentes || grau != _grau) {
            arestasPonderadas ? inserirAresta(vetor1[sortearVertice(tam1)-1], vetor2[sortearVertice(tam2)-1], sortearPeso(20)) : inserirAresta(vetor1[sortearVertice(tam1)-1], vetor2[sortearVertice(tam2)-1], 1);
            componentes = n_conexo();
            grau = get_grau();
            if (componentes < _componentes || grau > _grau) {
                removerAresta(raizAresta);
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
                    removerAresta(raizAresta);
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
                removerAresta(a);
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
                    removerAresta(a);
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
                removerAresta(a);
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
                    removerAresta(a);
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
                inserirAresta(buscaVertice(ordem), buscaVertice(sortearVertice(ordem - 1)), peso);
                componentes = n_conexo();
                grau = get_grau();
                articulacao = possui_articulacao();
                if (componentes < _componentes || grau > _grau) {
                    removerAresta(raizAresta);
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
                    removerAresta(a);
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
                        removerAresta(a);
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

void GrafoLista::salvaGrafoLista(string nomeArquivo) // para os casos de comando -l
{
    //verificação do arquivo

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

void GrafoLista::imprimeGrafo(string nomeArquivo)
{
    cout<<nomeArquivo<<"\n";

    cout<<"Grau: "<<get_grau()<<"\n";

    cout<<"Ordem: "<<get_ordem()<<"\n";

    if(eh_direcionado())
    {cout<<"Direcionado: "<<"Sim"<<"\n";}
    else{cout<<"Direcionado: "<<"Nao"<<"\n";}

    cout<<"Componentes conexas: "<<n_conexo()<<"\n";

    if(vertice_ponderado())
    {cout<<"Vertices ponderados: "<<"Sim"<<"\n";}
    else{cout<<"Vertices ponderados: "<<"Nao"<<"\n";}

    if(aresta_ponderada())
    {cout<<"Arestas ponderadas: "<<"Sim"<<"\n";}
    else{cout<<"Arestas ponderadas: "<<"Nao"<<"\n";}

    if(eh_completo())
    {cout<<"Completo: "<<"Sim"<<"\n";}
    else{cout<<"Completo: "<<"Nao"<<"\n";}

    if(eh_bipartido())
    {cout<<"Bipartido: "<<"Sim"<<"\n";}
    else{cout<<"Bipartido: "<<"Nao"<<"\n";}

    if(eh_arvore())
    {cout<<"Arvore: "<<"Sim"<<"\n";}
    else{cout<<"Arvore: "<<"Nao"<<"\n";}

    if(possui_ponte())
    {cout<<"Aresta Ponte: "<<"Sim"<<"\n";}
    else{cout<<"Aresta Ponte: "<<"Nao"<<"\n";}

    if(possui_articulacao())
    {cout<<"Vertide de Articulacao: "<<"Sim"<<"\n";}
    else{cout<<"Vertide de Articulacao: "<<"Nao"<<"\n";}
}
