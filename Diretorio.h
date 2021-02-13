#include <string>
#include <vector>
#include "Balde.h"

class Diretorio {
    public:
        Diretorio(int tam,int b);
        ~Diretorio();

        void inserir(std::string chave);
        int buscarPosicao(std::string chave);
        bool buscar(std::string chave);
        void dividirBaldes(int posicao);
        void duplicarDiretorio();
        float fatorCarga();

        int tamanho;
        int d_global;
        int quant_baldes;
        std::vector<Balde *> dados;
};