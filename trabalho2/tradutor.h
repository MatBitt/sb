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
void subrotinas_ia32(ofstream& arquivo);

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

    subrotinas_ia32(arquivo_traduzido);

    // section data
    string bss, data;
    bss = "section .bss\n";
    bss = bss + "_aux: resd 101\n";
    data = "section .data\n";
    data = data + "_menos: db '-'\n";
    data = data + "_mais: db '+'\n";
    data = data + "_enter: db 0dh, adh \n";
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
                traducao = traducao + "push dword ";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "\n";
                traducao = traducao + "_call LeeInteiro\n";
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
                traducao = traducao + "push dword [";
                for(++i; i<palavras.size(); i++){
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                traducao = traducao + "_LeerChar";
                break;
            case 16: // C_OUTPUT
                for(; i<palavras.size(); i++){
                    traducao = traducao + palavras[i] + ' ';
                }
                traducao = traducao + "  ----- NAO TRADUZIDO\n";
                break;
            case 19: // S_INPUT
                traducao = traducao + "push dword ["; // End de memoria
                for(++i; i<palavras.size(); i++){
                    if(palavras[i][palavras[i].length()-1] == ','){
                        traducao = traducao + palavras[i].substr(0, palavras[i].find(","));
                        break;
                    }
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                traducao = traducao + "push dword " + palavras[++i] + "\n";
                traducao = traducao + "call _LeerString\n";
                break;
            case 20: // S_OUTPUT
                traducao = traducao + "push dword ["; // End de memoria
                for(++i; i<palavras.size(); i++){
                    if(palavras[i][palavras[i].length()-1] == ','){
                        traducao = traducao + palavras[i].substr(0, palavras[i].find(","));
                        break;
                    }
                    traducao = traducao + palavras[i];
                }
                traducao = traducao + "]\n";
                traducao = traducao + "push dword " + palavras[++i] + "\n"; // Tamanho
                traducao = traducao + "call _EscreverString\n";
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
    arquivo << "_LeerInteiro:\n";
    arquivo << "enter 0, 0\n";
    arquivo << "push EAX\n";
    arquivo << "push EBX\n";
    arquivo << "push ECX\n";
    arquivo << "push EDX\n";
    arquivo << "push ESI\n";
    arquivo << "call LeerString _aux, 5\n";
    arquivo << "movz EAX, byte [_aux]\n";
    arquivo << "movz EBX, byte [_menos]\n";
    arquivo << "cmp EAX, EBX\n";
    arquivo << "jne _positivo\n";

    arquivo << "_negativo:\n";
    arquivo << "mov EBX, _aux\n";
    arquivo << "mov EDX, word [_enter]\n";
    arquivo << "mov ECX, 2\n";
    arquivo << "sub EAX, 30h\n";
    arquivo << "imul -1\n";   //////////// TESTAAAAR ISSSO AQUIIIII
    arquivo << "inc EBX\n";
    arquivo << "cmp word [EBX], EDX\n"; 
    arquivo << "je _fimloop\n";
    arquivo << "jmp _loop:\n";

    arquivo << "_positivo:\n";
    arquivo << "mov EBX, _aux\n";
    arquivo << "mov EDX, word [_enter]\n";
    arquivo << "mov ECX, 2\n";
    arquivo << "sub EAX, 30h\n";
    arquivo << "inc EBX\n";
    arquivo << "cmp word [EBX], EDX\n"; 
    arquivo << "je _fimloop\n";

    arquivo << "_loop:\n";
    arquivo << "mult EAX, 10\n";
    arquivo << "movz ESI, byte [EBX]\n";
    arquivo << "sub ESI, 30h\n";
    arquivo << "add EAX, ESI";
    arquivo << "inc EBX\n";
    arquivo << "cmp word [EBX], EDX\n";
    arquivo << "je _fimloop\n";
    arquivo << "loop _loop\n";

    arquivo << "_fimloop:\n";
    arquivo << "mov dword [EBP + 8], EAX";
    arquivo << "pop ESI\n";
    arquivo << "pop EDX\n";
    arquivo << "pop ECX\n";
    arquivo << "pop EBX\n";
    arquivo << "pop EAX\n";
    arquivo << "leave\n";
    arquivo << "ret 4\n";


    arquivo << "_EscreverInteiro:\n";
    arquivo << "ret\n";


    arquivo << "_LeerChar:\n";
    arquivo << "enter 0, 0\n";
    arquivo << "push EAX\n";
    arquivo << "push EBX\n";
    arquivo << "push ECX\n";
    arquivo << "push EDX\n";
    arquivo << "mov EAX, 3\n";
    arquivo << "mov EBX, 0\n";
    arquivo << "mov ECX, _aux\n";
    arquivo << "mov EDX, 2\n";
    arquivo << "int 80h\n";
    arquivo << "movz dword [EBP + 8], byte [_aux]\n"; // TESTAAAAAARRR
    arquivo << "pop EDX\n";
    arquivo << "pop ECX\n";
    arquivo << "pop EBX\n";
    arquivo << "pop EAX\n";
    arquivo << "leave\n";
    arquivo << "ret 4\n";


    arquivo << "_EscreverChar:\n";
    arquivo << "enter 0, 0\n";
    arquivo << "push EAX\n";
    arquivo << "push EBX\n";
    arquivo << "push ECX\n";
    arquivo << "push EDX\n";
    arquivo << "mov EAX, 4\n";
    arquivo << "mov EBX, 1\n";
    arquivo << "mov ECX, dword [EBP + 8]\n";
    arquivo << "mov EDX, 1\n";
    arquivo << "int 80h\n";
    arquivo << "pop EDX\n";
    arquivo << "pop ECX\n";
    arquivo << "pop EBX\n";
    arquivo << "pop EAX\n";
    arquivo << "ret 4\n";


    arquivo << "_LeerString:\n";
    arquivo << "enter 0, 0\n";
    arquivo << "push EAX\n";
    arquivo << "push EBX\n";
    arquivo << "push ECX\n";
    arquivo << "push EDX\n";
    arquivo << "mov EAX, 3\n";
    arquivo << "mov EBX, 0\n";
    arquivo << "mov ECX, dword [EBP + 12]\n";
    arquivo << "mov EDX, dword [EBP + 8]\n";
    arquivo << "int 80h\n";
    arquivo << "pop EDX\n";
    arquivo << "pop ECX\n";
    arquivo << "pop EBX\n";
    arquivo << "pop EAX\n";
    arquivo << "leave\n";
    arquivo << "ret 8\n";


    arquivo << "_EscreverString:\n";
    arquivo << "enter 0, 0\n";
    arquivo << "push EAX\n";
    arquivo << "push EBX\n";
    arquivo << "push ECX\n";
    arquivo << "push EDX\n";
    arquivo << "mov EAX, 4\n";
    arquivo << "mov EBX, 1\n";
    arquivo << "mov ECX, dword [EBP + 12]\n";
    arquivo << "mov EDX, dword [EBP + 8]\n";
    arquivo << "int 80h\n";
    arquivo << "pop EDX\n";
    arquivo << "pop ECX\n";
    arquivo << "pop EBX\n";
    arquivo << "pop EAX\n";
    arquivo << "leave\n";
    arquivo << "ret 8\n";
    
}