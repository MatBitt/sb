#ifndef PREPROCESSAMENTO_H_INCLUDED
#define PREPROCESSAMENTO_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <iterator>
#include <fstream>
#include "utilidade.h"

using namespace std;

// Retira os comentarios e poe tudo em caixa alta
string padronizar(string linha){

    linha = linha.substr(0, linha.find(";"));

    for(size_t i = 0; i<linha.length(); i++){
        linha[i] = toupper(linha[i]);
    }

    if(linha.find_first_not_of(' ') == string::npos){
        string vazia;
        linha = vazia;
    }

    return linha;
}

// Troca as variaveis definadas nas macros pelas variaveis que o programa fornece quando chama a macro
string substitui_labels(string texto, vector<string> macros_labels, string label1, string label2){
    if(macros_labels[0].length() > macros_labels[1].length()){
        texto = troca(texto, macros_labels[0], label1);
        texto = troca(texto, macros_labels[1], label2);
    }else{
        texto = troca(texto, macros_labels[1], label2);
        texto = troca(texto, macros_labels[0], label1);
    }

    return texto;
}

// Escreve uma linha na variavel que armazena a macro
string escreve_macro(vector<string> palavras){
    string linha;
    int i;
    for(i = 0; i< (int) palavras.size(); i++){

        if(i< (int) palavras.size() - 1){
            if(palavras[i+1] == ","){
                linha = linha + palavras[i];
                continue;
            }
            else if(palavras[i+1][0] == ','){
                linha = linha + palavras[i] + ',' + ' ';
                palavras[i+1] = palavras[i+1].substr(1);
                continue;
            }
            else{
                linha = linha + palavras[i] + ' ';
                continue;
            }
        }
        linha = linha + palavras[i];

    }
    linha.push_back('\n');
    return linha;
}

void pre_processamento(string arquivo_assembly){
    map<string, string> tabela_equ;
    map<string, string> macros;
    map<string, vector<string>> macros_labels;
    string arquivo = arquivo_assembly.substr(0, arquivo_assembly.find(".asm"));

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
            linha = padronizar(linha);
            if(linha.empty()) continue;
            vector<std::string> palavras;
            string aux;
            split(linha, palavras);

            // Tratamento de labels
            if(palavras[0][palavras[0].length()-1] == ':'){
                aux = palavras[0].substr(0, palavras[0].find(':'));
                if(palavras.size() == 1){
                    do{
                        getline(arquivo_raw, linha);
                        linha = padronizar(linha);
                    }while(linha.empty());
                    split(linha, palavras);
                }
                tabela_equ[aux] = palavras[2];
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
            arquivo_preprocessado << "SECTION TEXT\n";

            while(getline(arquivo_raw, linha)){
                linha = padronizar(linha);
                if(linha.empty()) continue;
                vector<std::string> palavras;
                string aux;
                split(linha, palavras);

                // Trata diretiva IF
                if(palavras[0] == "IF"){
                    if(tabela_equ[palavras[1]] == "0"){
                        do{
                            getline(arquivo_raw, linha);
                            linha = padronizar(linha);
                        }while(linha.empty());
                        continue;
                    }else{
                        do{
                            getline(arquivo_raw, linha);
                            linha = padronizar(linha);
                        }while(linha.empty());
                        palavras.clear();
                        split(linha, palavras);
                        escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                    }
                }else

                // Tratamento de Labels
                if(palavras[0][palavras[0].length()-1] == ':'){
                    if( (int)palavras.size() == 1){
                        do{
                            getline(arquivo_raw, linha);
                            linha = padronizar(linha);
                        }while(linha.empty());
                        split(linha, palavras);
                    }

                        // Tratamento de Macros
                    if(palavras[1] == "MACRO"){
                        aux = palavras[0].substr(0, palavras[0].find(':'));

                        if((int)palavras.size() == 5){
                            // &a , &b
                            macros_labels[aux] = {palavras[2], palavras[4]};
                        }
                        else if((int)palavras.size() == 4){
                            // &a, &b ou &a ,&b
                            if(palavras[3][0] == ','){
                                macros_labels[aux] = {palavras[2].substr(0, palavras[2].find(',')), palavras[3].substr(1)};
                            } 
                            else{
                                macros_labels[aux] = {palavras[2].substr(0, palavras[2].find(',')), palavras[3]};
                            } 
                        }
                        else if((int)palavras.size() == 3){
                            // &a
                            macros_labels[aux] = {palavras[2]};
                        }
                        while(palavras[0] != "ENDMACRO"){
                            palavras.clear();   
                            do{
                                getline(arquivo_raw, linha);
                                linha = padronizar(linha);
                            }while(linha.empty());
                            split(linha, palavras);
                            if(palavras[0] != "ENDMACRO"){
                                macros[aux] = macros[aux] + escreve_macro(palavras);
                            }
                        }
                        palavras.clear();
                        
                    }else{
                        map<string, string>::iterator it_equ;

                        it_equ = tabela_equ.find(palavras[1]);
                        if(it_equ != tabela_equ.end()){
                            palavras[1] = it_equ->second;
                        }else if(palavras[1] == "CONST"){
                            it_equ = tabela_equ.find(palavras[2]);
                            if(it_equ != tabela_equ.end()){
                                palavras[2] = it_equ->second;
                            }
                        }
                        escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                    }

                    
                }else if(palavras.size() != 0){
                    map<string, string>::iterator it;
                    it = macros.find(palavras[0]);

                    // Caso ache uma label que referencia uma macro
                    if(it != macros.end()){
                        if((int)palavras.size() == 2){   
                            it->second = troca(it->second, macros_labels[palavras[0]][0], palavras[1]);
                        }
                        else if((int)palavras.size() == 3){
                            retira_virgulas(palavras);
                            it->second = substitui_labels(it->second, macros_labels[palavras[0]], palavras[1], palavras[2]);
                        }
                        else if((int)palavras.size() == 4){
                            it->second = substitui_labels(it->second, macros_labels[palavras[0]], palavras[1], palavras[3]);
                        }
                        arquivo_preprocessado << it->second;
                    }else{
                        escreve_linha_no_arquivo(palavras, arquivo_preprocessado);
                    }
                }              
            }   
        }
        arquivo_preprocessado.close();
        cout << "Arquivo \"" << arquivo << ".pre\" gerado!" << endl;
    }
    arquivo_raw.close();
}

#endif