#ifndef MAPA_ALT_H
#define MAPA_ALT_H
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

namespace mapa {
class MDA {
private:
        float** matriz; //matriz das altitudes (uma matriz 2d dinamica, ainda desconhecida)
        int dimensao;//tamanho da matriz (9 se for 9x9 por ex)
    //metodos privados como tem nas sugestoes do pdf
    //diamond vai calcular o centro do quadrado, square os valores dos meios das arestas
    //privados pois n será necessário chamá-los futuramente em outros códigos, usados apenas pelo gerar()
        void etapaDiamond(int x, int y, int tamanho, float deslocamento);
        void etapaSquare(int x, int y, int tamanho, float deslocamento);
public:
        MDA(int n);//recebe n para calcular 2^n + 1 (só aqui a matriz passa a ser conhecida) e ini o objeto
        ~MDA();//destroi o objeto e libera a memória
        void gerar(float rugosidade);//usando o diamond e square vai gerar o mapa de altitudes
        float getAlt(int lin, int col);//retornar altitude do mapa
        int getDim();//consultar as linhas e colunas (dimensões da matriz)
        void salvar(const std::string& nomearquivo);//salvar o mapa em um arquivo
        void ler(const std::string& nomearquivo);//carregar o mapa de um arquivo
};

}
#endif