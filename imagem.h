#ifndef IMAGEM_H
#define IMAGEM_H
#include "paleta.h"
namespace img {
    class Imagem {
private:
        int largura;
        int altura;
        pc::Cor* pixels; //pra ser alocado dinamicamente o array de pixels
public:
/**
 * @brief construtor da classe Imagem
 * @param largura
 * 
 * 
 */
        Imagem(int largura, int altura); //cria img com alt e larg especificadas
        ~Imagem(); //destrutor para liberar a memoria
        void DefPix(int x, int y, pc::Cor cor); //def a cor de um pixel em determinadas coordenadas
        pc::Cor obtPix(int x, int y) const; //obtem a cor de um pixel em deteminadas coordenadas
        bool salvar(const std::string& nomeArquivo) const; //salva a img em um arquivo ppm P3
};
}
#endif