# e) Soma com Degrau Unitário Escalonado — `y[n] = x[n] + A·u[n]`

## O que a operação faz

O **degrau unitário** `u[n]` é definido como:

```
u[n] = 1,  n ≥ 0
u[n] = 0,  n < 0
```

Ao somar `A·u[n]` ao sinal `x[n]`, adicionamos uma **componente DC constante** de amplitude `A` a partir de `n = 0`. O sinal é literalmente "levantado" (ou "abaixado" se `A < 0`) nessa região.

**Fórmula:** `y[n] = x[n] + A·u[n]`

## O que o gráfico deve mostrar (3 sinais)

| Cor | Sinal | Comportamento |
|-----|-------|---------------|
| 🔵 Azul | `x[n]` (original) | Qualquer forma; definido para `n = 0..N-1` |
| 🟢 Verde | `A·u[n]` (degrau) | Zero para `n < 0`; constante `A` para `n ≥ 0` |
| 🟠 Laranja | `y[n]` (soma) | Igual a `x[n]` para `n < 0`; levantado por `A` para `n ≥ 0` |

A transição em `n = 0` é marcada por uma linha tracejada vertical no gráfico.

## Casos especiais

| Situação | Resultado |
|----------|-----------|
| `A = 0` | `y[n] = x[n]`; degrau é zero |
| `A > 0` | Sinal levantado — offset positivo a partir de `n = 0` |
| `A < 0` | Sinal rebaixado — offset negativo a partir de `n = 0` |
| `A = -x[0]` | A amostra `y[0]` passa exatamente por zero |

## Aplicações práticas

- Modelagem de tensão de offset introduzida ao ligar um circuito
- Adição de bias DC em sinais de sensores
- Representação de funções degrau em sequências binárias digitais
- Base para síntese de formas de onda compostas (degrau + rampa + impulso)
