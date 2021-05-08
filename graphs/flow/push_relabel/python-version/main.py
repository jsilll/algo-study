from graph import Graph

g = Graph(6)
g.addEdge(0, 1, 8)
g.addEdge(0, 3, 7)
g.addEdge(1, 2, 5)
g.addEdge(1, 4, 3)
g.addEdge(2, 5, 3)
g.addEdge(3, 4, 4)
g.addEdge(4, 2, 4)
g.addEdge(4, 5, 5)

prio_lists = [
    [1, [2, 4, 0]],
    [2, [5, 1, 4]],
    [3, [4, 0]],
    [4, [5, 2, 1, 3]],
]

L0 = [3, 1, 2, 4]

g.relabelToFront(0, 6, prio_lists=prio_lists, L=L0)
