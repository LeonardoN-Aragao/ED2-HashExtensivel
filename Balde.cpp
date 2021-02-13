#include "Balde.h"

Balde::Balde(int tam){
    info.resize(tam);
    d_local = 1;
    quantidade = 0;
}

Balde::~Balde(){
    info.clear();
}