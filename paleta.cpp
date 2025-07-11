#include "paleta.h" // pra trazer as declarações do arquivo e as aspas sao pra dizer que é o nome do arquivo
#include <fstream> // essa biblioteca possibilita a leitura de arquivos
#include <iostream> 
#include <sstream>  
#include <limits>
using namespace pc; // foi previamente definido em paleta.h

// vamos receber valores na main e copiar em arrays e quantidades que sao privados, criando copias, garantindo segurança
Cores::Cores(int qtd, const Cor c[], const double v[]){ //vai receber a quantidade, os dois arrays de cores e valores
    // o const é prsa eles nao serem mudados
  if (qtd > 100) qtd = 100;  // limitar
    quantidade = qtd;
    for (int i = 0; i < qtd; ++i) { // vai copiar e colar os valores passados para os vetores
        cores[i] = c[i]; // construção de um array interno para nao ser afetado durante o programa
        valores[i] = v[i];
    }
}

// vai receber um valor real e retornar a cor que corresponde a esse valor
// a pessoa pode dar outros valores, mas vai atribuir a ele um especifico dentro da paleta
Cor Cores::obterCor(double valor) const {
    if (quantidade == 0) return Cor{0, 0, 0}; // ou uma cor padrão

    for (int i = 0; i < quantidade - 1; ++i) { // vai percorrer os valores ja guardados anteriormente 
        if (valor >= valores[i] && valor < valores[i + 1]) {// vai testar se ele esta em algum intervalo específico
            return cores[i];// vai retornar a cor com esse indice 
        }
    }
    return cores[quantidade - 1]; // Retorna a última cor se o valor for maior
}

// só pra saber se a pessoa colocou certo
bool Cores::estaOrdenados() const {// o const é pra nada da classe ser mudado
    for (int i = 0; i < quantidade - 1; ++i) {// o -1 é pra nao acessar coisa de fora do array
        if (valores[i] >= valores[i + 1]) { // os valores em ordem crescente 
            return false;
        }
    }
    return true;
}

bool Cores::carregarDeArquivos(const std::string& caminho) {
    // Abre o arquivo em modo binário para evitar problemas de codificação
    std::ifstream arquivo(caminho, std::ios::binary);
    if (!arquivo) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo!" << std::endl;
        return false;
    }

    // Lê a primeira linha (quantidade)
    std::string linha;
    if (!std::getline(arquivo, linha)) {
        std::cerr << "ERRO: Arquivo vazio!" << std::endl;
        return false;
    }

    // Remove possíveis caracteres BOM (Byte Order Mark)
    if (linha.size() >= 3 && 
        static_cast<unsigned char>(linha[0]) == 0xEF &&
        static_cast<unsigned char>(linha[1]) == 0xBB &&
        static_cast<unsigned char>(linha[2]) == 0xBF) {
        linha = linha.substr(3);
    }

    // Converte a quantidade
    std::istringstream qtd_ss(linha);
    if (!(qtd_ss >> quantidade) || quantidade <= 0 || quantidade > 100) {
        std::cerr << "ERRO: Quantidade inválida de cores!" << std::endl;
        return false;
    }

    // Lê cada linha de cores
    for (int i = 0; i < quantidade; ++i) {
        if (!std::getline(arquivo, linha)) {
            std::cerr << "ERRO: Arquivo incompleto!" << std::endl;
            return false;
        }

        // Converte os valores da linha
        std::istringstream iss(linha);
        double valor;
        int r, g, b;
        if (!(iss >> valor >> r >> g >> b) || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
            std::cerr << "ERRO: Formato inválido na linha " << i+1 << std::endl;
            return false;
        }

        valores[i] = valor;
        cores[i].R = static_cast<unsigned char>(r);
        cores[i].G = static_cast<unsigned char>(g);
        cores[i].B = static_cast<unsigned char>(b);
    }

    // Verificação final
    std::cout << "\nVERIFICAÇÃO FINAL (3 primeiros valores):\n";
    for (int i = 0; i < 3 && i < quantidade; ++i) {
        std::cout << valores[i] << " - "
                  << static_cast<int>(cores[i].R) << " "
                  << static_cast<int>(cores[i].G) << " "
                  << static_cast<int>(cores[i].B) << "\n";
    }

    return true;
}
