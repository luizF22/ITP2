#include "mapaalt.h"

using namespace mapa;

img::Imagem MDA::gerarImagem(const pc::Cores& paleta, float fatorSombra) const {
    // --- ETAPA DE NORMALIZAÇÃO (INÍCIO) ---
    // 1. Primeiro, precisamos encontrar a altitude mínima e máxima no mapa.
    float min_alt = matriz[0][0];
    float max_alt = matriz[0][0];

    for (int y = 0; y < dimensao; ++y) {
        for (int x = 0; x < dimensao; ++x) {
            if (matriz[y][x] < min_alt) {
                min_alt = matriz[y][x];
            }
            if (matriz[y][x] > max_alt) {
                max_alt = matriz[y][x];
            }
        }
    }
    
    float intervalo_alt = max_alt - min_alt;
    // Evita divisão por zero caso o mapa seja completamente plano
    if (intervalo_alt == 0) {
        intervalo_alt = 1.0f;
    }
    // --- ETAPA DE NORMALIZAÇÃO (FIM) ---


    // Cria um objeto Imagem com as mesmas dimensões do mapa.
    img::Imagem imagem(dimensao, dimensao);

    // Percorre cada ponto (pixel) do mapa.
    for (int y = 0; y < dimensao; ++y) {
        for (int x = 0; x < dimensao; ++x) {
            
            float altitude_atual = matriz[y][x];

            // 2. Normaliza a altitude atual para o intervalo [0.0, 1.0].
            float altitude_normalizada = (altitude_atual - min_alt) / intervalo_alt;

            // 3. Obtém a cor base usando o valor normalizado.
            pc::Cor cor_pixel = paleta.obterCor(altitude_normalizada);

            // 4. Aplica o efeito de sombreamento.
            if (y > 0 && x > 0) {
                float altitude_vizinho = matriz[y - 1][x - 1];

                if (altitude_atual < altitude_vizinho) {
                    cor_pixel.R = static_cast<unsigned char>(cor_pixel.R * fatorSombra);
                    cor_pixel.G = static_cast<unsigned char>(cor_pixel.G * fatorSombra);
                    cor_pixel.B = static_cast<unsigned char>(cor_pixel.B * fatorSombra);
                }
            }

            // 5. Define a cor do pixel (original ou sombreada) na imagem.
            imagem.DefPix(x, y, cor_pixel);
        }
    }

    // Retorna o objeto Imagem completo.
    return imagem;
}


// --- Construtor e Destrutor ---

MDA::MDA(int n) {
    // Garante que n não seja negativo
    if (n < 1) n = 1; 

    // Calcula a dimensão conforme a fórmula 2^n + 1
    dimensao = (int)(pow(2, n)) + 1;
    
    // Aloca a memória para as linhas (array de ponteiros)
    matriz = new float*[dimensao];
    for (int i = 0; i < dimensao; ++i) {
        // Aloca a memória para as colunas de cada linha
        matriz[i] = new float[dimensao];
        // Inicializa todos os valores com 0.0f
        for (int j = 0; j < dimensao; ++j) {
            matriz[i][j] = 0.0f;
        }
    }

    // Semente para o gerador de números aleatórios. 
    // É importante chamar isso apenas uma vez. O construtor é um bom lugar.
    srand((unsigned int)(time(nullptr)));
}

MDA::~MDA() {
    // Libera a memória na ordem inversa da alocação para evitar memory leaks
    if (matriz != nullptr) {
        for (int i = 0; i < dimensao; ++i) {
            delete[] matriz[i]; // Libera cada linha
        }
        delete[] matriz; // Libera o array de ponteiros
    }
}

// --- Métodos de Acesso ---

int MDA::getDim() {
    return dimensao;
}

float MDA::getAlt(int lin, int col) {
    // Checagem de segurança para não acessar memória fora dos limites da matriz
    if (lin >= 0 && lin < dimensao && col >= 0 && col < dimensao) {
        return matriz[lin][col];
    }
    // Retorna um valor de erro se as coordenadas forem inválidas
    std::cerr << "Erro: Tentativa de acesso a coordenadas invalidas (" << lin << ", " << col << ")\n";
    return -1.0f;
}

// --- Métodos do Algoritmo ---

void MDA::gerar(float rugosidade) {
    int tamanho = dimensao - 1;

    // 1. Inicializa os 4 cantos com valores aleatórios (ex: entre 0 e 500)
    matriz[0][0]             = ((float)(rand()) / RAND_MAX) * 500.0f;
    matriz[0][tamanho]       = ((float)(rand()) / RAND_MAX) * 500.0f;
    matriz[tamanho][0]       = ((float)(rand()) / RAND_MAX) * 500.0f;
    matriz[tamanho][tamanho] = ((float)(rand()) / RAND_MAX) * 500.0f;

    float deslocamento = 500.0f; // Deslocamento aleatório inicial

    // Loop principal: executa enquanto o tamanho do passo for maior que 1
    for (int passo = tamanho; passo > 1; passo /= 2) {
        
        // --- ETAPA DIAMOND ---
        for (int y = 0; y < tamanho; y += passo) {
            for (int x = 0; x < tamanho; x += passo) {
                etapaDiamond(x, y, passo, deslocamento);
            }
        }

        // --- ETAPA SQUARE ---
        for (int y = 0; y < tamanho; y += passo) {
            for (int x = 0; x < tamanho; x += passo) {
                etapaSquare(x, y, passo, deslocamento);
            }
        }
        
        // Reduz o deslocamento para a próxima iteração
        deslocamento *= rugosidade;
    }
}

void MDA::etapaDiamond(int x, int y, int tamanho, float deslocamento) {
    int meio = tamanho / 2;

    // Coordenadas dos 4 cantos do quadrado
    float superior_esq = matriz[y][x];
    float superior_dir = matriz[y][x + tamanho];
    float inferior_esq = matriz[y + tamanho][x];
    float inferior_dir = matriz[y + tamanho][x + tamanho];

    // Média dos 4 cantos
    float media = (superior_esq + superior_dir + inferior_esq + inferior_dir) / 4.0f;

    // Deslocamento aleatório entre [-deslocamento, +deslocamento]
    float rand_val = (((float)(rand()) / RAND_MAX) * 2.0f - 1.0f) * deslocamento;

    // Define a altitude do ponto central
    matriz[y + meio][x + meio] = media + rand_val;
}

void MDA::etapaSquare(int x, int y, int tamanho, float deslocamento) {
    int meio = tamanho / 2;

    // Coordenadas dos 4 pontos a serem calculados (centros das arestas do quadrado)
    int p_norte_x = x + meio, p_norte_y = y;
    int p_sul_x   = x + meio, p_sul_y   = y + tamanho;
    int p_leste_x = x + tamanho, p_leste_y = y + meio;
    int p_oeste_x = x, p_oeste_y = y + meio;
    
    // Função auxiliar para calcular cada ponto da etapa Square
    auto calcularPonto = [&](int px, int py) {
        float soma = 0.0f;
        int cont = 0;
        
        // Vizinho de cima
        if (py - meio >= 0) { soma += matriz[py - meio][px]; cont++; }
        // Vizinho de baixo
        if (py + meio < dimensao) { soma += matriz[py + meio][px]; cont++; }
        // Vizinho da esquerda
        if (px - meio >= 0) { soma += matriz[py][px - meio]; cont++; }
        // Vizinho da direita
        if (px + meio < dimensao) { soma += matriz[py][px + meio]; cont++; }

        float media = soma / cont;
        float rand_val = (((float)(rand()) / RAND_MAX) * 2.0f - 1.0f) * deslocamento;
        matriz[py][px] = media + rand_val;
    };

    // Calcula os 4 pontos
    calcularPonto(p_norte_x, p_norte_y);
    calcularPonto(p_sul_x, p_sul_y);
    calcularPonto(p_leste_x, p_leste_y);
    calcularPonto(p_oeste_x, p_oeste_y);
}

// --- Métodos de Arquivo ---

void MDA::salvar(const std::string& nomearquivo) {
    std::ofstream arquivo(nomearquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel criar o arquivo para salvar." << std::endl;
        return;
    }

    // Primeira linha: salva a dimensão da matriz
    arquivo << dimensao << std::endl;

    // Linhas seguintes: salva os valores de altitude
    for (int i = 0; i < dimensao; ++i) {
        for (int j = 0; j < dimensao; ++j) {
            arquivo << matriz[i][j] << " ";
        }
        arquivo << std::endl;
    }
    arquivo.close();
    std::cout << "Mapa salvo com sucesso em " << nomearquivo << std::endl;
}

void MDA::ler(const std::string& nomearquivo) {
    std::ifstream arquivo(nomearquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo para ler." << std::endl;
        return;
    }

    int novaDimensao;
    arquivo >> novaDimensao;

    // Se a dimensão for diferente, é preciso realocar a matriz
    if (novaDimensao != dimensao) {
        // Libera a memória antiga
        for (int i = 0; i < dimensao; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;

        // Aloca nova memória
        dimensao = novaDimensao;
        matriz = new float*[dimensao];
        for (int i = 0; i < dimensao; ++i) {
            matriz[i] = new float[dimensao];
        }
    }

    // Lê os valores de altitude do arquivo para a matriz
    for (int i = 0; i < dimensao; ++i) {
        for (int j = 0; j < dimensao; ++j) {
            arquivo >> matriz[i][j];
        }
    }
    arquivo.close();
    std::cout << "Mapa lido com sucesso de " << nomearquivo << std::endl;
}