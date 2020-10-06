#ifndef PREPROCESSAMENTO_H_INCLUDED
#define PREPROCESSAMENTO_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <iterator>
#include <fstream>
#include "utilidade.h"

using namespace std;

string padronizar(string linha){

    linha = linha.substr(0, linha.find(";"));

    for(size_t i = 0; i<linha.length(); i++){
        linha[i] = toupper(linha[i]);
    }

    return linha;
}

string escreve_macro(vector<string> palavras){
    string linha;
    size_t i;
    for(i = 0; i< palavras.size(); i++){
        linha = linha + palavras[i] + ' ';
    }
    linha.push_back('\n');
    return linha;
}

void pre_processamento(char *argv){
    map<string, int> tabela_equ;
    map<string, string> macros;
    string arquivo = string(argv).substr(0, string(argv).find(".asm"));

    fstream arquivo_raw;
    arquivo_raw.open(arquivo + ".asm", ios::in);
    if(!arquivo_raw.is_open())
    {
        cout << "Erro ao abrir o arquivo original!" << endl;
        exit(0);
    }
    else{
        string linha;
        // Antes de Section Text
        while(getline(arquivo_raw, linha)){
            if(linha.empty()) continue;
            vector<std::string> palavras;
            string aux;
            linha = padronizar(linha);
            split(linha, palavras);

            if(palavras[0][palavras[0].length()-1] == ':'){
                aux = palavras[0].substr(0, palavras[0].find(':'));
                if(palavras.size() == 1){
                    do{
                        getline(arquivo_raw, linha);
                    }while(linha.empty());
                    linha = padronizar(linha);
                    split(linha, palavras);
                }
                tabela_equ[aux] = stoi(palavras[2]);
            }else{
                break;
            }
        }

         // Depois de Section Text
        ofstream arquivo_preprocessado(arquivo + ".pre");
        if(!arquivo_preprocessado.is_open())
        {
            cout << "Erro ao abrir o arquivo pre processado!" << endl;
            exit(0);
        }else{

            // Escrever Section Text    
            arquivo_preprocessado << "SECTION TEXT\n";

            while(getline(arquivo_raw, linha)){
                if(linha.empty()) continue;
                vector<std::string> palavras;
                string aux;
                linha = padronizar(linha);
                split(linha, palavras);
                if(palavras[0] == "IF"){
                    if(tabela_equ[palavras[1]] == 0){
                        do{
                            getline(arquivo_raw, linha);
                        }while(linha.empty());
                        continue;
                    }else{
                        do{
                            getline(arquivo_raw, linha);
                        }while(linha.empty());
                        palavras.clear();
                        linha = padronizar(linha);
                        split(linha, palavras);
                        escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                    }
                }else

                // Tratamento de Labels
                if(palavras[0][palavras[0].length()-1] == ':'){
                    if( (int)palavras.size() > 1){

                         // Tratamento de Macros
                        if(palavras[1] == "MACRO"){
                            aux = palavras[0].substr(0, palavras[0].find(':'));

                            if((int)palavras.size() == 5){
                                // &a , &b
                            }
                            else if((int)palavras.size() == 4){
                                // &a, &b ou &a ,&b
                            }
                            else if((int)palavras.size() == 3){
                                // &a
                            }else{
                                while(palavras[0] != "ENDMACRO"){
                                    palavras.clear();   
                                    do{
                                        getline(arquivo_raw, linha);
                                    }while(linha.empty());
                                    linha = padronizar(linha);
                                    split(linha, palavras);
                                    if(palavras[0] != "ENDMACRO")
                                    macros[aux] = macros[aux] + escreve_macro(palavras);
                                }
                                palavras.clear();
                            }
                        }else{
                            escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                        }

                    }else{
                        do{
                            getline(arquivo_raw, linha);
                        }while(linha.empty());
                        linha = padronizar(linha);
                        split(linha, palavras);
                        escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                    }
                }else if(palavras.size() != 0){
                    map<string, string>::iterator it;
                    it = macros.find(palavras[0]);
                    // Caso ache a label nas macros
                    if(it != macros.end()){
                        arquivo_preprocessado << it->second;
                    }else{
                        escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                    }
                }              
            }   
        }
    arquivo_preprocessado.close();
    cout << "Arquivo .pre gerado!" << endl;
    }
    arquivo_raw.close();
}

#endif