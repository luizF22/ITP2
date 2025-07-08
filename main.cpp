#include "paleta.h"
#include <iostream>

int main() {
    // Usando o namespace "pc"
    pc::Cor vermelho = {255, 0, 0};
    pc::Cor verde = {0, 255, 0};
    pc::Cor cores[] = {vermelho, verde};
    double valores[] = {0.0, 10.0};

    pc::Cores paleta(2, cores, valores);  // Construtor
    pc::Cor cor = paleta.obterCor(5.0);

    std::cout << "Cor: R=" << (int)cor.R << " G=" << (int)cor.G << " B=" << (int)cor.B << std::endl;
    return 0;
}