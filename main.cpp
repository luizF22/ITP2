#include "paleta.h"
#include <iostream>
#include <iomanip> // std::setprecision

int main() {
    pc::Cores paleta(0, nullptr, nullptr);  // inicialização vazia

    if (!paleta.carregarDeArquivos("paleta.txt")) {
        std::cerr << "Erro ao carregar o arquivo da paleta.\n";
        return 1;
    }

    // Verifica se os valores estão ordenados
    if (!paleta.estaOrdenados()) {
        std::cerr << "Os valores da paleta não estão ordenados!\n";
        return 1;
    } else {
        std::cout << "Paleta carregada com sucesso e está ordenada.\n";
    }

    // Testa alguns valores
    double valoresTeste[] = { 0.0, 0.25, 0.5, 0.75, 1.0 };

    for (double v : valoresTeste) {
        pc::Cor cor = paleta.obterCor(v);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Valor " << v << " => RGB("
                  << static_cast<int>(cor.R) << ", "
                  << static_cast<int>(cor.G) << ", "
                  << static_cast<int>(cor.B) << ")\n";
    }

    return 0;
}
