#ifndef INSTRUCOES_H_INCLUDED
#define INSTRUCOES_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

map<string, vector<int>> getInstrucoes(){
    map<string, vector<int>> instrucao;
    // instrucao = {operando, tamanho, código}
    instrucao["ADD"] = {1, 2, 1};
    instrucao["SUB"] = {1, 2, 2};
    instrucao["MULT"] = {1, 2, 3};
    instrucao["DIV"] = {1, 2, 4};
    instrucao["JMP"] = {1, 2, 5};
    instrucao["JMPN"] = {1, 2, 6};
    instrucao["JMPP"] = {1, 2, 7};
    instrucao["JMPZ"] = {1, 2, 8};
    instrucao["COPY"] = {2, 3, 9};
    instrucao["LOAD"] = {1, 2, 10};
    instrucao["STORE"] = {1, 2, 11};
    instrucao["INPUT"] = {1, 2, 12};
    instrucao["OUTPUT"] = {1, 2, 13};
    instrucao["STOP"] = {0, 1, 14};
    return instrucao;
}

#endif