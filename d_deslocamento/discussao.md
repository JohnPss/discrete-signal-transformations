# d) Deslocamento Temporal (Shift) — `y[n] = x[n − k]`

## O que a operação faz

O deslocamento temporal desloca todas as amostras do sinal ao longo do eixo do tempo por `k` posições:

- **`k > 0`** → **atraso**: o sinal aparece mais tarde (desloca para a direita).
- **`k < 0`** → **avanço**: o sinal aparece mais cedo (desloca para a esquerda).

**Fórmula:** `y[n] = x[n − k]`

## Dois casos implementados

### Caso 1 — Domínio fixo `[0, N-1]`

O vetor de saída mantém o mesmo comprimento do original. Amostras que "saem" pela borda são **descartadas** (truncamento). Amostras que entrariam de fora do domínio original são **zero** (zero-padding).

> ⚠️ **Perde informação** quando `k ≠ 0`. A energia do sinal diminui proporcionalmente a `|k|/N`.

### Caso 2 — Domínio expandido

O domínio de plotagem é estendido para incluir os índices `[min(0, k) .. max(N-1, N-1+k)]`. Nenhuma amostra é descartada.

> ✅ **Preserva toda a informação** do sinal original.

## O que os gráficos devem mostrar

| Caso | Gráfico |
|------|---------|
| Caso 1 | Sinal laranja "empurrado" dentro da janela fixa; zeros nas extremidades |
| Caso 2 | Sinal laranja com **mesma forma** do azul, porém transladado horizontalmente por `k` |

## Casos especiais

| Situação | Resultado |
|----------|-----------|
| `k = 0` | `y[n] = x[n]`, sinal inalterado |
| `\|k\| ≥ N` (Caso 1) | Sinal nulo na janela — todo o conteúdo foi "empurrado" para fora |
| `k` muito grande (Caso 2) | Dois sinais sem sobreposição no gráfico |

## Aplicações práticas

- Modelagem de atraso de propagação (linhas de transmissão, canais de rádio)
- Sincronização de sinais em receptores digitais
- Geração de ecos e reverberações em áudio digital
