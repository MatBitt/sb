#ifndef SEGUNDAPASSAGEM_H_INCLUDED
#define SEGUNDAPASSAGEM_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <fstream>
#include "utilidade.h"
#include "instrucoes.h"
#include "diretivas.h"
#define CODIGO 2

using namespace std;

void segunda_passagem(string arquivo, map<string, int> tabela_de_simbolos){

    fstream arquivo_pre;
    
    arquivo_pre.open(arquivo, ios::in);
    if(!arquivo_pre.is_open())
    {
        cout << "Erro ao abrir o arquivo pre processado na segunda passagem!" << endl;
        exit(0);
    }
    else{
        string linha;
        map<string, vector<int>> instrucoes = getInstrucoes();
        map<string, vector<int>> diretivas = getDiretivas();
        map<string, vector<int>>::iterator it;

        fstream arquivo_obj;
        string objeto = arquivo.substr(0, arquivo.find(".pre"));

        arquivo_obj.open(objeto + ".obj", ios::out);
        if(!arquivo_pre.is_open())
        {
            cout << "Erro ao abrir o arquivo objeto na segunda passagem!" << endl;
            exit(0);
        }

        else{

            // Remove Section Text
            getline(arquivo_pre, linha);

            while(getline(arquivo_pre, linha)){
                vector<std::string> palavras;
                string aux;
                split(linha, palavras);
                retira_virgulas(palavras);

                // Criterio de parada
                if(palavras[0] == "SECTION") break;

                // Caso seja label
                if(palavras[0][palavras[0].length()-1] == ':'){

                    it = instrucoes.find(palavras[1]);
                    if(palavras[1] == "COPY"){
                        arquivo_obj << it->second[CODIGO] << ' ';
                        arquivo_obj << tabela_de_simbolos[palavras[2]] << ' ' << tabela_de_simbolos[palavras[3]] << ' ';
                    }else if(palavras[1] == "STOP"){
                        arquivo_obj << it->second[CODIGO] << ' ';
                    }else{
                        arquivo_obj << it->second[CODIGO] << ' ';
                        arquivo_obj << tabela_de_simbolos[palavras[2]] << ' ';
                    }  
                }

                // Caso seja instrucao
                else{

                    it = instrucoes.find(palavras[0]);
                    if(palavras[0] == "COPY"){
                        arquivo_obj << it->second[CODIGO] << ' ';
                        arquivo_obj << tabela_de_simbolos[palavras[1]] << ' ' << tabela_de_simbolos[palavras[2]] << ' ';
                    }else if(palavras[0] == "STOP"){
                        arquivo_obj << it->second[CODIGO] << ' ';  
                    }else{
                        arquivo_obj << it->second[CODIGO] << ' ';  
                        arquivo_obj << tabela_de_simbolos[palavras[1]] << ' ';
                    }

                }
                
            }

            // Section Data
            while(getline(arquivo_pre, linha)){
                vector<std::string> palavras;
                string aux;
                split(linha, palavras);

                if(palavras[1] == "CONST") arquivo_obj << palavras[2] << ' ';
                else arquivo_obj << "0" << ' ';
            }

        }
        arquivo_obj.close();
        cout << "Arquivo \"" << objeto << ".obj\" gerado!" << endl;
    }
    arquivo_pre.close();
}

#endif