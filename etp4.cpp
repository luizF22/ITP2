#include <iostream>
#include <string>
#include <stdexcept>//para std::invalid_argument e std::out_of_range
#include "paleta.h"
#include "imagem.h"
#include "mapaalt.h"

int main() {
    const float RUGOSIDADE = 0.4f;//cntrola a "aspereza" do terreno. valores entre 0.4 e 0.7 são bons os melhores
    const float FATOR_SOMBRA = 0.5f;//quão escuro o sombreamento será (0.5 = 50% mais escuro, por ex)

    std::cout << "--- Gerador de Imagens de Terreno Aleatorio ---\n";

    std::string arquivo_paleta;
    std::cout << "Digite o nome do arquivo da paleta de cores (ex: paleta.txt): ";
    std::cin >> arquivo_paleta;

    int n_valor;
    std::cout << "Digite o valor de N para o tamanho do mapa (a dimensao sera 2^N + 1): ";
    std::cin >> n_valor;

    std::string arquivo_saida;
    std::cout << "Digite o nome do arquivo de imagem a ser salvo (ex: terreno.ppm): ";
    std::cin >> arquivo_saida;

    try {
        //etp2: carregar a paleta de cores
        std::cout << "\nCarregando paleta de '" << arquivo_paleta << "'...\n";
        pc::Cores paleta(0, nullptr, nullptr); //cria um objeto paleta vazio
        if (!paleta.carregarDeArquivos(arquivo_paleta)) {
            std::cerr << "ERRO FATAL: Nao foi possivel ler ou processar o arquivo de paleta.\n";
            return 1; 
        }
        std::cout << "Paleta carregada com sucesso!\n";

        //gerar o mapa de altitudes
        std::cout << "Gerando mapa de altitudes com N=" << n_valor << "...\n";
        mapa::MDA mapa_de_altitudes(n_valor);
        mapa_de_altitudes.gerar(RUGOSIDADE);
        std::cout << "Mapa de " << mapa_de_altitudes.getDim() << "x" << mapa_de_altitudes.getDim() << " gerado.\n";
        
        //etp3: criar a imagem a partir do mapa
        std::cout << "Renderizando a imagem com sombreamento...\n";
        img::Imagem imagem_final = mapa_de_altitudes.gerarImagem(paleta, FATOR_SOMBRA);

        //etp4: salvar a imagem em Arquivo
        std::cout << "Salvando imagem em '" << arquivo_saida << "'...\n";
        if (imagem_final.salvar(arquivo_saida)) {
            std::cout << "\nSucesso! Imagem salva.\n";
        } else {
            std::cerr << "ERRO FATAL: Falha ao salvar a imagem no arquivo.\n";
            return 1;
        }

    } catch (const std::bad_alloc& e) {
        std::cerr << "ERRO DE MEMORIA: Nao foi possivel alocar memoria para o mapa. Tente um valor de N menor. Detalhes: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Ocorreu um erro inesperado: " << e.what() << std::endl;
        return 1;
    }

    return 0; // Sucesso
}   