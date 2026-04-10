# b) Mudança de Escala Temporal — Compressão e Expansão

## O que a operação faz

A mudança de escala temporal resameia o sinal no eixo do tempo por um fator inteiro.

### Compressão (`M > 1`): `y[n] = x[Mn]`

Retém apenas **1 de cada M amostras**. O sinal parece "acelerado" — passa pelas mesmas amplitudes em menos amostras.

> ⚠️ Sem filtragem anti-aliasing prévia, a compressão pode causar **aliasing temporal**:
> componentes de alta frequência se dobram sobre as de baixa frequência.

### Expansão (`M < -1`, fator `L = |M|`): inserção de zeros

Insere `L - 1` zeros entre cada amostra original. O sinal parece "dilatado" — as amplitudes originais aparecem espaçadas.

> ℹ️ Expansão + **filtro passa-baixas interpolador** = interpolação ideal (conversão de taxa de amostragem).

## O que o gráfico deve mostrar

| Modo | Gráfico |
|------|---------|
| Compressão | Sinal laranja com **menos hastes**, mais compacto no eixo n |
| Expansão | Sinal laranja com **mais hastes**, maioria em zero, com amostras originais espaçadas |

## Casos especiais

| Situação | Resultado |
|----------|-----------|
| `N` não divisível por `M` (compressão) | Última janela incompleta; amostras descartadas |
| `M = 1` | `y[n] = x[n]`, sinais idênticos |
| Expansão sem filtro | Imagens espectrais — sinal parece "piscando" no domínio da frequência |

## Aplicações práticas

- Conversão de taxa de amostragem (decimação e interpolação)
- Compressão de áudio e vídeo
- Bancos de filtros multirresolução (wavelets)
