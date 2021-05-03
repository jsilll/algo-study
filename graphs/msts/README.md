## Minimum Spanning Trees
Dado um grafo G = (V, E, w) não dirigido e pesado, calcular um subconjunto dos arcos de G, T contido em E, tal que:
- T não contém ciclos
- T abrange todos os vértices de G

W(T) é definido com a soma de todos os pesos de T. Uma árvore abrangente de menor custo (MST) é um a árvore abrangente de peso mínimo.

### Arco Seguro
Seja A um subconjunto de uma MST de um grafo G = (V, E, T), um arco (u, v) diz-se seguro para A sse A + {(u, v)} também é um subconjunto de uma MST de G.

Problema: Como identificar arcos seguros?

### Corte que respeita A
Seja (S, V\S) um corte num grafo G = (V, E, w) e A um subconjunto de uma MST de G, então diz-se que o corte respeita A sse nenhum arco de A cruza (S, V/S).

### Arco leve que cruza o corte
Um arco (u,v) diz-se leve para (S,V\S) sse (u,v) atravessa o corte e:
w(u,v) = min{w(x,y) | (x,y) atravessa (S, V\S)}

### Teorema Arco Leve => Arco Seguro
Cruza o corte => Não causa ciclos, pois vai para um vértice ainda não antes visto
É leve logo é o melhor que se pode escolher