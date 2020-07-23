from queue import Queue


def topological_sort(in_adj, out_adj):
    def explore(v):
        if v not in visited:
            frontier.put(v)
        while not frontier.empty():
            v = frontier.get()
            order[i[0]] = v
            i[0] += 1
            visited.add(v)
            for u in out_adj[v]:
                pred[u] -= 1
                if pred[u] == 0:
                    frontier.put(u)

    order = {}
    pred = {v: len(in_adj[v]) for v in in_adj}
    frontier = Queue()
    visited = set()
    i = [1]
    for v in in_adj:
        if pred[v] == 0:
            explore(v)
    return order
