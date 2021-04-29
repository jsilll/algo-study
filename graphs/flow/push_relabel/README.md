### Intuição:
- Operações mais localizadas do que o método de Ford-Fulkerson
- Não é baseada na identficação de caminhos de aumento.
- Propriedade da conservação de fluxo não é mantida durante a execução do algoritmo.
- Cada vértice contém um reservatório de fluxo
     - Representa excesso de fluxo, e(u)
     - Comçar por enviar todo o fluxo possível de s para vértices adjacentes
- Noção de altura de cada vértice, que evolui com a aplicação do algoritmo
     - Envio de fluxo só de vertices mais altos para vértices mais baixos
     - Fazer subir altura de vértices em caso de necessidade de envio de fluxo.

## Definições

### Pré-Fluxo
f : V^2 -> R
- Verifica restrições de capacidade, simetria e f(V, u) >= 0 para vértices u pertencentes a V - {s}
- Não verifica necessariamente a conservação de fluxo

### Excesso de fluxo
e(u) = sum(f(v, u)) - sum(f(u, v)), for all v in V
- u pertencente a S - {s, t} transborda se e(u) > 0

### Altura de um vértice
Uma função h : V -> N é uma função de alturas se h(s) = |V|,
h(t) = 0, e h(u) <= h(v) + 1 para todo o arco residual (u, v) pertencente a Ef.
- Função de alturas permite estabelecer condições para ser possível enviar fluxo de u para v.

## Push Relabel
Assumir que o fluxo que entra é maior do que o que sai dos vértices:
sum(f(v, u)) >= sum(f(u, v)), for all v in V

Enquanto há, pelo menos, um vértice com excesso de fluxo no grafo empurrar esse fluxo para o vértice adjacente de altura - 1, ou se esse vértice nao existir fazer relabel.

### Invariantes
1. f é um pré-fluxo
1. para qualquer aresta (u,v) pertencente à rede residual, h[u] =< h[v] + 1
1. Se 2 se verifica então não existe um caminho entre s e t na rede residual.

Através de 3 e do Teorema de Fluxo Máximo Corte Mínimo garantimos que quando o algoritmo acaba f é um fluxo máximo garantidamente.