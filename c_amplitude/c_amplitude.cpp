// =============================================================================
// c_amplitude/c_amplitude.cpp — Alteração de Amplitude: y[n] = A * x[n]
// Compilar: g++ c_amplitude.cpp -o c_amplitude
// Executar: ./c_amplitude
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

    std::cout << "=== Alteracao de Amplitude (Ganho) ===" << std::endl;
    std::cout << "Sinal original: N = " << N << " amostras." << std::endl;

    // ---- 2) Ler fator A ----
    double A;
    std::cout << "Fator de ganho A (real): ";
    std::cin >> A;

    // ---- 3) Calcular y[n] = A * x[n] ----
    std::vector<double> y(N);
    for (int n = 0; n < N; n++)
        y[n] = A * x[n];

    // ---- 4) Arquivos .dat ----
    {
        std::ofstream f("original.dat");
        for (int n = 0; n < N; n++)
            f << n << "\t" << x[n] << "\n";
    }
    {
        std::ofstream f("amplificado.dat");
        for (int n = 0; n < N; n++)
            f << n << "\t" << y[n] << "\n";
    }

    // ---- 5) Script gnuplot → PNG ----
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << A;
    std::string A_str = oss.str();

    std::string titulo;
    if (A > 1.0)        titulo = "Amplificacao: y[n] = " + A_str + " * x[n]";
    else if (A > 0.0)   titulo = "Atenuacao: y[n] = " + A_str + " * x[n]";
    else if (A < 0.0)   titulo = "Inversao e Escala: y[n] = " + A_str + " * x[n]";
    else                titulo = "Sinal zerado (A = 0)";

    {
        std::ofstream gp("plot_amplitude.gp");
        gp << "set terminal pngcairo size 900,500 enhanced font 'Sans,12'\n";
        gp << "set output 'amplitude.png'\n";
        gp << "set title '" << titulo << "' font 'Sans,14'\n";
        gp << "set xlabel 'n'\n";
        gp << "set ylabel 'Amplitude'\n";
        gp << "set key top right\n";
        gp << "set grid\n";
        gp << "set style data impulses\n";
        gp << "plot 'original.dat'   using 1:2 lw 3 lc rgb '#0077BB' title 'x[n] (original)', \\\n";
        gp << "     'original.dat'   using 1:2 with points pt 7 ps 1.8 lc rgb '#0077BB' notitle, \\\n";
        gp << "     'amplificado.dat' using 1:2 lw 3 lc rgb '#EE7733' title 'y[n] = A*x[n]', \\\n";
        gp << "     'amplificado.dat' using 1:2 with points pt 7 ps 1.8 lc rgb '#EE7733' notitle\n";
    }

    std::cout << "\nGerando grafico: amplitude.png ..." << std::endl;
    int ret = system("gnuplot plot_amplitude.gp");
    if (ret == 0)
        std::cout << "Imagem salva em: amplitude.png" << std::endl;
    else
        std::cerr << "Erro ao executar gnuplot." << std::endl;

    return 0;
}
