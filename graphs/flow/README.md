Uma rede de fluxo é um grafo dirigido em que cada arco (u,v) corresponde uma capacidade c(u,v)
Tem dois vértices especiais, a fonte e o destino (sumidouro/sink)
Todos os vértices de G pertencem a um caminho de s para t (é tudo um scc)
O grafo é ligado, |E| >= |V| - 1

Um fluxo de G = (V, E) é uma funcao f:V^2 -> R tal que:
f(u,v) <= c(u,v), f(u,v) = -f(v, u)
sum(f(u,v)) for all u,v in G - {source, sink} = 0

Algoritmo de fluxo maximo, uma fonte e um destino
Se houver mais do que um destino e/ou mais do que uma fonte
definir uma super fonte que se fornece todas as fontes e as capacidades das arestas sao infinitas
definir um suer destino ao qual se ligam todos os destinos, com cada uma das arestas com capacidade infinita

Valor do fluxo : |sum(f(s,v)) for all v in G|
por outras palavras, é a soma dos fluxos que saem da source

Fluxo Máximo : soma das capacidadades das arestas que acabam no sink

Capacidade de residual de uma aresta é o fluxo adicional que ainda se pode
envia de u para v cf(u,v) = c(u,v) - f(u,v)

Rede residual é a rede original onde só aparecem as arestas que ainda
podem ser aumentadas com peso igual à capacidade residual da aresta original (cf > 0)
aparecem, tambem, novas arestas com sentido contrario, a estas que correspondem ao fluxo já
presente na aresta no grafo original, caso este seja, tambem maior do que 0.

Um caminho de aumento, é um caminho simples de s para t na rede residual de Gt
A capacidade residual de um caminho de aumento é definida por:
min{cf(u, v)}

A capacidade residual de um caminho é dada pela capacidade
residual minima dos arcos pertencentes a esse caminho

Um corte (S,T) de G = (V, E) é uma partição de V em S e T = V - S, tal que
s pertence a S e t pertence a T
fluxo líquido do corte (S, T): f(S, T) = sum(sum(f(u,v))) for all u in E, for all v in T
capacidade do corte (S, T): c(S, T) = sum(sum(c(u,v))) for all u in E, for all v in T

f(u, V) = 0 for all u in S - {s}, conservação de fluxo nos vértices intermédios

Ver o corte minimo aka ver ate onde se consegue empurrar mais agua para a frente

Metodo de Ford-Fulkerson (nao algoritmo, pois nao define como encontrar o caminho de aumento)
Em loop:
Calcular a rede residual, encontrar um caminho de aumento
aumentar o fluxo atraves desse caminho
caso nao haja um caminho já chegámos ao fluxo máximo e podemos encontrar
o corte mínimo