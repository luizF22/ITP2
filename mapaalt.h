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
        float** matriz; //matriz de altitudes
        int dimensao;//tamanho da matriz (9 se for 9x9 por ex)
    //metodos privados como tem nas sugestoes do pdf
        void etapaDiamond(int x, int y, int tamanho, float deslocamento);
        void etapaSquare(int x, int y, int tamanho, float deslocamento);
public:
        MDA(int n);//recebe n para calcular (2^n + 1)
        ~MDA();
        void gerar(float rugosidade);
        float getAlt(int lin, int col);
        int getDim();//consultar as linhas e colunas
        void salvar(const std::string& nomearquivo);
        void ler(const std::string& nomearquivo);
};

}
#endif