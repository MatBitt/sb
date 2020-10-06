#include <iostream>
#include <string.h>
#include <map>
#include <fstream>
#include "utilidade.h"
#include "instrucoes.h"
#include "diretivas.h"
#include "preprocessamento.h"
#include "primeirapassagem.h"

using namespace std;

void segunda_passagem(char *argv, map<string, int> tabela_de_simbolos){
    fstream arquivo;
    arquivo.open(string(argv), ios::in);
    if(!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(0);
    }
    else{
        string linha;
        map<string, vector<int>> instrucoes = getInstrucoes();
        map<string, vector<int>> diretivas = getDiretivas();
        map<string, vector<int>>::iterator it; 

        while(getline(arquivo, linha)){
            vector<std::string> palavras;
            string aux;
            padronizar(linha);
            split(linha, palavras);  

            
        }
    }
}

int main(int argc, char **argv){
   
    map<string, int> tabela_de_simbolos;

    switch(argc){
        case 1:
            cout << "Numero de argumentos abaixo do esperado!";
            return 0;

        case 2:
            pre_processamento(argv[1]);
            tabela_de_simbolos = primeira_passagem(argv[1]);
            segunda_passagem(argv[1], tabela_de_simbolos);
            break;
        
        case 3:
            if(string(argv[1]) == "-p"){
                pre_processamento(argv[2]);
            }else if(string(argv[1]) == "-o"){
                pre_processamento(argv[2]);
                tabela_de_simbolos = primeira_passagem(argv[2]);
                segunda_passagem(argv[2], tabela_de_simbolos);
            }else{
                cout << "Argumento invalido!" << endl;
                return 0;
            }
            break;

        default:
            cout << "Numero de argumentos acima do esperado" << endl;
    }

}
