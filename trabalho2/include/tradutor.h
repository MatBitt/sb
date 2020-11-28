#include <iostream>
#include <string.h>
#include <map>
#include <iterator>
#include <fstream>
#include "utilidade.h"
#include "instrucoes.h"

using namespace std;

void traduz_ia32(string arquivo_assembly){

    string arquivo_raw = arquivo_assembly.substr(0, arquivo_assembly.find(".asm"));
    fstream arquivo;
    arquivo.open(arquivo_raw + ".asm", ios::in);

    if(!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo original!" << endl;
        exit(0);
    }
    else{
        string linha;
        while(getline(arquivo, linha)){
            vector<std::string> palavras;
            string aux;
            split(linha, palavras);
            
        }
    }
}

void troca_instrucao(vector<std::string> palavras){
    map<string, int> instrucoes;
    instrucoes = getInstrucoes();
    string traducao;

    for(auto i=0; i<palavras.size(); i++){

        if(palavras[i][palavras[i].length()-1] == ':'){
            traducao = palavras[i] + ' ';
            continue;
        }

        switch(instrucoes[palavras[i]]){
            case 1: // ADD
                traducao = traducao + "add EAX, [" + palavras[i+1] + "]\n";
                break;

            case 2: // SUB
                traducao = traducao + "sub EAX, [" + palavras[i+1] + "]\n";
                break;

            case 3: // MULT
                break;

            case 4: // DIV
                break;

            case 5: // JMP
                break;

            case 6: // JMPN
                break;

            case 7: // JMPP
                break;

            case 8: // JMPZ
                break;

            case 9: // COPY
                traducao = traducao + "mov EBX, [" + palavras[i+1].substr(0, palavras[i+1].find(',')) + "]\n";
                traducao = traducao + "mov [" + palavras[i+2] + "], EBX";
                break;

            case 10: // LOAD
                traducao + "mov EAX, [" + palavras[i+1] + "]\n";
                break;

            case 11: // STORE
                break;
            case 12: // INPUT
                break;
            case 13: // OUTPUT
                break;
            case 14: // STOP
                break;
        }
        break; 
    }

    // Escreve traducao no arquivo final
}