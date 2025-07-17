#ifndef PALETA_H//evitar que leia-se 2x os arquivos quando forem trazidos pros .cpp (caso ja tenha sido def em outra inclusão)
#define PALETA_H
#include <string>

namespace pc{//evitar conflitos com nomes de outros arquivos, indicando exatamente de onde é cada coisa
struct Cor {
    unsigned char R;// unsigned char para variar de 0-255
    unsigned char G;
    unsigned char B;
};

class Cores {
        private://garantir que em outros códigos esses atributos n sejam alterados de forma alguma
        int quantidade;
        Cor cores[100];   
        double valores[100];

        public://vão ser chamados futuramente em outros códigos
 /**
 * @brief Construtor que inicializa o array interno de cores e valores internos com base nos parâmetros fornecidos.
 * @param qtd Número de cores a ser carregado (máximo 100).
 * @param c Array de objetos Cor representando as cores.
 * @param v Array de valores reais associados a cada cor.
 */
        Cores(int qtd, const Cor c[], const double v[]);//ini a paleta com cores e valores pre-def
    
 /**
 * @brief Carrega dados de cores e seus valores a partir de um arquivo de texto.
 * @param caminho recebe o "Caminho", que é o nome do arquivo, para o arquivo a ser lido.
 * @return true se o carregamento for bem-sucedido, false em caso de erro de leitura ou formato inválido.
 */
        bool carregarDeArquivos(const std::string& caminho);//carregar as cores de um arquivo externo

/**
 * @brief Retorna a cor correspondente a um valor real, com base nos intervalos definidos.
 * @param valor Valor real a ser mapeado.
 * @return Objeto Cor correspondente ao intervalo do valor.
 */   
        Cor obterCor(double valor) const;//mapear um valor para cor da paleta

/**
 * @brief Verifica se os valores estão ordenados em ordem crescente.
 * @return true se estiverem ordenados corretamente, false caso contrário.
 */
        bool estaOrdenados() const;//necessario pra que o obterCor funcione (ordem crescente)
};
}
#endif
