# =============================================================================
# Makefile — Manipulação de Sinais Discretos
# Uso: make all    → compila todos os programas
#      make demo   → compila + executa com entradas de exemplo → gera PNGs
#      make clean  → remove executáveis, .dat, .gp e .png de todas as pastas
# =============================================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -O2

.PHONY: all demo clean \
        a_reflexao b_escala c_amplitude d_deslocamento e_degrau

all: a_reflexao b_escala c_amplitude d_deslocamento e_degrau

a_reflexao:
	$(CXX) $(CXXFLAGS) a_reflexao/a_reflexao.cpp -o a_reflexao/a_reflexao

b_escala:
	$(CXX) $(CXXFLAGS) b_escala/b_escala.cpp -o b_escala/b_escala

c_amplitude:
	$(CXX) $(CXXFLAGS) c_amplitude/c_amplitude.cpp -o c_amplitude/c_amplitude

d_deslocamento:
	$(CXX) $(CXXFLAGS) d_deslocamento/d_deslocamento.cpp -o d_deslocamento/d_deslocamento

e_degrau:
	$(CXX) $(CXXFLAGS) e_degrau/e_degrau.cpp -o e_degrau/e_degrau

# -----------------------------------------------------------------------------
# demo: compila (se necessário) e executa todos com entradas de exemplo
#   a) reflexao   — N=6, amplitudes: 0 1 2 3 2 1
#   b) escala     — M=2  (compressao)
#   c) amplitude  — A=2.5
#   d) deslocamento — k=2 (atraso)
#   e) degrau     — A=1.5
# -----------------------------------------------------------------------------
demo: all
	@echo ">>> a) Reflexao (N=6, x=[0 1 2 3 2 1])"
	@cd a_reflexao && printf "6\n0\n1\n2\n3\n2\n1\n" | ./a_reflexao
	@echo ""
	@echo ">>> b) Escala (M=2, compressao)"
	@cd b_escala && printf "2\n" | ./b_escala
	@echo ""
	@echo ">>> c) Amplitude (A=2.5)"
	@cd c_amplitude && printf "2.5\n" | ./c_amplitude
	@echo ""
	@echo ">>> d) Deslocamento (k=2)"
	@cd d_deslocamento && printf "2\n" | ./d_deslocamento
	@echo ""
	@echo ">>> e) Degrau (A=1.5)"
	@cd e_degrau && printf "1.5\n" | ./e_degrau
	@echo ""
	@echo "=== Imagens geradas ==="
	@find . -name "*.png" | sort

clean:
	rm -f a_reflexao/a_reflexao    a_reflexao/*.dat    a_reflexao/*.gp    a_reflexao/*.png
	rm -f b_escala/b_escala        b_escala/*.dat      b_escala/*.gp      b_escala/*.png
	rm -f c_amplitude/c_amplitude  c_amplitude/*.dat   c_amplitude/*.gp   c_amplitude/*.png
	rm -f d_deslocamento/d_deslocamento d_deslocamento/*.dat d_deslocamento/*.gp d_deslocamento/*.png
	rm -f e_degrau/e_degrau        e_degrau/*.dat      e_degrau/*.gp      e_degrau/*.png
