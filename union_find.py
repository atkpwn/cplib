class UnionFind:

    def __init__(self, n):
        self.pset = {i: i for i in range(n)}

    def get_sets(self):
        return set(self.pset.values())

    def find(self, i):
        if not self.pset[i] == i:
            self.pset[i] = self.find(self.pset[i])
            return self.pset[i]
        else:
            return i

    def union(self, i, j):
        self.pset[self.find(i)] = self.find(j)
