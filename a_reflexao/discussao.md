# a) Reflexão Temporal — `x_r[n] = x[-n]`

## O que a operação faz

A reflexão temporal, também chamada de **espelhamento** ou **time reversal**, inverte o eixo do tempo de um sinal discreto. Cada amostra que estava no instante `n` é movida para o instante `-n`. O resultado é uma "imagem espelho" do sinal em torno da origem `n = 0`.

**Fórmula:** `x_r[n] = x[-n]`

## O que o gráfico deve mostrar

- Sinal **azul** (`x[n]`): hastes de impulso à **direita** de `n = 0` (domínio `n = 0..N-1`).
- Sinal **laranja** (`x[-n]`): hastes de impulso à **esquerda** de `n = 0` (domínio `n = -(N-1)..0`).
- A amplitude da amostra em `n = 0` é **idêntica** nos dois sinais (ponto fixo da reflexão).
- As demais amostras são espelhos horizontais umas das outras.

## Casos especiais

| Situação | Resultado |
|----------|-----------|
| Sinal simétrico: `x[n] = x[-n]` | Gráficos sobrepostos; sinal par |
| Sinal antissimétrico: `x[n] = -x[-n]` | Hastes invertidas; sinal ímpar |
| `N = 1` | Apenas uma amostra em `n=0`; reflexão não altera nada |

## Aplicações práticas

- Implementação de filtros FIR lineares de fase
- Correlação cruzada e autocorrelação
- Processamento de imagens (espelhamento)
