#include "../include/Grafo.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#define INF 1e9

using namespace std;

Grafo::Grafo() {
    direcionado = false;
    verticesPonderados = false;
    arestasPonderadas = false;
    ordem = 0;
}

Grafo::~Grafo() = default;

void Grafo::carrega_grafo(string nomeArquivo) {
    ifstream arquivo;
    arquivo.open("entradas/"+nomeArquivo, ios::in);
    //arquivo.open("entradas/Grafo.txt", ios::out);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int numVertices, direcao, ponderado_nos, ponderado_arestas;
    arquivo >> numVertices >> direcao >> ponderado_nos >> ponderado_arestas;

    setDirecao(direcao);
    this->verticesPonderados = ponderado_nos;
    this->arestasPonderadas = ponderado_arestas;

    // Criar vértices
    if (ponderado_nos == 1) {
        float peso;
        for (int i = 0; i < numVertices; i++) {
            arquivo >> peso;
            inserirVertice(i+1, peso);
        }
    } else {
        for (int i = 0; i < numVertices; ++i) {
            inserirVertice(i+1, 1);
        }
    }

    // Criar arestas
    int origem, destino;
    float peso;
    while (arquivo >> origem >> destino) {
        if (ponderado_arestas == 1) {
            arquivo >> peso;
            inserirAresta(origem, destino, peso);
        } else {
            inserirAresta(origem, destino, 1);
        }
    }

    arquivo.close();
}

void Grafo::imprimeGrafo() {

    cout << "Grau: " << get_grau() << endl;

    cout<<"Ordem: "<<get_ordem()<<"\n";

    if(eh_direcionado())
    {cout<<"Direcionado: "<<"Sim"<<"\n";}
    else{cout<<"Direcionado: "<<"Nao"<<"\n";}

    //cout<<"Componentes conexas: "<<n_conexo()<<"\n";

    if(vertice_ponderado())
    {cout<<"Vertices ponderados: "<<"Sim"<<"\n";}
    else{cout<<"Vertices ponderados: "<<"Nao"<<"\n";}

    if(aresta_ponderada())
    {cout<<"Arestas ponderadas: "<<"Sim"<<"\n";}
    else{cout<<"Arestas ponderadas: "<<"Nao"<<"\n";}

    if(eh_completo())
    {cout<<"Completo: "<<"Sim"<<"\n";}
    else{cout<<"Completo: "<<"Nao"<<"\n";}
}

bool Grafo::eh_completo() {
    if (get_ordem() == 0)
        return false;
    ///verifica se todos os nos possuem mesmo grau
    int grau = 0, grauGrafo = 0, aux = 0;
    for (int i = 1; i <= get_ordem(); i++) {
        aux++;
        grau = eh_direcionado() ? getVertice(i)->totalArestasSaida() : getVertice(i)->getTotalVizinhos();
        if (aux == 1)
            grauGrafo = grau;
        if (grau != grauGrafo) {
            return false;
        }
    }
    if (grauGrafo == get_ordem()-1)
        return true;
    return false;
}

bool Grafo::eh_direcionado() const {
    return direcionado;
}

bool Grafo::vertice_ponderado() const {
    return verticesPonderados;
}

bool Grafo::aresta_ponderada() const {
    return arestasPonderadas;
}

int Grafo::get_ordem() const {
    return ordem;
}

int Grafo::n_conexo() {
    int numVertices = get_ordem();
    if (numVertices == 0) return 0;

    bool *visitados = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visitados[i] = false;
    }

    int componentesConexas = 0;
    for (int i = 1; i <= get_ordem(); i++) {
        if (!visitados[getVertice(i)->getId() - 1]) {
            auxNConexo(visitados, getVertice(i));
            componentesConexas++;
        }
    }

    delete[] visitados;
    return componentesConexas;
}

void Grafo::auxNConexo(bool *visitados, Vertice *v) {
    visitados[v->getId() - 1] = true;
    for (int i = 0; i < v->getTotalVizinhos(); ++i) {
        Aresta* a = v->getVizinho(i);
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

int Grafo::get_grau() {
    ///informa o grau do grafo para grafos não direcionados
    int grauGrafo = 0;
    if (!eh_direcionado()) {
        int grau = 0;
        for(int i = 1; i <= get_ordem(); i++){
            Vertice *v = getVertice(i);
            grau = v-> getTotalVizinhos();
            if(grau > grauGrafo)
                grauGrafo = grau;
        }
        return grauGrafo;
    }
    ///informa o grau do grafo para grafos direcionados
    else{
        for(int i = 1; i <= get_ordem(); i++){
            Vertice *v = getVertice(i);
            int grauSaida = v->totalArestasSaida();
            if(grauSaida > grauGrafo)
                grauGrafo = grauSaida;
        }
        return grauGrafo;
    }
}

void Grafo::caminhoMinino() {
    if (get_ordem() == 0)
        cout << "Não existem caminhos" << endl;
    else {
        ///Verifica se as arestas possuem peso e verifica se tem algum peso negativo
        float neg = 0;
        if (aresta_ponderada()) {
            ///verifica se existe algum peso negativo
            for(int i = 1; i <= get_ordem(); i++) {
                Vertice *v = getVertice(i);
                Aresta **a = v->getVetorVizinhos();
                for (int j = 0; j < v->getTotalVizinhos(); j++) {
                    if (a[j]->getPeso() < neg)
                        neg = a[j]->getPeso();
                }
            }
            ///passa o valor absoluto do menor peso negativo para a variavel neg
            neg = abs(neg)+1;
            ///caso exista peso negativo, é adicionado o valor absoluto do menor peso negativo
            if (neg > 1) {
                for(int i = 1; i <= get_ordem(); i++) {
                    Vertice *v = getVertice(i);
                    Aresta **a = v->getVetorVizinhos();
                    for (int j = 0; j < v->getTotalVizinhos(); j++){
                        ///se a aresta ainda não foi visitada, é adicionado o valor absoluto do menor peso negativo
                        if(!a[j]->getVisitado()){
                            a[j]->setPeso(a[j]->getPeso() + neg);
                            a[j]->setVisitado(true);
                        }
                    }
                }
            }
        }
        ///inicialização das variaveis
        float menor_caminho[4] = {0, 0, 0, 0};

        for(int n = 1; n <= ordem; n++){
        float dist[ordem];
        bool visitados[ordem];
        int num_aresta[ordem];
        for (int i = 0; i < ordem; i++) {
            dist[i] = INF;
            visitados[i] = false;
            num_aresta[i]=0;}

        ///indica o no de origem
        dist[n] = 0;
        ///caso para grafos direcionados
        if (eh_direcionado()) {
            for (int k = 0; k < ordem - 1; k++) {
                int u = minDistance(dist, visitados);
                if(u == -1)break;
                visitados[u] = true;
                for (int v = 0; v < ordem; v++) {
                    Aresta* uv = getAresta(u+1,v+1);
                    if (!visitados[v] && uv != nullptr
                    && dist[u] != INF && dist[u] + uv->getPeso() < dist[v]){
                        dist[v] = dist[u] + uv->getPeso();
                        num_aresta[v] += 1;}}}}

        ///caso para grafos não direcionados
        else {
            for (int m = 0; m < ordem - 1; m++) {
                int u = minDistance(dist, visitados);
                visitados[u] = true;
                for (int v = 0; v < ordem; v++) {
                    Aresta* uv = getAresta(u+1,v+1);
                    Aresta* vu = getAresta(v+1,u+1);
                    if (!visitados[v] && uv != nullptr
                    && dist[u] != INF && dist[u] + uv ->getPeso() < dist[v]){
                        dist[v] = dist[u] + uv->getPeso();
                        num_aresta[v] += 1;
                    }
                    else if(!visitados[u] && vu != nullptr && dist[v] != INF && dist[v] + vu->getPeso()<dist[u]){
                        dist[v] = dist[u] + vu->getPeso();
                        num_aresta[v] += 1;}
        }}}
        ///verifica o maior menor caminho
        for (int j = 0; j < ordem; j++) {
            if (dist[j] != INF && dist[j] > menor_caminho[0]) {
                menor_caminho[0] = dist[j];  // Peso do menor caminho
                menor_caminho[1] = n+1;       // Vértice inicial
                menor_caminho[2] = j + +1;   // Vértice final
                menor_caminho[3] = num_aresta[j]; // Número de arestas
            }}
        }
        // Impressão
        if(neg > 1)
            cout<< "Maior menor distancia: (" << menor_caminho[1] << "-" << menor_caminho[2] << ") " << menor_caminho[0]-(menor_caminho[3]*neg) << endl;
        else
        cout<< "Maior menor distancia: (" << menor_caminho[1] << "-" << menor_caminho[2] << ") " << menor_caminho[0] << endl;

        // Restaurar os pesos
        if (neg > 1) {
            for(int i = 1; i <= get_ordem(); i++) {
                Vertice *v = getVertice(i);
                Aresta **a = v->getVetorVizinhos();
                for (int j = 0; j < v->getTotalVizinhos(); j++){
                    ///se a aresta ainda não foi visitada, é adicionado o valor absoluto do menor peso negativo
                    if(a[j]->getVisitado()){
                        a[j]->setPeso(a[j]->getPeso() - neg);
                        a[j]->setVisitado(false);}}}}
    }
}

int Grafo::minDistance(float dist[], bool visitados[]) {
        float min = INF;
        int min_index = -1;

        for (int i = 0; i < ordem; i++) {
            if (visitados[i] == false && dist[i] <= min) {
                min = dist[i];
                min_index = i;
            }
        }
        return min_index;
}
/// Outra maneira de implementar seria criando um vetor do tamanho de todos os vizinhos de um vértice
/// armazenar as cores de todos seus vizinhos e fazer uma comparação entre todas as posições para
/// encontrar o menor valor a ser adicionado no próximo vértice

void Grafo::colorirVerticesRandomizado() {
    /// Algoritmo de sorteio
    int *sorteados = sortearValores(get_ordem(), get_ordem());

    /// Início do código de coloração
    for (int i = 0; i < get_ordem(); i++) {
        /// Pega o primeiro vértice que foi sorteados aleatoriamente
        Vertice *v = getVertice(sorteados[i]);

        /// Inicializa um vetor para todos os vizinhos do vértice
        Vertice** verticesVizinhos = v->getVerticesVizinhos();
        int n = v->getTotalVizinhos();

        int coresVizinhas[n];

        for (int j = 0; j < n; j++) {
            coresVizinhas[j] = verticesVizinhos[j]->getCor();
        }
        delete[] verticesVizinhos;

        int cor = menor_valor_ausente(coresVizinhas, n);

        /// Atribui a menor cor encontrada para o vértice
        v->setCor(cor);
    }

    imprimirVertices();
    delete[] sorteados;
}

int* Grafo::sortearValores(int intervalo, int quantidade) {
    // Intervalo de 1 até ordem
    // Quantidade de números a serem sorteados

    /// Verifica se a quantidade de números a serem sorteados é maior que o intervalo
    if (quantidade > intervalo) {
        cout << "Erro: A quantidade de numeros a serem sorteados e maior que o intervalo.";
        exit(1);
    }

    /// Aloca memória para um array com todos os números do intervalo
    int* numeros = new int[intervalo];
    for (int i = 0; i < intervalo; ++i) {
        numeros[i] = i + 1;
    }

    /// Inicializa o gerador de números aleatórios com a hora atual
    srand(time(0));

    /// Embaralha o array aleatoriamente usando o algoritmo de Fisher-Yates
    for (int i = intervalo - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(numeros[i], numeros[j]);
    }

    /// Retorna um vetor com os números sorteados
    return numeros;
}

void Grafo::ordenarVetor(int arr[], int n) {
    /// Algoritmo Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca arr[j] e arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int Grafo::menor_valor_ausente(int arr[], int tamanho) {
    // 1. Verificar se o array está vazio
    if (tamanho == 0) {
        return 1; // Se estiver vazio, o menor valor ausente é 1
    }

    // 2. Ordenar o array em ordem crescente (usando algoritmo da biblioteca algorithm)
    ordenarVetor(arr, tamanho);

    // 3. Verificar se o menor valor é maior que 1
    if (arr[0] > 1) {
        return 1; // Se for, o menor valor ausente é 1
    }

    // 4. Iterar pelo array procurando por lacunas
    for (int i = 0; i < tamanho - 1; ++i) {
        if (arr[i + 1] - arr[i] > 1) {
            return arr[i] + 1; // Encontramos uma lacuna, o valor ausente é o seguinte
        }
    }

    // 5. Se não houver lacunas, o menor valor ausente é o seguinte ao maior valor
    return arr[tamanho - 1] + 1;
}

void Grafo::gulosoColoracaoVertice(){
    if (get_ordem() == 0)
        cout << "Não existem vertices" << endl;
    ///caso o grafo possua grau 0, todos podem ser coloridos com a mesma cor
    else if(get_grau() == 0){
        for(int i=0; i<ordem; i++){
            Vertice *v = getVertice(i);
            v->setCor(1);
        }
    }
    else{
        //Marca o primeiro vertice com a menor cor
        Vertice *v = getVertice(1);
        v->setCor(1);
        ///começa a colorir os vertices a partir do segundo
        for(int i = 2; i<=ordem; i++){
            v = getVertice(i);
            int viz = v->getTotalVizinhos();

            /// Inicializa um vetor para todos os vizinhos do vértice
            Vertice** verticesVizinhos = v->getVerticesVizinhos();
            ///inicializa um vetor com as cores dos vizinhos
            int cores_vizinhas[viz];
            //preenche o vetor com as cores dos vizinhos
            for(int j=0; j<viz; j++)
                cores_vizinhas[j] = verticesVizinhos[j]->getCor();


            /// Ordena o vetor das cores dos vizinhos
            ordenarVetor(cores_vizinhas, viz);
            /// Atribui a menor cor possível ao vértice
            int cor = menor_valor_ausente(cores_vizinhas, viz);
            /// Atribui a cor ao vértice sorteado
            v->setCor(cor);
        }
    }
    imprimirVertices();
}