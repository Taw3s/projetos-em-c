#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include "vetor.h"

namespace {

using Clock = std::chrono::steady_clock;

double elapsed_ms(Clock::time_point inicio, Clock::time_point fim) {
    return std::chrono::duration<double, std::milli>(fim - inicio).count();
}

long long benchmark_vetor_c(int quantidade, double &tempo_ms) {
    auto inicio = Clock::now();

    Vetor *v = vetor_criar(quantidade);
    if (v == nullptr) {
        tempo_ms = -1.0;
        return 0;
    }

    for (int i = 0; i < quantidade; ++i) {
        vetor_adicionar(v, i);
    }

    long long soma = 0;
    for (int i = 0; i < v->tamanho; ++i) {
        int valor = 0;
        if (vetor_obter(v, i, &valor)) {
            soma += valor;
        }
    }

    vetor_destruir(v);
    auto fim = Clock::now();
    tempo_ms = elapsed_ms(inicio, fim);
    return soma;
}

long long benchmark_std_vector(int quantidade, bool reservar, double &tempo_ms) {
    auto inicio = Clock::now();

    std::vector<int> v;
    if (reservar) {
        v.reserve(static_cast<std::size_t>(quantidade));
    }

    for (int i = 0; i < quantidade; ++i) {
        v.push_back(i);
    }

    long long soma = 0;
    for (std::size_t i = 0; i < v.size(); ++i) {
        soma += v[i];
    }

    auto fim = Clock::now();
    tempo_ms = elapsed_ms(inicio, fim);
    return soma;
}

} // namespace

int main() {
    constexpr int quantidade = 100000;

    double ms_c = 0.0;
    double ms_cpp_sem_reserve = 0.0;
    double ms_cpp_com_reserve = 0.0;

    long long soma_c = benchmark_vetor_c(quantidade, ms_c);
    long long soma_cpp_1 = benchmark_std_vector(quantidade, false, ms_cpp_sem_reserve);
    long long soma_cpp_2 = benchmark_std_vector(quantidade, true, ms_cpp_com_reserve);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Benchmark com " << quantidade << " elementos:\n";
    std::cout << "  Vetor (C)                : " << ms_c << " ms (soma=" << soma_c << ")\n";
    std::cout << "  std::vector (sem reserve): " << ms_cpp_sem_reserve << " ms (soma=" << soma_cpp_1 << ")\n";
    std::cout << "  std::vector (com reserve): " << ms_cpp_com_reserve << " ms (soma=" << soma_cpp_2 << ")\n";

    return 0;
}
