#ifndef PALETA_H
#define PALETA_H
#include <string>
class Pixel {
    public:
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

class Cores {
    private:
    int quantidade;
    Pixel cores[100]; 
    double valores[100];

    public:
    Cores(int qtd, const Pixel c[], const double v[]);
    bool carregarDeArquivos(const std::string& caminho);
    Pixel obterCor(double valor) const;
    bool estaOrdenados() const;
};

#endif