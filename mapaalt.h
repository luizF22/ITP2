#ifndef MAPA_ALT_H
#define MAPA_ALT_H
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "paleta.h"
#include "imagem.h"

namespace mapa {
class MDA {
private:
        float** matriz; //matriz das altitudes (uma matriz 2d dinamica, ainda desconhecida)
        int dimensao;//tamanho da matriz (9 se for 9x9 por ex)
/**
 * @brief etapa diamond calcula o ponto médio de um quadrado
 * @param x coordenada x do canto superior esquerdo do quadrado
 * @param y coordenada y do canto superior esquerdo do quadrado
 * @param tamanho o lado do quadrado
 * @param deslocamento a magnitude do deslocamento aleatório a ser aplicado na altitude
 */
        void etapaDiamond(int x, int y, int tamanho, float deslocamento);
/**
 * @brief etapa square vai calcular o ponto médio das arestas
 * @param x coordenada x do centro do losango (feito pela etapa diamond)
 * @param y coordenada y do centro do losango (feito pela etapa diamond)
 * @param tamanho distancia do centro a um dos vértices do losango
 * @param deslocamento magnitude do deslocamento aleatório que será aplicado na altitude
 */
        void etapaSquare(int x, int y, int tamanho, float deslocamento);
public:
/**
 * @brief construtor de classe MDA que prepara a matriz de altitude
 * @param n o expoente que define a dimensão do mapa (que será 2^n + 1)
 */
        MDA(int n);
/**
 * @brief destrutor para liberar a memória
 */
        ~MDA();
/**
 * @brief gera o relevo do mapa usando o algoritmo diamond-square
 * @param rugosidade fator para controlar a aspereza e variação do terreno gerado
 */
        void gerar(float rugosidade);
/**
 * @brief ir atrás da altitude específica de um ponto no mapa
 * @param lin linha da matriz
 * @param col coluna da matriz
 * @return o valor de ponto flutuante da altitude na posição especificada
 */
        float getAlt(int lin, int col);
/**
 * @brief retorna a dimensão da matriz do mapa (largura/altura)
 * @return o tamanho da dimensão do mapa
 */
        int getDim();
/**
 * @brief salva os dados brutos da matriz de altitudes num arquivo txt
 * @param nomearquivo o nome do arquivo que os dados serão salvos
 */
        void salvar(const std::string& nomearquivo);
/**
 * @brief carrega um mapa de altitudes a partir de um arquivo txt
 * @param nomearquivo nome do arquivo de onde os dados serão lidos
 */
        void ler(const std::string& nomearquivo);
/**
 * @brief gera uma representação visual do mapa de altitudes como um objeto Imagem
 * @param paleta a paleta de cores a ser usada para mapear altitudes para cores
 * @param fatorsombra fator para aplicar efeito de sombreamento
 * @return objeto do tipo img::Imagem, colorido e sombreado de acordo com o relevo
 */
        img::Imagem gerarImagem(const pc::Cores& paleta, float fatorsombra) const;
};

}
#endif