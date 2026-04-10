# Manipulação de Sinais Discretos Unidimensionais

Cinco programas independentes em C++ para operações fundamentais sobre sinais discretos, com plotagem automática via **gnuplot** (saída em PNG).

## Estrutura do Projeto

```
discrete-signal-transformations/
├── README.md              ← este arquivo
├── Makefile               ← compila todos com `make all`
├── a_reflexao/
│   ├── a_reflexao.cpp     ← código-fonte
│   └── discussao.md       ← teoria e resultados esperados
├── b_escala/
│   ├── b_escala.cpp
│   └── discussao.md
├── c_amplitude/
│   ├── c_amplitude.cpp
│   └── discussao.md
├── d_deslocamento/
│   ├── d_deslocamento.cpp
│   └── discussao.md
└── e_degrau/
    ├── e_degrau.cpp
    └── discussao.md
```

## Dependências

| Ferramenta | Instalação |
|-----------|-----------|
| `g++` (C++17) | `sudo apt install g++` |
| `gnuplot` | `sudo apt install gnuplot` |

## Como compilar

### Todos de uma vez (a partir da raiz do projeto):

```bash
make all
```

### Individualmente (dentro da pasta):

```bash
cd a_reflexao
g++ -std=c++17 -Wall -O2 a_reflexao.cpp -o a_reflexao
```

## Como executar cada programa

Todos os programas devem ser executados **de dentro da sua própria pasta**
(os arquivos `.dat`, `.gp` e a imagem `.png` são gerados no diretório atual).

---

### a) Reflexão Temporal

```bash
cd a_reflexao
./a_reflexao
```

**Entradas solicitadas:**
1. `N` — tamanho do sinal
2. `N` amplitudes `x[0]`, `x[1]`, ..., `x[N-1]`

**Saída:** `reflexao.png`

**Exemplo de entrada:**
```
N = 5
x[0]=1  x[1]=2  x[2]=3  x[3]=4  x[4]=5
```

---

### b) Mudança de Escala Temporal

```bash
cd b_escala
./b_escala
```

**Entrada solicitada:**
- `M` — fator de escala inteiro
  - `M > 1` → compressão (ex: `2`)
  - `M < -1` → expansão (ex: `-2`)

> O sinal de entrada é hardcoded (senoide de 8 amostras).

**Saída:** `escala.png`

---

### c) Alteração de Amplitude

```bash
cd c_amplitude
./c_amplitude
```

**Entrada solicitada:**
- `A` — fator de ganho real (ex: `2.5`, `0.5`, `-1`)

**Saída:** `amplitude.png`

---

### d) Deslocamento Temporal

```bash
cd d_deslocamento
./d_deslocamento
```

**Entrada solicitada:**
- `k` — deslocamento inteiro (positivo = atraso, negativo = avanço)

**Saídas:** dois gráficos separados:
- `deslocamento_caso1.png` — domínio fixo com truncamento/zeros
- `deslocamento_caso2.png` — domínio expandido (sem perda de informação)

---

### e) Soma com Degrau Unitário

```bash
cd e_degrau
./e_degrau
```

**Entrada solicitada:**
- `A` — amplitude do degrau

**Saída:** `degrau.png` (3 sinais no mesmo gráfico: original, degrau e soma)

---

## Resumo das Operações

| Programa | Operação | Entrada | Imagem gerada |
|----------|----------|---------|---------------|
| `a_reflexao` | `x_r[n] = x[-n]` | N + amplitudes | `reflexao.png` |
| `b_escala` | `y[n] = x[Mn]` ou zeros | Fator M | `escala.png` |
| `c_amplitude` | `y[n] = A·x[n]` | Ganho A | `amplitude.png` |
| `d_deslocamento` | `y[n] = x[n−k]` | Shift k | `deslocamento_caso1/2.png` |
| `e_degrau` | `y[n] = x[n] + A·u[n]` | Amplitude A | `degrau.png` |

## Limpeza

```bash
make clean   # remove executáveis, .dat, .gp e .png de todas as pastas
```
