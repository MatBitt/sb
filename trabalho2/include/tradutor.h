#include <iostream>
#include <string.h>
#include <map>
#include <iterator>
#include <fstream>
#include "utilidade.h"
#include "instrucoes.h"

using namespace std;

string obtem_traducao(vector<string> palavras);
void section_data(vector<string> palavras, string& bss, string& data);

void traducao(string arquivo_assembly){

    string arquivo_raw = arquivo_assembly.substr(0, arquivo_assembly.find(".asm"));
    fstream arquivo;
    arquivo.open(arquivo_raw + ".pre", ios::in);

    if(!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo preprocessado!" << endl;
        exit(0);
    }
    ofstream arquivo_traduzido(arquivo_raw + ".s");

    if(!arquivo_traduzido.is_open())
    {
        cout << "Erro ao abrir o arquivo final!" << endl;
        exit(0);
    }

    arquivo_traduzido << "global _start\n";
    arquivo_traduzido << "section .text\n";
    arquivo_traduzido << "_start:\n";

    string linha;
    getline(arquivo, linha);
    while(getline(arquivo, linha)){
        vector<string> palavras;
        string aux;
        split(linha, palavras);
        if(palavras[0] == "SECTION") break;
        linha = obtem_traducao(palavras);
        arquivo_traduzido << linha; 
    }

    // section data
    string bss, data;
    bss = "section .bss\n";
    data = "section .data\n";
    while(getline(arquivo, linha)){
        vector<string> palavras;
        string aux;
        split(linha, palavras);
        section_data(palavras, bss, data);
    }
    arquivo_traduzido << bss << data;
    arquivo.close();
    arquivo_traduzido.close();
    cout << "Arquivo gerado!" << endl;
}

string obtem_traducao(vector<string> palavras){
    map<string, int> instrucoes;
    instrucoes = getInstrucoes();
    string traducao;

    for(size_t i=0; i<palavras.size(); i++){

        if(palavras[i][palavras[i].length()-1] == ':'){
            traducao = palavras[i] + ' ';
            continue;
        }

        switch(instrucoes[palavras[i]]){
            case 1: // ADD
                traducao = traducao + "add EAX, dword [";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                break;

            case 2: // SUB
                traducao = traducao + "sub EAX, dword [";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                break;

            case 3: // MULT
                traducao = traducao + "imul dword [";
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                break;

            case 4: // DIV
                traducao = traducao + "cdq\n";
                traducao = traducao + "idiv dword [";
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                break;

            case 5: // JMP
                traducao = traducao + "jmp ";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "\n";
                break;

            case 6: // JMPN
                traducao = traducao + "cmp EAX, 0\n";
                traducao = traducao + "jl ";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "\n";
                // usar cmp em todos os jmps
                break;

            case 7: // JMPP
                traducao = traducao + "cmp EAX, 0\n";
                traducao = traducao + "jg ";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "\n";
                break;

            case 8: // JMPZ
                traducao = traducao + "cmp EAX, 0\n";
                traducao = traducao + "je ";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "\n";
                break;

            case 9: // COPY
                traducao = traducao + "mov EBX, dword [";
                if(palavras[i+2] == "+"){
                    traducao = traducao + palavras[i+1] + palavras[i+2] + palavras[i+3].substr(0, palavras[i+3].find(','));
                    i+=3;
                }else{
                    traducao = traducao + palavras[i+1].substr(0, palavras[i+1].find(','));
                    i++;
                }
                traducao = traducao + "]\n";

                traducao = traducao + "mov dword [";

                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "], EBX\n";;

                break;

            case 10: // LOAD
                traducao = traducao + "mov EAX, dword [";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                break;

            case 11: // STORE
                traducao = traducao + "mov dword [";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "], EAX\n";
                break;
            case 12: // INPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
            case 13: // OUTPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
            case 14: // STOP
                traducao = traducao + "mov eax, 1\n";
                traducao = traducao + "mov ebx, 0\n";
                traducao = traducao + "int 80h\n";
                break;
            case 15: // C_INPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
            case 16: // C_OUTPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
            case 19: // S_INPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
            case 20: // S_OUTPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
        }
    }
    return traducao;
}

void section_data(vector<string> palavras, string& bss, string& data){
    if(palavras[1] == "CONST"){
        // DATA
        palavras[1] = "dd";
        for(size_t i = 0; i<palavras.size(); i++){
            data = data + palavras[i] + ' ';
        }
        data = data + "\n";
    }
    else{
        // BSS
        palavras[1] = "resd";
        for(size_t i = 0; i<palavras.size(); i++){
            bss = bss + palavras[i] + ' ';
        }
        bss = bss + "\n";
    }
}

void subrotinas_ia32(ofstream& arquivo){
    arquivo << "LeerInteiro:";
    arquivo << "ret";
    arquivo << "EscreverInteiro:";
    arquivo << "ret";
    arquivo << "LeerChar:";
    arquivo << "";
    arquivo << "ret";
    arquivo << "EscreverChar:";
    arquivo << "ret";
    arquivo << "LeerString:";
    arquivo << "ret";
    arquivo << "EscreverString:";
    arquivo << "ret";
}