#ifndef UTILIDADE_H_INCLUDED
#define UTILIDADE_H_INCLUDED

#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template <class Container>

void split(const string& linha, Container& cont){
    istringstream iss(linha);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}

void escreve_linha_no_arquivo(vector<string> palavras, ofstream& arquivo){
    int i;
    for(i = 0; i< (int) palavras.size(); i++){
        if(palavras[i] == "+"){
            int aux = stoi(palavras[i+1]);
            aux = aux*4;
            palavras[i+1] = to_string(aux);
        }
        if(i< (int) palavras.size() - 1){
            if(palavras[i+1] == ","){
                arquivo << palavras[i];
                continue;
            }
            else if(palavras[i+1][0] == ','){
                arquivo << palavras[i] << ',' << ' ';
                palavras[i+1] = palavras[i+1].substr(1);
                continue;
            }
            else{
                arquivo << palavras[i] + ' ';
                continue;
            }
        }
        arquivo << palavras[i];
    }
    if(palavras[i-1] != "\n") arquivo << endl;
}

void retira_virgulas(vector<string>& palavras){
    size_t i;
    for(i=0; i<palavras.size(); i++){
        if(palavras[i][0] == ','){
            palavras[i] = palavras[i].substr(1);
        }else{
            palavras[i] = palavras[i].substr(0,palavras[i].find(','));
        }
    }
}

string troca(string macro, const string& label, const string& valor){
    size_t start_pos = 0;
    while((start_pos = macro.find(label, start_pos)) != string::npos){
        macro.replace(start_pos, label.length(), valor);
        start_pos += valor.length();
    }
    return macro;
}

#endif