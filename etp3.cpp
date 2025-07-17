#include "mapaalt.h"
#include "imagem.h"
#include "paleta.h"

#include <iostream>
#include <limits> // Para std::numeric_limits

int main() {
    // --- 1. Configurações Iniciais ---
    const int N_MAPA = 8; // Gera um mapa de 2^8 + 1 = 257x257. Mude para N=9 para 513x513.
    const float RUGOSIDADE = 0.65f; // Um bom valor para terrenos. Experimente mudar!
    const std::string NOME_ARQUIVO_IMAGEM = "mapa_de_altitudes.ppm";

    // --- 2. Geração do Mapa de Altitudes ---
    std::cout << "ETAPA 3: GERACAO E VISUALIZACAO DE MAPA DE ALTITUDES\n\n";
    std::cout << "1. Gerando mapa de " << (pow(2, N_MAPA) + 1) << "x" << (pow(2, N_MAPA) + 1) << " com rugosidade " << RUGOSIDADE << "...\n";
    
    mapa::MDA meuMapa(N_MAPA);
    meuMapa.gerar(RUGOSIDADE);
    
    int dimensao = meuMapa.getDim();
    std::cout << "   ...Mapa gerado com sucesso!\n";

    // --- 3. Encontrar as Altitudes Mínima e Máxima para Normalização ---
    std::cout << "2. Buscando altitudes minima e maxima para a paleta de cores...\n";
    float minAlt = std::numeric_limits<float>::max();
    float maxAlt = std::numeric_limits<float>::lowest();

    for (int i = 0; i < dimensao; ++i) {
        for (int j = 0; j < dimensao; ++j) {
            float alt = meuMapa.getAlt(i, j);
            if (alt < minAlt) minAlt = alt;
            if (alt > maxAlt) maxAlt = alt;
        }
    }
    std::cout << "   ...Altitude Minima: " << minAlt << " | Altitude Maxima: " << maxAlt << "\n";

    // --- 4. Definir a Paleta de Cores ---
    // Usaremos as classes que você já criou, definindo as cores e os valores em arrays C-style.
    std::cout << "3. Criando paleta de cores para o terreno...\n";
    const int QTD_CORES = 6;
    
    pc::Cor cores_paleta[QTD_CORES] = {
    {30, 60, 150},     // Azul escuro (menos saturado)
    {70, 130, 200},    // Azul médio (água)
    {100, 160, 80},    // Verde (vegetação)
    {120, 100, 60},    // Marrom (montanhas)
    {180, 180, 180},   // Cinza claro (rochas)
    {240, 240, 240}    // Branco (neve)
};

    // Os valores devem estar em ordem crescente, mapeando de 0.0 a 1.0.
    double valores_paleta[QTD_CORES] = {
        0.0,    // Nível do mar
        0.3,    // Transição para terra
        0.4,    // Nível da planície
        0.6,    // Nível da montanha
        0.8,    // Nível das rochas
        1.0     // Pico nevado
    };

    pc::Cores paleta(QTD_CORES, cores_paleta, valores_paleta);
    std::cout << "   ...Paleta criada!\n";

    // --- 5. Criar a Imagem e Pintar os Pixels ---
    std::cout << "4. Criando imagem e pintando pixels com base nas altitudes...\n";
    img::Imagem imagem(dimensao, dimensao);
    
    float rangeAlt = maxAlt - minAlt;

    for (int i = 0; i < dimensao; ++i) { // 'i' controla as linhas (altura, y)
        for (int j = 0; j < dimensao; ++j) { // 'j' controla as colunas (largura, x)
            float alt = meuMapa.getAlt(i, j);
            
            // Normaliza a altitude para o intervalo [0.0, 1.0]
            double valorNormalizado = 0.0;
            if (rangeAlt > 0) { // Evita divisão por zero se todas as altitudes forem iguais
                valorNormalizado = (alt - minAlt) / rangeAlt;
            }

            // Obtém a cor correspondente da paleta
            pc::Cor corDoPixel = paleta.obterCor(valorNormalizado);

            // Define o pixel na imagem. Cuidado com a ordem (x, y) -> (j, i)
            imagem.DefPix(j, i, corDoPixel);
        }
        if (i % 50 == 0) { // Mostra o progresso a cada 50 linhas
            std::cout << "   ...Processando linha " << i << " de " << dimensao << "\n";
        }
    }
    std::cout << "   ...Pintura da imagem concluida!\n";

    // --- 6. Salvar a Imagem Final ---
    std::cout << "5. Salvando imagem final em '" << NOME_ARQUIVO_IMAGEM << "'...\n";
    if (imagem.salvar(NOME_ARQUIVO_IMAGEM)) {
        std::cout << "\nSUCESSO! O arquivo de imagem foi gerado.\n";
        std::cout << "Abra o arquivo '" << NOME_ARQUIVO_IMAGEM << "' para ver seu terreno.\n";
    } else {
        std::cerr << "\nERRO: Falha ao salvar a imagem.\n";
    }

    return 0;
}