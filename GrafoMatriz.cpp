#include "GrafoMatriz.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::ios;

GrafoMatriz::GrafoMatriz() : Grafo() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            matriz[i][j] = 0; //inicializa a matriz de adjacência
        }
    }
    numVertices = 0;
    direcionado = false;
}

GrafoMatriz::GrafoMatriz(int vertices, bool dir) : Grafo() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            matriz[i][j] = 0; //inicializa a matriz de adjacência
        }
        numVertices = vertices;
        direcionado = dir;
    }
}

GrafoMatriz::~GrafoMatriz() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        delete matriz[i];
    }
    delete matriz;
}

bool GrafoMatriz::eh_bipartido() {
    int cores[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        cores[i] = -1; //inicializa as cores em -1 para dizer que ainda nao foi coloriada
    }

    int fila[MAX_VERTICES], inicio = 0, fim = 0;
    for(int i=0; i<numVertices; i++){
        if(cores[i]==-1){
            cores[i] = 0; //cor do primeiro 0
            fila[fim] = i; //add vertice inical na fila
            fim++;
            while(inicio<fim){
                int u = fila[inicio];//remove o vertice do incio da fila
                inicio++;
                for(int v=0; v<numVertices; v++){
                    if(matriz[u][v]){ //se é diferente de 0
                        if(cores[v]==-1){
                            cores[v] = 1 - cores[u]; //v é colorida com a cor oposta de u
                            fila[fim] = v;//enfileira v
                            fim++;
                        }else if(cores[v]==cores[u]){
                            return false;//se u e v sao da mesma cor é falso
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GrafoMatriz::adicionaAresta(int origem, int destino, int peso) {
    matriz[origem - 1][destino - 1] = peso;
    if (!direcionado) {
        matriz[destino - 1][origem - 1] = 1;
    }
}
void GrafoMatriz::buscaProfundidade(int u, bool visitado[]) {
    visitado[u] = true;
    for (int v = 0; v < numVertices; v++) {
        if (matriz[u][v] && !visitado[v]) {
            buscaProfundidade(v, visitado);
        }
    }
}
/*int GrafoMatriz::AdicionarVertice(){
    return numVertices+1;
}*/
int GrafoMatriz::n_conexo() {
    bool visitado[MAX_VERTICES] = {false};
    int componentes = 0;

    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            componentes++;
            buscaProfundidade(i, visitado);
        }
    }
    return componentes;
}

int GrafoMatriz::get_grau(){
    int maior=0;
    if(direcionado){
        for(int i=0; i<numVertices; i++){
            int grau = 0;
            for(int j=0; j<numVertices; j++){
                if(matriz[j][i]){
                    grau++;
                }
            }
            if(grau>maior){
                maior = grau;
            }
        }
        return maior;
    }else{
        for(int i=0; i<numVertices; i++){
            int grau = 0;
            for(int j=0; j<numVertices; j++){
                if(matriz[i][j]){
                    grau++;
                }
            }
            if(grau>maior){
                maior = grau;
            }
        }
    }
    return maior;
}

int GrafoMatriz::get_ordem() {
    return numVertices;
}

bool GrafoMatriz::eh_direcionado() {
    return direcionado;
}

bool GrafoMatriz::eh_completo() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && !matriz[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int GrafoMatriz::contarArestas() {
    int arestas = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matriz[i][j] != 0) {
                arestas++;
            }
        }
    }
    return direcionado ? arestas : arestas / 2;
}

bool GrafoMatriz::eh_arvore() {
    return (n_conexo() == 1 && contarArestas() == numVertices - 1);
}

bool GrafoMatriz::vertice_ponderado() {
    return false;  // Implementação fictícia; ajuste conforme necessário
}

bool GrafoMatriz::aresta_ponderada() {
    return true;  // Implementação fictícia; ajuste conforme necessário
}

void GrafoMatriz::carrega_grafo(string nomeArquivo) {
    ifstream arquivo;
    //cout << "Carregando grafo do arquivo " << arquivo << "..." << endl;
    arquivo.open("Grafo.txt", ios::in);

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    cout << "Arquivo aberto com sucesso!" << endl;

    
    int numVertices, direcionado, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcionado >> ponderado_nos >> ponderado_arestas;
    /*std::cout<< "numVertices: "<<numVertices<<endl;
    std::cout<< "direcionado: "<<direcionado<<endl;
    std::cout<< "ponderado_nos: "<<ponderado_nos<<endl;
    std::cout<< "ponderado_arestas: "<<ponderado_arestas<<endl;*/

    this->numVertices = numVertices;
    this->direcionado = direcionado;

    //peso dos vertices
    int pesosVertices[numVertices];
    if (ponderado_nos == 1) {
        //cout << "Peso dos vértices:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            arquivo >> pesosVertices[i];
        }
    } else {
        //cout<< "Não há pesos nos vértices"<<endl;
        for (int i = 0; i < numVertices; ++i) {
            pesosVertices[i] = 1;
        }
    }

    //ler arestas
    int origem, destino, pesoAresta, pesoNada;
    while (arquivo >> origem >> destino) {
        
        if (ponderado_arestas == 1) {
            arquivo >> pesoAresta;
        } else {
            arquivo >> pesoNada;
            pesoAresta = 1;
        }

        if(direcionado){
            matriz[origem - 1][destino - 1] = pesoAresta;
        }
        else{
            if(origem<destino){
                matriz[origem - 1][destino - 1] = pesoAresta;
            }
            else{
                matriz[destino-1][origem-1] = pesoAresta;
            }
        }
    }

    arquivo.close();
    //cout<< "Arquivo fechado com sucesso"<<endl;
    // Exibir o grafo carregado
    //cout << "Grafo carregado com sucesso!" << endl;
    /*cout << "Matriz de adjacência:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << endl;
    }

    if (ponderado_nos == 1) {
        //std::cout << "Pesos dos vértices:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            //std::cout << "Vértice " << (i + 1) << ": " << pesosVertices[i] << endl;
        }
    }*/
}
void GrafoMatriz::imprimir_descricao() {
    cout << "Grau: " << get_grau() << endl;
    cout << "Ordem: " << get_ordem() << endl;
    cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Não") << endl;
    cout << "Componentes conexas: " << n_conexo() << endl;
    cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Não") << endl;
    cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Não") << endl;
    cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << endl;
    cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Não") << endl;
    cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << endl;
    cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
    cout << "Vertice de Articulação: " << (possui_articulacao() ? "Sim" : "Não") << endl;
}

void GrafoMatriz::novo_grafo(string nomeArquivo){
    //sem erro
}

bool GrafoMatriz::possui_ponte() {
    int componentesIniciais = n_conexo();

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matriz[i][j] != 0) {  
                int peso = matriz[i][j];  // Armazena o peso da aresta 
                // Removendo aresta(s)

                if (!direcionado) {
                    matriz[j][i] = 0; //remove a simetrica se direcionado
                    matriz[i][j] = 0;
                }
                else{
                matriz[i][j] = 0;}
                if (n_conexo() > componentesIniciais) {
                    
                    if (!direcionado)
                    {
                        matriz[i][j] = peso;
                        matriz[j][i] = peso;
                        return true; // Há pelo menos uma ponte
                    }
                    else{
                    matriz[i][j] = peso;
                    return true; // Há pelo menos uma ponte
                }}
                matriz[i][j] = peso;

                if (!direcionado) {
                    matriz[j][i] = peso; // Restaura a aresta reversa se o grafo não for direcionado
                }
            }
        }
    }

    return false; // Não há pontes
}

bool GrafoMatriz::possui_articulacao() {
    
    int componentesIniciais = n_conexo(); 

    for (int i = 0; i < numVertices; ++i) {
        // Aux para a linha e a coluna do vértice i, pra restauração 
        int linhaAux[MAX_VERTICES];
        int colunaAux[MAX_VERTICES];
        for (int j = 0; j < numVertices; ++j) {
            linhaAux[j] = matriz[i][j];
            colunaAux[j] = matriz[j][i];
        }

        // Remover o vértice
        for (int j = 0; j < numVertices; ++j) {
            matriz[i][j] = 0;
            matriz[j][i] = 0;
        }

       
        if (n_conexo() > componentesIniciais) {
            // Restaurando vértice
            
            for (int j = 0; j < numVertices; ++j) {
                matriz[i][j] = linhaAux[j];
                matriz[j][i] = colunaAux[j];
            }
            return true; // Pelo menos um vértice de articulação
        }

        // Restaurando vértice
        for (int j = 0; j < numVertices; ++j) {
            matriz[i][j] = linhaAux[j];
            matriz[j][i] = colunaAux[j];
        }
    }

    return false; // Não possui vértices de articulação
}

void GrafoMatriz::salvaGrafoMatriz(string nomeArquivo)
{
    ofstream arquivoGrafo;
    arquivoGrafo.open(nomeArquivo, ios::out);

    if (!arquivoGrafo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    } else {

        arquivoGrafo << nomeArquivo << "\n\n";
        arquivoGrafo << numVertices << " " << direcionado << " "<< vertice_ponderado() << " " << aresta_ponderada() << "\n";

        if (vertice_ponderado()) {
            int pesosVertices[numVertices];
            for (int i = 0; i < numVertices; i++) {
                arquivoGrafo << pesosVertices[i] <<" ";
            }
        }
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matriz[i][j] != 0) {
                if (aresta_ponderada()) {
                    arquivoGrafo << i << " " << j << " " << matriz[i][j] << "\n";
                } else {
                    arquivoGrafo << i << " " << j << "\n";
                }
            }
        }
    }

    arquivoGrafo.close();
}

void GrafoMatriz::imprimeGrafo(string nomeArquivo) {
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
