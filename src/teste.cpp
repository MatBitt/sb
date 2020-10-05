#include <iostream>
#include <string.h>
#include <map>
#include <fstream>
#include "utilidade.h"
#include "instrucoes.h"
#include "diretivas.h"
#include "preprocessamento.h"
#define OPERANDOS 0
#define TAMANHO 1
#define CODIGO 2

using namespace std;

map<string, int> primeira_passagem(char *argv){
    map<string, int> tabela_de_simbolos;
    string file = string(argv).substr(0, string(argv).find(".asm"));
    fstream arquivo;
    
    arquivo.open(file + ".pre", ios::in);
    if(!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo na primeira passagem!" << endl;
        exit(0);
    }
    else{
        string linha;
        map<string, vector<int>> instrucoes = getInstrucoes();
        map<string, vector<int>> diretivas = getDiretivas();
        map<string, vector<int>>::iterator it; 
        int cp = 0;

        while(getline(arquivo, linha)){
            vector<std::string> palavras;
            string aux;
            padronizar(linha);
            split(linha, palavras);

            // Caso seja uma label
            if(palavras[0][palavras[0].length()-1] == ':'){
                aux = palavras[0].substr(0, palavras[0].find(':'));
                it = instrucoes.find(aux);
                if(it != instrucoes.end()){   
                    cout << "Erro, instrução redefinida!" << endl;   
                }else{
                    tabela_de_simbolos[aux] = cp;
                }
                it = instrucoes.find(palavras[1]);
                if(it != instrucoes.end()){
                    cp += it->second[TAMANHO];
                }else{
                    it = diretivas.find(palavras[1]);
                    if(it != diretivas.end()){
                        cp += it->second[TAMANHO];
                    }
                }
            }

            // Caso seja ou uma instrucao ou diretiva
            else{
                it = instrucoes.find(palavras[0]);
                if(it != instrucoes.end()){
                    cp += it->second[TAMANHO];
                }else{
                    it = diretivas.find(palavras[0]);
                    if(it != diretivas.end()){
                        cp += it->second[TAMANHO];
                    }
                }
            }

        }
    }
    arquivo.close();
    return tabela_de_simbolos;
}

void segunda_passagem(char *argv, map<string, int> tabela_de_simbolos, int objeto = true){
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
            tabela_de_simbolos = primeira_passagem(argv[1]);
            segunda_passagem(argv[1], tabela_de_simbolos, true);
            break;
        
        case 3:
            if(string(argv[1]) == "-p"){
                pre_processamento(argv[2]);
            }else if(string(argv[1]) == "-o"){
                tabela_de_simbolos = primeira_passagem(argv[2]);
                segunda_passagem(argv[2], tabela_de_simbolos, true);
            }else{
                cout << "Argumento invalido!" << endl;
                return 0;
            }
            break;

        default:
            cout << "Numero de argumentos acima do esperado" << endl;
    }

}
