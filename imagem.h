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
/**
 * @brief construtor da classe Imagem que aloca memoria para a imagem
 * @param largura largura da imagem em pixels
 * @param altura altura da imagem em pixels
 */
        Imagem(int largura, int altura);
/**
 * @brief destrutor de classe imagem que libera a memoria criada pelo construtor
 */
        ~Imagem();
/**
 * @brief define a cor de um pixel em coordenadas especificas
 * @param x coordenada x (coluna) do pixel
 * @param y coordenada y (linha) do pixel
 * @param cor o objeto Cor a ser atribuido ao pixel
 */
        void DefPix(int x, int y, pc::Cor cor);
/**
 * @brief obtem a cor de um pixel em uma determinada coordenada
 * @param x x (coluna) do pixel
 * @param y y (linha) do pixel
 * @return o objeto Cor do pixel em coordenadas dadas
 */
        pc::Cor obtPix(int x, int y) const;
/**
 * @brief salva a imagem em um arquivo ppm (P3)
 * @param nomeArquivo o caminho e nome do arquivo onde a imagem será salva
 * @return retora true se o arquivo foi salvo com sucesso, false se houve erros
 */
        bool salvar(const std::string& nomeArquivo) const;
};
}
#endif
