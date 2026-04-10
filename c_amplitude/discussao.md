# c) Alteração de Amplitude (Ganho) — `y[n] = A · x[n]`

## O que a operação faz

A alteração de amplitude é uma operação **linear ponto a ponto**: cada amostra do sinal é multiplicada pelo fator escalar `A`. Não altera a posição temporal das amostras, apenas sua magnitude (e possivelmente direção).

**Fórmula:** `y[n] = A · x[n]`

## O que o gráfico deve mostrar

| Valor de A | Efeito visual |
|------------|---------------|
| `A > 1` | Hastes **maiores** que o original (amplificação) |
| `0 < A < 1` | Hastes **menores** (atenuação) |
| `A = 1` | Sinais **idênticos** (ganho unitário) |
| `A = 0` | Sinal **nulo** — todas as hastes em zero |
| `A = -1` | Sinal **invertido** (reflexão no eixo de amplitude) |
| `A < -1` | Amplificado e invertido |

## Casos especiais

- **A negativo**: inverte a fase do sinal. Hastes que apontavam para cima passam para baixo e vice-versa. Matematicamente equivale a uma rotação de 180° no diagrama de fase.
- **A = 0**: destroys toda informação do sinal (operação irreversível).
- **A muito grande**: risco de **clipping** em sistemas com faixa dinâmica limitada (ex.: áudio de 16 bits).

## Aplicações práticas

- Controle de volume em sistemas de áudio
- Normalização de sinais para faixas específicas
- Atenuação de canal em sistemas de comunicação
- Pré-ênfase / deênfase em rádio FM
