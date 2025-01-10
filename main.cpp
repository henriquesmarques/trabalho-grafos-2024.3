#include <iostream>
#include <fstream>
#include "GrafoLista.h"
#include "GrafoMatriz.h"
#include <string>

using namespace std;

int main(int argc, char *argv[])
{

    // comando inválido fornecido no terminal
    if (argc < 4 || argc > 5)
    {
        cout << "Erro na quantidade de argumentos" << "\n";
        return 1;
    }

    string opcao = argv[1];
    cout << "Valor armazenado em opcao: " << opcao << endl;
    string estrutura = argv[2];
    cout << "Valor armazenado em estrutura: " << estrutura << endl;
    string arquivoDescricao, arquivoGrafo;

    // Validação dos argumentos
    if (opcao != "-c" && opcao != "-d")
    {
        cout << "Erro: opção inválida" << "\n";
        return 1;
    }

    if (estrutura != "-l" && estrutura != "-m")
    {
        cout << "Erro: Estrutura inválida" << "\n";
        return 1;
    }

    if (opcao == "-d")
    {
        if (argc != 4)
        {
            cout << "Erro: -d requer 4 argumentos" << "\n";
            return 1;
        }
        arquivoGrafo = argv[3];
        if (estrutura == "-m")
        {
            cout << "Teste: grafo -d -m entrou" << "\n";
            GrafoMatriz g(0, false);
            g.carrega_grafo(arquivoGrafo);
            g.imprimir_descricao();
            // carrega grafo como matriz
            //  passar pra depois desse pedaço // imprime a descrição no fromato desejado
        }
        else
        {
            cout << "Teste: grafo -d -l entrou" << "\n";
            GrafoLista g;
            g.carrega_grafo(arquivoGrafo);
            g.imprimeGrafo(arquivoGrafo);
            // carrega grafo como lista
            //  passar pra depois desse pedaço // imprime a descrição no fromato desejado
        }
    }
    else if (opcao == "-c")
    {
        if (argc != 5)
        {
            cout << "Erro: -c requer 5 argumentos" << "\n";
            return 1;
        }
        arquivoDescricao = argv[3]; // arquivo passado para leitura
        arquivoGrafo = argv[4];     // arquivo passado para escrita

        if (estrutura == "-m")
        {
            cout << "Teste: grafo -c -m entrou" << "\n";
            // carrega grafo como matriz
            //  passar pra depois desse pedaço // imprime a descrição no fromato desejado
        }
        else
        {
            cout << "Teste: grafo -c -l entrou" << "\n";
            //GrafoLista g;
            //g.novo_grafo(arquivoDescricao);
            //g.salvaGrafoLista(arquivoGrafo);
            // carrega grafo como lista
            // imprime a descrição no fromato desejado
        }
    }
    else
    {
        cout << "Erro inesperado";
        return 1;
    }
    return 0;
}
