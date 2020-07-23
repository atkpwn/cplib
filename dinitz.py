from queue import Queue

INF = 2**60


class Edge:
    def __init__(self, cap, flow):
        self.cap = cap
        self.flow = flow

    def __repr__(self):
        return '({} / {})'.format(self.flow, self.cap)

    def __gt__(self, other):
        if isinstance(other, Edge):
            return self.flow > other.flow
        return self.cap - self.flow > other


def dinitz(adj, s, t):
    # Modified from Dinitz's algorithm implementation by
    # https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
    # The breadth first search start from the sink following the
    # recommendation of Boris Cherkassky mentioned in the paper of
    # Yefim Dinitz (author of the Dinic's algorithm)
    # https://www.cs.bgu.ac.il/~dinitz/Papers/Dinitz_alg.pdf
    def bfs(s, t):
        rank.clear()
        rank[t] = 0
        q = Queue()
        q.put(t)
        while not q.empty():
            u = q.get()
            for v in adj[u]:
                if v not in rank and adj[v][u] > 0:
                    rank[v] = rank[u] + 1
                    q.put(v)
        return (rank.get(s, -1) != -1)

    def dfs(u, t, aug=INF):
        if u == t or aug == 0:
            return aug
        for v in list(adj[u].keys())[last[u]:]:
            last[u] += 1
            e = adj[u][v]
            if rank.get(v, -1) == rank.get(u, -1) - 1 and e > 0:
                pushed = dfs(v, t, min(aug, e.cap - e.flow))
                if pushed:
                    e.flow += pushed
                    re = adj[v][u]
                    re.flow -= pushed
                    return pushed
        return 0

    rank = {}
    flow = 0
    while bfs(s, t):
        last = {u: 0 for u in adj}
        f = dfs(s, t)
        while f > 0:
            flow += f
            f = dfs(s, t)

    return flow


def add_edge(adj, u, v, capacity=1, twoway=True):
    adj.setdefault(u, {})[v] = Edge(capacity, 0)
    if twoway:
        adj.setdefault(v, {})[u] = Edge(0, 0)


if __name__ == '__main__':
    edges = [(0, 2, 70), (0, 3, 30), (1, 2, 0), (1, 3, 0), (2, 0, 0),
             (2, 1, 25), (2, 3, 5), (3, 0, 1), (3, 1, 70), (3, 2, 0)]
    adj = {}
    for u, v, w in edges:
        add_edge(adj, u, v, w, False)
    f = dinitz(adj, 0, 1)
    print(adj)
    print(f)
