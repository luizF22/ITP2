#ifndef PALETA_H
#define PALETA_H
#include <string>

namespace pc{
class Cor {
    public:
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

class Cores {
    private:
    int quantidade;
    Cor cores[100];   
    double valores[100];

    public:
    Cores(int qtd, const Cor c[], const double v[]);
    bool carregarDeArquivos(const std::string& caminho);
    Cor obterCor(double valor) const;
    bool estaOrdenados() const;
};
}
#endif