class DictTrie:
    # Modified from https://stackoverflow.com/a/11016430
    def __init__(self):
        self.root = {}

    def insert(self, word):
        u = self.root
        for c in word:
            u = u.setdefault(c, {})
        u['end'] = {}

    def lookup(self, word):
        u = self.root
        for c in word:
            if c not in u:
                return False
            u = u[c]
        return ('end' in u)
