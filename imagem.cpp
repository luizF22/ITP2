#include "imagem.h" // inclusão do cabeçalho com as definições
#include <fstream> //para usar o ofstream, que salva a imagem 
#include <iostream> //mensagens de erro

using namespace img;

//vai criar espaços com base na largura e altura recebidas 
Imagem::Imagem(int larg, int alt) {
    largura = larg; // armazenar as dimensões de imagem
    altura = alt;
    int total_pixels = largura * altura; // calcula o total de pixels necessarios
    // alocar um array dinamicamente de pc::Cor com tamanho necessario
    // new reserva um bloco de memoria e pixels aponta pro inicio dele
    pixels = new pc::Cor[total_pixels];
    for(int i = 0; i < total_pixels; ++i) { // somente para inicializar todos como preto 
        pixels[i] = {0, 0, 0}; //rgb, todos iguais a 0 inicialmente
    }
}

Imagem::~Imagem() {
    // o destrutor é liberar a memória que foi alocada com 'new[]'.
    delete[] pixels;
}

// vai alocar dentro do array pixels as cores recebidas com base nas suas coordenadas
void Imagem::DefPix(int x, int y, pc::Cor cor) {
    //verificação de segurança para garantir que x, y estão dentro dos lim da img
    if (x >= 0 && x < largura && y >= 0 && y < altura) {
        int indice = y * largura + x; //formula dada para converter 2D em um indice 1D pro array
        pixels[indice] = cor; // vai indicar o local da cor de
    }
}

pc::Cor Imagem::obtPix(int x, int y) const {
    if (x >= 0 && x < largura && y >= 0 && y < altura) {
        int indice = y * largura + x;
        return pixels[indice]; // retorna a cor presente naquele pixel
    }
    return {0, 0, 0}; //retornar preto se as coordenadas tiverem fora dos limites por segurança
}
// criar arquivo e ir colocando as coisas escritas dentro dele 
bool Imagem::salvar(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);//cria um obj de fluxo de arquivo para escrita (output file stream), um arquivo que permite escrever coisas
    if (!arquivo.is_open()) { //verfic se o arquivo pôde ser aberto
        std::cerr << "Erro, não foi possível criar arquivo: " << nomeArquivo << std::endl;
        return false;
    }
    //escrita do cabeçalho no formato ppm P3
    arquivo << "P3\n"; //numero que identifica o formato do PPM
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";//valor max de cada cor
    //escreve os dados dos pixels
    int total_pixels = largura * altura;
    for (int i = 0; i < total_pixels; ++i) { //escrever os valores de RGB e do pixel atual
        arquivo << (int)pixels[i].R << " " //usa-se o (int) para garantir que numeros e n carac ascii
        << (int)pixels[i].G << " "
        << (int)pixels[i].B << "  "; // Deixei um espaço duplo para separar melhor os pixels
        if ((i + 1) % largura == 0) {//vai colocar um quebra linha a cada final de linha
            arquivo << "\n";
        }
    }
    arquivo.close();
    return true;
}
