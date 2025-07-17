#ifndef IMAGEM_H
#define IMAGEM_H
#include "paleta.h"
namespace img { // criando pra usar no .cpp
    class Imagem {
private:
        int largura;
        int altura;
        pc::Cor* pixels; //ponteiro para o primeiro elemento de um array dinamico, que vai ser repleto de elementos do tipo Cor
        //pra ser alocado dinamicamente o array de pixels
public:
        Imagem(int largura, int altura); // construtor para cria imagem com alt e larg especificadas
        ~Imagem(); //destrutor para liberar a memoria
        void DefPix(int x, int y, pc::Cor cor); //def a cor de um pixel em determinadas coordenadas
        pc::Cor obtPix(int x, int y) const; //obtem a cor de um pixel em deteminadas coordenadas
        bool salvar(const std::string& nomeArquivo) const; //salva a img em um arquivo ppm P3
};
}
#endif
