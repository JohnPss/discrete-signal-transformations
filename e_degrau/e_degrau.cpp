// =============================================================================
// e_degrau/e_degrau.cpp — Soma com Degrau Unitário: y[n] = x[n] + A*u[n]
// Compilar: g++ e_degrau.cpp -o e_degrau
// Executar: ./e_degrau
// =============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iomanip>

int main() {
    // ---- 1) Sinal de entrada (mesmo do item a, hardcoded) ----
    std::vector<double> x = {0.0, 0.707, 1.0, 0.707, 0.0, -0.707, -1.0, -0.707};
    int N = static_cast<int>(x.size());

    std::cout << "=== Soma com Degrau Unitario ===" << std::endl;
    std::cout << "Sinal original: N = " << N << " amostras (n=0.." << N-1 << ")." << std::endl;

    // ---- 2) Ler amplitude do degrau ----
    double A;
    std::cout << "Amplitude A do degrau: ";
    std::cin >> A;

    // ---- 3) Calcular sinais num domínio estendido (com margem antes de n=0) ----
    int margem  = 3;            // amostras exibidas antes de n=0
    int n_total = margem + N;
    int n_min   = -margem;

    std::vector<double> xext(n_total, 0.0);
    std::vector<double> d(n_total, 0.0);
    std::vector<double> y(n_total, 0.0);

    for (int i = 0; i < n_total; i++) {
        int n   = n_min + i;
        double xn = (n >= 0 && n < N) ? x[n] : 0.0;
        double un = (n >= 0)           ? 1.0  : 0.0;
        xext[i] = xn;
        d[i]    = A * un;
        y[i]    = xn + A * un;
    }

    // ---- 4) Arquivos .dat ----
    {
        std::ofstream f("original.dat");
        for (int i = 0; i < n_total; i++)
            f << (n_min+i) << "\t" << xext[i] << "\n";
    }
    {
        std::ofstream f("degrau.dat");
        for (int i = 0; i < n_total; i++)
            f << (n_min+i) << "\t" << d[i] << "\n";
    }
    {
        std::ofstream f("soma.dat");
        for (int i = 0; i < n_total; i++)
            f << (n_min+i) << "\t" << y[i] << "\n";
    }

    // ---- 5) Script gnuplot → PNG ----
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << A;
    std::string A_str = oss.str();

    {
        std::ofstream gp("plot_degrau.gp");
        gp << "set terminal pngcairo size 900,500 enhanced font 'Sans,12'\n";
        gp << "set output 'degrau.png'\n";
        gp << "set title 'Soma com Degrau: y[n] = x[n] + " << A_str << "*u[n]' font 'Sans,14'\n";
        gp << "set xlabel 'n'\n";
        gp << "set ylabel 'Amplitude'\n";
        gp << "set key top left\n";
        gp << "set grid\n";
        gp << "set arrow from 0, graph 0 to 0, graph 1 nohead lc rgb '#888888' lw 1 dt 2\n";
        gp << "set label 'n=0' at 0, graph 1.04 center font 'Sans,10'\n";
        gp << "set style data impulses\n";
        gp << "plot 'original.dat' using 1:2 lw 3 lc rgb '#0077BB' title 'x[n] (original)', \\\n";
        gp << "     'original.dat' using 1:2 with points pt 7 ps 1.8 lc rgb '#0077BB' notitle, \\\n";
        gp << "     'degrau.dat'   using 1:2 lw 3 lc rgb '#009988' title '" << A_str << "*u[n] (degrau)', \\\n";
        gp << "     'degrau.dat'   using 1:2 with points pt 7 ps 1.8 lc rgb '#009988' notitle, \\\n";
        gp << "     'soma.dat'     using 1:2 lw 3 lc rgb '#EE7733' title 'y[n] (soma)', \\\n";
        gp << "     'soma.dat'     using 1:2 with points pt 7 ps 1.8 lc rgb '#EE7733' notitle\n";
    }

    std::cout << "\nGerando grafico: degrau.png ..." << std::endl;
    int ret = system("gnuplot plot_degrau.gp");
    if (ret == 0)
        std::cout << "Imagem salva em: degrau.png" << std::endl;
    else
        std::cerr << "Erro ao executar gnuplot." << std::endl;

    return 0;
}
