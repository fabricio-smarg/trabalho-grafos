/*
 *  Grupo: 
 *      Fabrício Alves Smargiasse - 202020117
 *      Otávio Rodrigues de Faria - 202020784
 *      Weverton Andrade Ferreira - 202020782
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef pair<int, int> coleta; 
typedef pair<int, int> entrega;

struct caminhao{
    int capacidade;
};

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

    /*
    
    a ideia era ter varias funções de verificação, uma para cada condição e a cada movimento
    do caminhão, ou atualização da rota haveria uma checagem da da matriz "edgesVisitados" e 
    sempre quando chegar num ponto de coleta ou há a checagem tanto da capacidade do caminhão, 
    mas primeiramente se o ponto de entrega não foi visitado ainda. Após essas duas checagems 
    seria feito uma confirmação se é possivel entregar dentro da janela de tempo, sendo possivel
    o caminhão voltar a tempo ao ponto de origem. 
    */

    //A principio seriam feitos três funções: 
    //1 - Uma para chegar a precedencia de coleta e entrega e a obrigadotoriedade e exclusividade de visita.
    bool precedenciaObrigatoriedade(int *edgesVisitados, pair<int, int> x){
        if(edgesVisitados[x.first][x.second] == 1)
            return false;
        else 
            return true; 
    }
    //2 - Uma para calcular se é possivel executar toda movimentação dentro do regulamento da janela de tempo e, 
    //    origem e horario de serviço.
    
    bool janelaTempo(int *informacao[], int tempoTotalGasto, int tempoNovaColeta){// origem e horario de serviço && janela de tempo (predendemos ir atualizando o tempo) 
        if((tempoTotalGasto + tempoNovaColeta <= informacao[8]) and (tempoNovaColeta - informacao[7] >= 0))
            return true;
        else 
            return false;

    }
    
    //3 - E uma terceira para calcular a capacidade do veiculo e a obrigatoriedade do atendimento do serviço ser feita 
    //    pelo mesmo veiculo. 
    bool capacidadeVeiculo(caminhao x, int novaCarga, int *informacao[], int *edgesVisitados [][], int coord1, int coord2){
         if(x.capacidade + novaCarga <= informacao[9]) and (edgesVisitados[coord1][coord2] != 1)
            return true;
         else 
            return false;
}

int main(){

    string informacao[9];
    
    lerInfo(informacao);

    int size = stoi(informacao[4]);

    double nodes[size][8];
    lerNodes(nodes, size);

    int edges[size][size];
    lerEdges(edges, size);

    int edgesVisitados[size][size];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            edgesVisitados[i][j] = 0;
        }
    }

    return 0;
}
