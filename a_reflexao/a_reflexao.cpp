// =============================================================================
// a_reflexao/a_reflexao.cpp — Reflexão Temporal: y_r[n] = x[-n]
// Compilar: g++ a_reflexao.cpp -o a_reflexao
// Executar: ./a_reflexao
// =============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>

int main() {
    // ---- 1) Entrada do usuário ----
    int N;
    std::cout << "=== Reflexao Temporal ===" << std::endl;
    std::cout << "Tamanho N do sinal: ";
    std::cin >> N;

    std::vector<double> x(N);
    std::cout << "Amplitudes de x[n] (n=0 ate n=" << N-1 << "):" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "  x[" << i << "] = ";
        std::cin >> x[i];
    }

    // ---- 2) Reflexão: x_r[-n] = x[n] ----
    // Original: n = 0..N-1
    // Refletido: n = -(N-1)..0

    // ---- 3) Arquivos .dat ----
    {
        std::ofstream f("original.dat");
        for (int n = 0; n < N; n++)
            f << n << "\t" << x[n] << "\n";
    }
    {
        std::ofstream f("refletido.dat");
        for (int i = 0; i < N; i++) {
            int n = -(N - 1) + i;      // vai de -(N-1) a 0
            f << n << "\t" << x[N-1-i] << "\n";
        }
    }

    // ---- 4) Script gnuplot → PNG ----
    {
        std::ofstream gp("plot_reflexao.gp");
        gp << "set terminal pngcairo size 900,500 enhanced font 'Sans,12'\n";
        gp << "set output 'reflexao.png'\n";
        gp << "set title 'Reflexao Temporal: x[n] e x[-n]' font 'Sans,14'\n";
        gp << "set xlabel 'n'\n";
        gp << "set ylabel 'Amplitude'\n";
        gp << "set key top right\n";
        gp << "set grid\n";
        gp << "set style data impulses\n";
        gp << "plot 'original.dat'  using 1:2 lw 3 lc rgb '#0077BB' title 'x[n] (original)', \\\n";
        gp << "     'original.dat'  using 1:2 with points pt 7 ps 1.8 lc rgb '#0077BB' notitle, \\\n";
        gp << "     'refletido.dat' using 1:2 lw 3 lc rgb '#EE7733' title 'x[-n] (refletido)', \\\n";
        gp << "     'refletido.dat' using 1:2 with points pt 7 ps 1.8 lc rgb '#EE7733' notitle\n";
    }

    std::cout << "\nGerando grafico: reflexao.png ..." << std::endl;
    int ret = system("gnuplot plot_reflexao.gp");
    if (ret == 0)
        std::cout << "Imagem salva em: reflexao.png" << std::endl;
    else
        std::cerr << "Erro ao executar gnuplot." << std::endl;

    return 0;
}
