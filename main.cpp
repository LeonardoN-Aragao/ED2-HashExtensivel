#include <iostream>
#include <math.h>
#include "Diretorio.h"

using namespace std;

int main() {
    
    int tam;
    int bits;

    cout<<"Insira o tamanho dos baldes: ";
    cin>>tam;
    cout<<"Insira o numero de bits: ";
    cin>>bits;

    // TESTES

    Diretorio d(tam,bits);
    d.inserir("a"); 
    d.inserir("b");
    cout<<"Fator de Carga: "<<d.fatorCarga()<<endl;
    d.inserir(".");
    d.inserir(";");
    cout<<"Fator de Carga: "<<d.fatorCarga()<<endl;
    d.inserir("]");
    d.inserir(":");
    d.inserir("c");
    d.inserir("d");
    cout<<"Fator de Carga: "<<d.fatorCarga()<<endl;


    srand(time(NULL));
    int N = 1000;
    for(int i = 0; i < N; i ++){
        string teste = std::to_string(rand()%N);
        d.inserir(teste);
        if(i% 10 == 0)
            cout<<"Fator de Carga: "<<d.fatorCarga()<<endl;
    }
    

    return 0;
}