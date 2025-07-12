#include "imagem.h"
#include <fstream> //para usar o ofstream
#include <iostream> //mensagens de erro

// NOTA: Adicionei o "using namespace img;" aqui para não precisar repetir "img::" em todas as funções.
using namespace img;

//implementação do construtor abaixo, chamado quando criamos uma Imagem img(10, 15)
Imagem::Imagem(int larg, int alt) {
    largura = larg; // armazenar as dimensoes de imagem
    altura = alt;
    int total_pixels = largura * altura; // calcular o num total de pixels necessarios
    // alocar um array dinamicamente de pc::Cor com tamanho necessario
    // new reserva um bloco de memoria e pixels aponta pro inicio dele
    pixels = new pc::Cor[total_pixels];
    for(int i = 0; i < total_pixels; ++i) {
        pixels[i] = {0, 0, 0}; //rgb, todos iguais a 0 inicialmente
    }
}

// *** A PARTE QUE FALTAVA - A IMPLEMENTAÇÃO DO DESTRUTOR ***
Imagem::~Imagem() {
    // A única função do destrutor é liberar a memória que foi alocada com 'new[]'.
    delete[] pixels;
}
// *** FIM DA PARTE QUE FALTAVA ***


//implementação de Definir Pixel
void Imagem::DefPix(int x, int y, pc::Cor cor) {
    //verif de segurança para garantir que x, y estão dentro dos lim da img
    if (x >= 0 && x < largura && y >= 0 && y < altura) {
        int indice = y * largura + x; //formula dada para converter 2D em um indice 1D pro array
        pixels[indice] = cor;
    }
}
//implementar obter pixel
pc::Cor Imagem::obtPix(int x, int y) const {
    if (x >= 0 && x < largura && y >= 0 && y < altura) {
        int indice = y * largura + x;
        return pixels[indice];
    }
    return {0, 0, 0}; //retornar preto se as coordenadas tiverem fora dos lim por segurança
}

//implemetar salvar
bool Imagem::salvar(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);//cria um obj de fluxo de arquivo para escrita (output file stream)
    if (!arquivo.is_open()) { //verfic se o arquivo pôde ser aberto
        std::cerr << "Erro, não foi possível criar arquivo: " << nomeArquivo << std::endl;
        return false;
    }
    //escrita do cabeçalho no formato ppm P3
    arquivo << "P3\n"; //numero que identifica o formato
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";//valor max de cada cor
    //escreve os dados dos pixels
    int total_pixels = largura * altura;
    for (int i = 0; i < total_pixels; ++i) { //escrever os valores de RGB e do pixel atual
        arquivo << (int)pixels[i].R << " " //usa-se o (int) para transforma-los em numeros e n carac ascii
        << (int)pixels[i].G << " "
        << (int)pixels[i].B << "  "; // Deixei um espaço duplo para separar melhor os pixels
        if ((i + 1) % largura == 0) {//apenas uma quebra de linha pra ficar + legivel
            arquivo << "\n";
        }
    }
    arquivo.close();
    return true;
}