#include "paleta.h"
#include <fstream>
#include <iostream>
using namespace pc;

Cores::Cores(int qtd, const Cor c[], const double v[]){
    quantidade = qtd;
    for (int i = 0; i < qtd; ++i) {
        cores[i] = c[i];
        valores[i] = v[i];
    }
}

Cor Cores::obterCor(double valor) const {
    for (int i = 0; i < quantidade - 1; ++i) {
        if (valor >= valores[i] && valor < valores[i + 1]) {
            return cores[i];
        }
    }
    return cores[quantidade - 1]; // Retorna a última cor se o valor for maior
}

bool Cores::estaOrdenados() const {
    for (int i = 0; i < quantidade - 1; ++i) {
        if (valores[i] >= valores[i + 1]) {
            return false;
        }
    }
    return true;
}

bool Cores::carregarDeArquivos(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) return false;
    arquivo >> quantidade;
    for (int i = 0; i < quantidade; ++i) {
        arquivo >> valores[i] >> cores[i].R >> cores[i].G >> cores[i].B;
    }
    arquivo.close();
    return true;
}

