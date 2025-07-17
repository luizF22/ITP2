#ifndef PALETA_H//evitar que leia-se 2x os arquivos quando forem trazidos pros .cpp (caso ja tenha sido def em outra inclusão)
#define PALETA_H
#include <string>

namespace pc{//evitar conflitos com nomes de outros arquivos
struct Cor {//facil acesso para uso posterior (como um cor.R = 255), n há necessidade de ser classe
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

class Cores {   
    private://garantir que em outros códigos esses atributos n sejam alterados de forma alguma
    int quantidade;
    Cor cores[100];   
    double valores[100];

    public://vão ser chamados futuramente em outros códigos
    Cores(int qtd, const Cor c[], const double v[]);//ini a paleta com cores e valores pre-def
    bool carregarDeArquivos(const std::string& caminho);//carregar as cores de um arquivo externo
    Cor obterCor(double valor) const;//mapear um valor para cor da paleta
    bool estaOrdenados() const;//necessario pra que o obterCor funcione (ordem crescente)
};
}
#endif