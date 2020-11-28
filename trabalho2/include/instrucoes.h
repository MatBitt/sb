#ifndef INSTRUCOES_H_INCLUDED
#define INSTRUCOES_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

map<string, int> getInstrucoes(){
    map<string, int> instrucao;
    // instrucao = {código}
    instrucao["ADD"] = 1;
    instrucao["SUB"] = 2;
    instrucao["MULT"] = 3;
    instrucao["DIV"] = 4;
    instrucao["JMP"] = 5;
    instrucao["JMPN"] = 6;
    instrucao["JMPP"] = 7;
    instrucao["JMPZ"] = 8;
    instrucao["COPY"] = 9;
    instrucao["LOAD"] = 10;
    instrucao["STORE"] = 11;
    instrucao["INPUT"] = 12;
    instrucao["OUTPUT"] = 13;
    instrucao["STOP"] = 14;
    return instrucao;
}

#endif