// =============================================================================
// b_escala/b_escala.cpp — Mudança de Escala Temporal
//   M > 1  → compressão: y[n] = x[Mn]
//   M < -1 → expansão por |M|: inserção de zeros
// Compilar: g++ b_escala.cpp -o b_escala
// Executar: ./b_escala
// =============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>

int main() {
    // ---- 1) Sinal de entrada (mesmo do item a, hardcoded) ----
    std::vector<double> x = {0.0, 0.707, 1.0, 0.707, 0.0, -0.707, -1.0, -0.707};
    int N = static_cast<int>(x.size());

    std::cout << "=== Mudanca de Escala Temporal ===" << std::endl;
    std::cout << "Sinal original: N = " << N << " amostras." << std::endl;

    // ---- 2) Ler fator M ----
    int M;
    std::cout << "Fator M (M>1 compressao, M<-1 expansao): ";
    std::cin >> M;

    // ---- 3) Calcular sinal escalonado ----
    std::vector<int>    ns;
    std::vector<double> ys;

    if (M > 1) {
        for (int n = 0; n * M < N; n++) {
            ns.push_back(n);
            ys.push_back(x[n * M]);
        }
    } else if (M < -1) {
        int L = std::abs(M);
        for (int i = 0; i < N; i++) {
            ns.push_back(i * L);
            ys.push_back(x[i]);
            if (i < N - 1) {
                for (int z = 1; z < L; z++) {
                    ns.push_back(i * L + z);
                    ys.push_back(0.0);
                }
            }
        }
    } else {
        std::cerr << "Erro: |M| deve ser >= 2." << std::endl;
        return 1;
    }

    // ---- 4) Arquivos .dat ----
    {
        std::ofstream f("original.dat");
        for (int n = 0; n < N; n++)
            f << n << "\t" << x[n] << "\n";
    }
    {
        std::ofstream f("escalonado.dat");
        for (int i = 0; i < (int)ns.size(); i++)
            f << ns[i] << "\t" << ys[i] << "\n";
    }

    // ---- 5) Script gnuplot → PNG ----
    std::string titulo = (M > 1)
        ? "Compressao Temporal: y[n] = x[" + std::to_string(M) + "n]"
        : "Expansao Temporal por fator " + std::to_string(std::abs(M));

    {
        std::ofstream gp("plot_escala.gp");
        gp << "set terminal pngcairo size 900,500 enhanced font 'Sans,12'\n";
        gp << "set output 'escala.png'\n";
        gp << "set title '" << titulo << "' font 'Sans,14'\n";
        gp << "set xlabel 'n'\n";
        gp << "set ylabel 'Amplitude'\n";
        gp << "set key top right\n";
        gp << "set grid\n";
        gp << "set style data impulses\n";
        gp << "plot 'original.dat'  using 1:2 lw 3 lc rgb '#0077BB' title 'x[n] (original)', \\\n";
        gp << "     'original.dat'  using 1:2 with points pt 7 ps 1.8 lc rgb '#0077BB' notitle, \\\n";
        gp << "     'escalonado.dat' using 1:2 lw 3 lc rgb '#EE7733' title 'y[n] (escalonado)', \\\n";
        gp << "     'escalonado.dat' using 1:2 with points pt 7 ps 1.8 lc rgb '#EE7733' notitle\n";
    }

    std::cout << "\nGerando grafico: escala.png ..." << std::endl;
    int ret = system("gnuplot plot_escala.gp");
    if (ret == 0)
        std::cout << "Imagem salva em: escala.png" << std::endl;
    else
        std::cerr << "Erro ao executar gnuplot." << std::endl;

    return 0;
}
