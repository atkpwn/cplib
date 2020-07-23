from queue import PriorityQueue

INF = 2**64


def dijkstra(adj, u):
    q = PriorityQueue()
    q.put((0, u))
    dist = {v: INF for v in adj}
    prev = {v: set() for v in adj}
    dist[u] = 0
    visited = set()
    while not q.empty():
        c, v = q.get()
        if v not in visited:
            for w in adj[v]:
                if dist[v] + adj[v][w] < dist[w]:
                    dist[w] = dist[v] + adj[v][w]
                    prev[w] = {v}
                    q.put((dist[w], w))
                elif dist[v] + adj[v][w] == dist[w]:
                    prev[w].add(v)
            visited.add(v)
    return dist, prev


def bellman_ford(adj, u):
    # Modified from Steven Halim and Felix Halim, "Competitive
    # Programming 2". The original code is writtten in C++.
    n = len(adj)
    V = range(1, n + 1)
    dist = {v: INF for v in adj}
    dist[u] = 0
    for i in range(n):
        for v in V:
            for w in adj[v]:
                dist[w] = min(dist[w], dist[v] + adj[v][w])
    has_negative_cycle = False
    for v in V:
        for w in adj[v]:
            if dist[v] + adj[v][w] < dist[w]:
                has_negative_cycle = True

    return dist, has_negative_cycle


# TODO: all-pairs shortest path
