#include <iostream>
#include <string>
#include <bitset>
#include <math.h>
#include "Diretorio.h"

Diretorio::Diretorio(int tam, int b){
    
    d_global = b;
    tamanho = tam;
    dados.resize(4);
    quant_baldes = 1;

    // Cria um balde e faz todas posições apontarem pra ele
    Balde * aux = new Balde(tamanho);
    for(int i = 0; i < dados.size(); i ++)
        dados[i] = aux;
}

Diretorio::~Diretorio(){

    for(int i = 0; i < dados.size(); i ++)
        dados[i]->info.clear();

    dados.clear();
}

//transforma a chave para bitset
std::string func_hash (std::string chave){
    /*
    for (std::size_t i = 0; i < cahve.size(); ++i){
      cout << bitset<8>(myString.c_str()[i]) << endl;
    }*/
    return std::bitset<8>(chave.c_str()[0]).to_string();
}

void Diretorio::inserir(std::string chave){

    if(buscar(chave)){
        std::cout<<"Chave "<<chave<<" já inserida!\n";
        return;
    }

    int posicao = buscarPosicao(chave);

    // Se não tem espaço no balde
    if(dados[posicao]->quantidade == tamanho){ //ultima posicao != vazia
        if(d_global == dados[posicao]->d_local)
            duplicarDiretorio();

        dados[posicao]->d_local++;
        dividirBaldes(quant_baldes-1);
    }

    // Insere no balde
    dados[posicao]->info[dados[posicao]->quantidade] = chave;
    dados[posicao]->quantidade++;
}

void Diretorio::dividirBaldes(int posicao){

    int nova_posicao = posicao + 1;
    Balde * b = new Balde(tamanho);

    //fazer todos apos nova_posicao apontarem para o ultimo balde
    for(int i = nova_posicao; i < dados.size(); i++)
        dados[i] = b;

    for(int i = 0; i < tamanho; i++){
        // IF TINHA QUE TA NO OUTRO BALDE
        if(buscarPosicao(dados[posicao]->info[i]) == nova_posicao){
            //adiciona no novo
            dados[nova_posicao]->info[dados[nova_posicao]->quantidade] = dados[posicao]->info[i];
            // apaga do outro
            for(int j = i; j < tamanho-1; j++)
                dados[posicao]->info[i] = dados[posicao]->info[i+1];
            
            dados[posicao]->info[tamanho-1] = "";

            //Atualiza a quantidade de informação no balde
            dados[nova_posicao]->quantidade++;
            dados[posicao]->quantidade--;
        }
    }
    dados[nova_posicao]->d_local++;
    quant_baldes++;
}

void Diretorio::duplicarDiretorio(){
    
    std::vector<Balde *> aux;
    aux.resize(dados.size()*2);

    for(int i = 0; i < dados.size(); i ++)
        aux[i] = dados[i];

    dados = aux;

    //fazer todos novos apos ultimo apontarem para o ultimo balde
    for(int i = dados.size()/2; i < dados.size(); i++)
        dados[i] = dados[quant_baldes-1];

    d_global++;
}

bool Diretorio::buscar(std::string chave){

    int posicao = buscarPosicao(chave);

    for(int i = 0; i < tamanho; i++){
        if(dados[posicao]->info[i] == chave)
            return true;
    }

    return false;
}

int Diretorio::buscarPosicao(std::string chave){

    // Pega posicao utilizando func_hash(chave)
    std::string h = func_hash(chave);

    // bits a esquerda
    std::string bitsMaisEsquerda;
    for(int i = 0; i < d_global; i++)
        bitsMaisEsquerda += h[i];
    
    int codigo = stoi(bitsMaisEsquerda);

    //Transforma de binario para inteiro
    int decimal = 0;
    for(int i = 0; codigo > 0; i++)
    {
        decimal = decimal + pow(2, i) * (codigo % 10);
        codigo = codigo / 10;
    }

    return decimal%dados.size();
}

float Diretorio::fatorCarga(){ 

    int quant = 0;

    for(int i = 0; i < quant_baldes; i++){
        quant += dados[i]->quantidade;
    }

    return (float) quant/(tamanho*quant_baldes);
}

