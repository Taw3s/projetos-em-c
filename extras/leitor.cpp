#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "vetor.h"

namespace {

// Substitui separadores comuns (vírgula, ponto e vírgula) por espaços para facilitar a leitura.
std::string normalizar_separadores(std::string linha) {
    for (char &ch : linha) {
        if (ch == ',' || ch == ';') {
            ch = ' ';
        }
    }
    return linha;
}

bool tentar_converter_int(const std::string &token, int &valor) {
    std::size_t pos = 0;
    try {
        valor = std::stoi(token, &pos);
    } catch (...) {
        return false;
    }
    return pos == token.size();
}

void carregar_arquivo(const std::string &caminho, Vetor *v, int &ignorados, int &descartados) {
    std::ifstream arquivo(caminho);
    if (!arquivo) {
        std::cerr << "Erro: nao foi possivel abrir '" << caminho << "'.\n";
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        auto pos_comentario = linha.find('#');
        if (pos_comentario != std::string::npos) {
            linha.erase(pos_comentario);
        }

        std::istringstream iss(normalizar_separadores(linha));
        std::string token;
        while (iss >> token) {
            int numero = 0;
            if (!tentar_converter_int(token, numero)) {
                ++ignorados;
                continue;
            }
            if (!vetor_adicionar(v, numero)) {
                ++descartados;
            }
        }
    }
}

void imprimir_relatorio(Vetor *v, int ignorados, int descartados) {
    std::cout << "Elementos carregados: " << v->tamanho << " / " << v->capacidade << "\n";

    if (v->tamanho == 0) {
        std::cout << "Nenhuma nota valida encontrada.\n";
        return;
    }

    int soma = 0;
    int menor = 0;
    int maior = 0;

    std::cout << "Valores: ";
    for (int i = 0; i < v->tamanho; ++i) {
        int val = 0;
        if (!vetor_obter(v, i, &val)) {
            continue;
        }
        if (i == 0) {
            menor = val;
            maior = val;
        } else {
            if (val < menor) menor = val;
            if (val > maior) maior = val;
        }
        soma += val;
        std::cout << val << (i + 1 < v->tamanho ? ", " : "\n");
    }

    double media = static_cast<double>(soma) / v->tamanho;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media : " << media << "\n";
    std::cout << "Menor : " << menor << "\n";
    std::cout << "Maior : " << maior << "\n";

    if (ignorados > 0) {
        std::cout << "Tokens nao numericos ignorados: " << ignorados << "\n";
    }
    if (descartados > 0) {
        std::cout << "Valores descartados (vetor cheio): " << descartados << "\n";
    }
}

} // namespace

int main(int argc, char *argv[]) {
    std::string caminho = (argc >= 2) ? argv[1] : "data/notas.txt";
    constexpr int capacidade_padrao = 100;

    Vetor *notas = vetor_criar(capacidade_padrao);
    if (notas == nullptr) {
        std::cerr << "Erro: sem memoria para criar o vetor.\n";
        return 1;
    }

    int ignorados = 0;
    int descartados = 0;
    carregar_arquivo(caminho, notas, ignorados, descartados);
    imprimir_relatorio(notas, ignorados, descartados);

    vetor_destruir(notas);
    return 0;
}
