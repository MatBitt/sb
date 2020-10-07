#ifndef PRIMEIRAPASSAGEM_H_INCLUDED
#define PRIMEIRAPASSAGEM_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <fstream>
#include "utilidade.h"
#include "instrucoes.h"
#include "diretivas.h"
#define OPERANDOS 0
#define TAMANHO 1
#define CODIGO 2

map<string, int> primeira_passagem(string arquivo_prepocessado){
    map<string, int> tabela_de_simbolos;
    fstream arquivo;
    cout << arquivo_prepocessado << endl;
    
    arquivo.open(arquivo_prepocessado, ios::in);
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
            split(linha, palavras);

            // Caso seja uma label
            if(palavras[0][palavras[0].length()-1] == ':'){
                aux = palavras[0].substr(0, palavras[0].find(':'));
                it = instrucoes.find(aux);
                if(it != instrucoes.end()){   
                    cout << "Erro, instrução redefinida!" << endl;
                    exit(0);
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

#endif