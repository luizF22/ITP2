#include "imagem.h"
#include <iostream>
using namespace std;
using namespace img;
void ImpRes(const string& nometeste, bool sucesso) {
    cout << "Teste '" << nometeste << "': " << (sucesso ? "Sucesso." : "Falha.") << endl;
} // auxilia a imprimir os resultados do teste
int main() {
    cout << "Etapa 2: " << endl;
    bool teste1_sucesso = true; //fazer um teste com todos os pixels sendo preto
    Imagem img_preta(2, 2);
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            pc::Cor pixel = img_preta.obtPix(x, y);
            if (pixel.R != 0 || pixel.G != 0 || pixel.B != 0) {
                teste1_sucesso = false;
                break;
            }
        }
        if (!teste1_sucesso) break;
    }
    ImpRes("Iniciando com preto (2x2)", teste1_sucesso);
    bool teste2_sucesso = true;//agora com todos eles sendo brancos
    Imagem img_branca(3, 4);
    pc::Cor cor_branca = {255, 255, 255};
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 3; ++x) {
            img_branca.DefPix(x, y, cor_branca);
        }
    }
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 3; ++x) {
            pc::Cor pixel = img_branca.obtPix(x, y);
            if (pixel.R != 255 || pixel.G != 255 || pixel.B != 255) {
                teste2_sucesso = false;
                break;
            }
        }
        if (!teste2_sucesso) break;
    }
    ImpRes("Definir e obter pixel (3x4 branco)", teste2_sucesso);
    if (teste2_sucesso) {//salvar a img branca em um arquivo
        bool salvou = img_branca.salvar("imagem_branca.ppm");
        ImpRes("Salvar arquivo ppm", salvou);
        if (salvou) {
            cout << "=> Verifique o arquivo 'imagem_branca.ppm' para confirmar que a img está branca.\n";
        }
    }
    cout << "Teste finalizado, criando bandeira\n" << endl;
//fazendo um outro teste agora com a bandeira da frança
    Imagem bandeira_franca(300, 200);
    pc::Cor azul = {0, 85, 164};
    pc::Cor branco = {255, 255, 255};
    pc::Cor vermelho = {239, 65, 53};
     for (int y = 0; y < 200; ++y) {
        for (int x = 0; x < 300; ++x) {// o primeiro, segundo e ultimo terço da largura abaixo:
            if (x < 100) { 
                bandeira_franca.DefPix(x, y, azul);
            } else if (x < 200) { 
                bandeira_franca.DefPix(x, y, branco);
            } else {
                bandeira_franca.DefPix(x, y, vermelho);
            }
        }
    }
    if(bandeira_franca.salvar("bandeira_franca.ppm")) {
        cout << "Criado com sucesso!\n";
    }
    return 0;
}