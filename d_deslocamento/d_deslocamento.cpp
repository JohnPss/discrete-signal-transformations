// =============================================================================
// d_deslocamento/d_deslocamento.cpp — Deslocamento Temporal: y[n] = x[n-k]
//   Caso 1: domínio fixo [0, N-1] com truncamento/zeros
//   Caso 2: domínio expandido para acomodar todo o sinal
// Compilar: g++ d_deslocamento.cpp -o d_deslocamento
// Executar: ./d_deslocamento
// =============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>

int main() {
    // ---- 1) Sinal de entrada (mesmo do item a, hardcoded) ----
    std::vector<double> x = {0.0, 0.707, 1.0, 0.707, 0.0, -0.707, -1.0, -0.707};
    int N = static_cast<int>(x.size());

    std::cout << "=== Deslocamento Temporal ===" << std::endl;
    std::cout << "Sinal original: N = " << N << " amostras (n=0.." << N-1 << ")." << std::endl;

    // ---- 2) Ler deslocamento k ----
    int k;
    std::cout << "Deslocamento k (k>0 atraso, k<0 avanco): ";
    std::cin >> k;

    // ---- 3a) Caso 1: domínio fixo [0, N-1] ----
    std::vector<double> y1(N, 0.0);
    for (int n = 0; n < N; n++) {
        int src = n - k;
        if (src >= 0 && src < N)
            y1[n] = x[src];
    }

    // ---- 3b) Caso 2: domínio expandido ----
    int n_start = std::min(0, k);
    int n_end   = std::max(N-1, N-1+k);
    int M2      = n_end - n_start + 1;

    std::vector<double> x_exp(M2, 0.0), y2(M2, 0.0);
    for (int n = n_start; n <= n_end; n++) {
        int idx = n - n_start;
        if (n >= 0 && n < N)       x_exp[idx] = x[n];
        int src = n - k;
        if (src >= 0 && src < N)   y2[idx]    = x[src];
    }

    // ---- 4) Arquivos .dat ----
    // Caso 1
    {
        std::ofstream f("original_c1.dat");
        for (int n = 0; n < N; n++) f << n << "\t" << x[n] << "\n";
    }
    {
        std::ofstream f("deslocado_c1.dat");
        for (int n = 0; n < N; n++) f << n << "\t" << y1[n] << "\n";
    }
    // Caso 2
    {
        std::ofstream f("original_c2.dat");
        for (int i = 0; i < M2; i++) f << (n_start+i) << "\t" << x_exp[i] << "\n";
    }
    {
        std::ofstream f("deslocado_c2.dat");
        for (int i = 0; i < M2; i++) f << (n_start+i) << "\t" << y2[i] << "\n";
    }

    // ---- 5) Scripts gnuplot → PNG ----
    std::string tipo = (k >= 0) ? "Atraso" : "Avanco";
    std::ostringstream kss; kss << k;

    {
        std::ofstream gp("plot_shift_c1.gp");
        gp << "set terminal pngcairo size 900,500 enhanced font 'Sans,12'\n";
        gp << "set output 'deslocamento_caso1.png'\n";
        gp << "set title '" << tipo << " k=" << k << " — Dominio fixo [0," << N-1 << "]' font 'Sans,14'\n";
        gp << "set xlabel 'n'\n";
        gp << "set ylabel 'Amplitude'\n";
        gp << "set key top right\n";
        gp << "set grid\n";
        gp << "set style data impulses\n";
        gp << "plot 'original_c1.dat'  using 1:2 lw 3 lc rgb '#0077BB' title 'x[n] (original)', \\\n";
        gp << "     'original_c1.dat'  using 1:2 with points pt 7 ps 1.8 lc rgb '#0077BB' notitle, \\\n";
        gp << "     'deslocado_c1.dat' using 1:2 lw 3 lc rgb '#EE7733' title 'x[n-(" << k << ")] caso 1', \\\n";
        gp << "     'deslocado_c1.dat' using 1:2 with points pt 7 ps 1.8 lc rgb '#EE7733' notitle\n";
    }
    {
        std::ofstream gp("plot_shift_c2.gp");
        gp << "set terminal pngcairo size 900,500 enhanced font 'Sans,12'\n";
        gp << "set output 'deslocamento_caso2.png'\n";
        gp << "set title '" << tipo << " k=" << k << " — Dominio expandido [" << n_start << "," << n_end << "]' font 'Sans,14'\n";
        gp << "set xlabel 'n'\n";
        gp << "set ylabel 'Amplitude'\n";
        gp << "set key top right\n";
        gp << "set grid\n";
        gp << "set style data impulses\n";
        gp << "plot 'original_c2.dat'  using 1:2 lw 3 lc rgb '#0077BB' title 'x[n] (original)', \\\n";
        gp << "     'original_c2.dat'  using 1:2 with points pt 7 ps 1.8 lc rgb '#0077BB' notitle, \\\n";
        gp << "     'deslocado_c2.dat' using 1:2 lw 3 lc rgb '#EE7733' title 'x[n-(" << k << ")] caso 2', \\\n";
        gp << "     'deslocado_c2.dat' using 1:2 with points pt 7 ps 1.8 lc rgb '#EE7733' notitle\n";
    }

    std::cout << "\nGerando graficos..." << std::endl;
    int r1 = system("gnuplot plot_shift_c1.gp");
    int r2 = system("gnuplot plot_shift_c2.gp");
    if (r1 == 0) std::cout << "Imagem salva em: deslocamento_caso1.png" << std::endl;
    if (r2 == 0) std::cout << "Imagem salva em: deslocamento_caso2.png" << std::endl;
    if (r1 != 0 || r2 != 0) std::cerr << "Erro ao executar gnuplot." << std::endl;

    return 0;
}
