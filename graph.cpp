#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void lerInfo(string *informacao){

    ifstream arq("bar-n100-1.txt");
    string linha;
    int cont = 0;
    
    while(getline(arq, linha)){
        istringstream iss(linha);
        string palavra; 

        size_t pos = linha.find(": ");
        if(pos != -1){
            string variavel = linha.substr(pos+1);
            informacao[cont] = variavel;
            cont++;
        }
    }
}

void lerNodes(double *nodes, int size){
    ifstream arq("bar-n100-1.txt");
    string linha;
    
    while(getline(arq, linha)){
        istringstream iss(linha);
        string palavra;

        size_t pos1 = linha.find('NODES');

        while(getline(arq, linha)){
            size_t pos2 = linha.find(' ');
            if(pos2 != -1){
                string variavel = linha.substr(pos2 + 1);
                for(int i=0; i < size; i++){
                    for(int j=0; j<9; j++){
                        nodes[i][j] = stod(variavel);
                    }
                }
            }
        }
    }
}

void lerEdges(int *edges, int size){
    ifstream arq("bar-n100-1.txt");
    string linha;

    while(getline(arq, linha)){
        istringstream iss(linha);
        string palavra;

        size_t pos1 = linha.find('EDGES');

        while(getline(arq, linha)){
            size_t pos2 = linha.find(' ');
            if(pos2 != -1){
                string variavel = linha.substr(pos2 + 1);
                for(int i = 0; i < size; i++){
                    for(int j = 0; j < size; j++){
                        edges[i][j] = stoi(variavel);
                    }
                }
            }
        }
    }
}

void condicoesEntrega(){

    //

}

int main(){

    string informacao[10];
    
    lerInfo(informacao);

    int size = stoi(informacao[4]);

    double nodes[size][8];
    lerNodes(nodes, size);

    int edges[size][size];
    lerEdges(edges, size);

    return 0;
}
