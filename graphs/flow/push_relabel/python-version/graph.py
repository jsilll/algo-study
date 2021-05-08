class FlowEdge:
    def __init__(self, u, v, capacity):
        # u : int
        # v : int
        # capacity : int

        self.u = u
        self.v = v
        self.capacity = capacity
        self.flow = 0

    def getU(self):
        return self.u

    def getV(self):
        return self.v

    def getCapacity(self):
        return self.capacity

    def getFlow(self):
        return self.flow

    def getResidualCapacity(self):
        return self.capacity - self.flow

    def setFlow(self, flow):
        # flow : int
        self.flow = flow

    def getPrio(self, prio):
        # prio : list
        if self.u != prio[0]:
            return prio[1].index(self.u)

        else:
            return prio[1].index(self.v)

    def __repr__(self):
        return f"({self.u},{self.v},{self.flow}/{self.capacity})"


class Graph:
    def __init__(self, V):
        self.V = V
        self.adj = []
        for u in range(self.V):
            self.adj.append([])

    def addEdge(self, u, v, capacity):
        self.adj[u].append(FlowEdge(u, v, capacity))

    def push(self, u, v, edge, e, h):
        # v : int
        # u : int
        # edge : FlowEdge()
        # e : list
        # h : list

        new_flow = 0

        # Get max change posible to flow
        # Forward Edge
        if edge.getV() == v:
            new_flow = min(e[u], edge.getResidualCapacity())
            edge.setFlow(edge.getFlow() + new_flow)

        # Backwards Edge
        if edge.getV() == u:
            new_flow = min(e[u], edge.getFlow())
            edge.setFlow(edge.getFlow() - new_flow)

        e[u] -= new_flow
        e[v] += new_flow

    def relabel(self, u, h, N):
        # u : int
        # h : list
        # N : list

        min_height = 2 * self.V + 1
        for edge in N[u]:
            # Forward Edge
            if edge.getV() != u:
                if edge.getResidualCapacity():
                    min_height = min(min_height, h[edge.getV()])

            # Backwards Edge
            elif edge.getFlow():
                min_height = min(min_height, h[edge.getU()])
        h[u] = min_height + 1

    def pushRelabelInitialize(self, s, e, h):
        # s : int
        # e : list
        # h : list

        # Initializing all flows and heights at 0
        for u in range(self.V):
            for edge in self.adj[u]:
                edge.setFlow(0)
            e[u] = 0
            h[u] = 0

        # Pushing all the flow from the edge
        for edge in self.adj[s]:
            e[s] = e[s] - edge.getCapacity()
            e[edge.getV()] = edge.getCapacity()
            edge.setFlow(edge.getCapacity())

        h[s] = self.V

    def discharge(self, u, e, h, N, N_current):
        # u : int
        # e : list
        # h : list
        # N : list
        # N_current : list
        discharged = False
        while e[u] > 0:
            discharged = True
            if N_current[u] == len(N[u]):
                self.relabel(u, h, N)
                N_current[u] = 0

            # Forward Edge
            edge = N[u][N_current[u]]
            if edge.getV() != u:
                if edge.getResidualCapacity() and h[u] == h[edge.getV()] + 1:
                    self.push(u, edge.getV(), edge, e, h)

            # Backwards Edge
            elif edge.getFlow() and h[u] == h[edge.getU()] + 1:
                self.push(u, edge.getU(), edge, e, h)
            N_current[u] += 1

        return discharged

    def relabelToFront(self, s, t, prio_lists=None, L=None):
        # s : int
        # t : int

        e = [0] * self.V
        h = [0] * self.V
        N = [0] * self.V
        N_current = [0] * self.V

        # Forward Edges
        for u in range(self.V):
            N[u] = []
            for edge in self.adj[u]:
                N[u].append(edge)

        # Backwards Edges
        for u in range(self.V):
            for edge in self.adj[u]:
                N[edge.getV()].append(edge)

        # Initialize N List
        if N == None:
            L = []
            for u in range(self.V):
                if u != s and u != t:
                    L.append(u)

        # Organize N lists somehow
        if prio_lists != None:
            for prio_list in prio_lists:
                N[prio_list[0]] = sorted(
                    N[prio_list[0]], key=lambda x: x.getPrio(prio_list))

        self.pushRelabelInitialize(s, e, h)

        i = 0
        while i < len(L):
            u = L[i]
            h_old = h[u]
            if self.discharge(u, e, h, N, N_current):
                # Printing the discharged vertex
                print(f"Discharge {u}")
                print(f"e : {e}")
                print(f"h : {h}")
                print(self)

            if h_old != h[u]:
                L.insert(0, L.pop(i))
                print(L)
                i = 0

            i += 1

    def __repr__(self):
        res = ""
        for u in range(self.V - 1):
            res += f"{u} -> {self.adj[u]}\n"
        res += f"{self.V - 1} -> {self.adj[self.V - 1]}"
        return res
