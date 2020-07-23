from union_find import UnionFind


def build_mst(n, edges):
    # edge (w, (u, v))
    tree_edges = []
    pset = UnionFind(n + 1)
    edges.sort()
    for w, e in edges:
        u, v = e
        if pset.find(u) != pset.find(v):
            pset.union(u, v)
            tree_edges.append((u, v))
    return tree_edges
