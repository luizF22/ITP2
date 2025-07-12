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
     double valoresTeste[28] = {
    0.037136, 0.037137, 0.074074, 0.111111, 0.148148,
    0.185185, 0.222222, 0.259259, 0.296296, 0.333333,
    0.370370, 0.407407, 0.444444, 0.481481, 0.518519,
    0.555556, 0.592593, 0.629630, 0.666667, 0.703704,
    0.740741, 0.777778, 0.814815, 0.851852, 0.888889,
    0.925926, 0.962963, 1.000000
};

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
