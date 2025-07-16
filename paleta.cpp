#include "paleta.h" // pra trazer as declarações do arquivo e as aspas sao pra dizer que é o nome do arquivo
#include <fstream> // essa biblioteca possibilita a leitura de arquivos
#include <iostream> // pra usar std
#include <sstream>  // usada para manipular strings 
#include <limits> // só pra saber os limites de cada tipo 
using namespace pc; // foi previamente definido em paleta.h, posso usar para evitar pc:: cores, por exemplo

// vamos receber valores e copiar em arrays e quantidades que sao privados, criando copias, garantindo segurança
Cores::Cores(int qtd, const Cor c[], const double v[]){ //vai receber a quantidade, os dois arrays de cores e valores
    // o const é para eles nao serem mudados
  if (qtd > 100) qtd = 100;  // limitar
    quantidade = qtd;
    for (int i = 0; i < qtd; ++i) { // vai copiar e colar os valores passados para os vetores/arrays
        cores[i] = c[i]; // construção de um array interno para nao ser afetado durante o programa
        valores[i] = v[i]; // vai pegar informações externas e transformar em internas, encapsulando os dados
    }
}

// vai receber um valor real e retornar a cor que corresponde a esse valor
// a pessoa pode dar outros valores, mas vai atribuir a ele um especifico dentro da paleta, sendo o piso
Cor Cores::obterCor(double valor) const {
    if (quantidade == 0) return Cor{0, 0, 0}; // retorna uma cor padrão: preto

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
    // Abre o arquivo em modo binário para evitar problemas de codificação, pra evitar os caracteres invisiveis 
    std::ifstream arquivo(caminho, std::ios::binary);
    if (!arquivo) { // vai ver se o arquivo foi aberto
        std::cerr << "ERRO: Não foi possível abrir o arquivo!" << std::endl;// vai mostrar que tem um erro
        return false;
    }

    // Lê a primeira linha (quantidade)
    std::string linha;
    if (!std::getline(arquivo, linha)) { // vai ler ate o primeio /n e colocar na string 
        std::cerr << "ERRO: Arquivo vazio!" << std::endl; // caso esteja vazio, não vai conseguir ler 
        return false;
    }

    // Remove possíveis caracteres BOM (Byte Order Mark)
    if (linha.size() >= 3 && //vai verificar se a string linha tem pelo menos 3 caracteres
    // são 3 bytes para indicar que há caracteres invisíveis no UFT-8
    // vai converter o caractere em unsigned char, para ficar entre 0-255
        static_cast<unsigned char>(linha[0]) == 0xEF && //usa isso para evitar problemas com números negativos 
        static_cast<unsigned char>(linha[1]) == 0xBB && // caso o char nao seja assinado, pode ser interpretado como valor negativo, ja que esse bytes são maiores que 127
        static_cast<unsigned char>(linha[2]) == 0xBF) {
        linha = linha.substr(3);// vai criar uma nova string que descarta os 3 primeiros para tirar o BOM
    }

    // Converte a quantidade
    std::istringstream qtd_ss(linha);//tranforma a string linha em um inteiro 
    if (!(qtd_ss >> quantidade) || quantidade <= 0 || quantidade > 100) { // vai extrair o valor e ver se ele esta dentro do intervalo
        std::cerr << "ERRO: Quantidade inválida de cores!" << std::endl;
        return false; // caso isso não aconteça, vai retornar false
    }

    // Lê cada linha de cores
    for (int i = 0; i < quantidade; ++i) {
        if (!std::getline(arquivo, linha)) { // lê e atribui a string linha, vendo se está com as cores da quantidade
            std::cerr << "ERRO: Arquivo incompleto!" << std::endl;
            return false;
        }

        // depois de atribuir isso à string, vai extrair em ordem e ver se eles estão dentro dos valores esperados
        std::istringstream iss(linha);// transforma a linha em um fluxo de entrada pra pegar os valores
        double valor;
        int r, g, b;
        if (!(iss >> valor >> r >> g >> b) || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
            std::cerr << "ERRO: Formato inválido na linha " << i+1 << std::endl;
            return false;
        }

        valores[i] = valor;
        //  converte esse inteiro para um valor do tipo unsigned char (um byte, 0 a 255)
        // tem que converter por causa da estrutura do RGB, que é em unsigned char, não inteiro
        cores[i].R = static_cast<unsigned char>(r);
        cores[i].G = static_cast<unsigned char>(g);
        cores[i].B = static_cast<unsigned char>(b);
    }

    return true;
}
