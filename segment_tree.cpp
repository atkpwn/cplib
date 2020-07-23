#include <cstdio>
#include <vector>

using namespace std;

struct Node {
  int v;
  int l;
  int r;
  int lazy = 0;
  bool islazy = false;
};

class SegmentTree {
  // SegmentTree for Range Sum Query based on the meeting slide 11
 private:
  int build(const vector<int> &data, int p, int l, int r) {
    tree[p].l = l;
    tree[p].r = r;
    if (l == r)
      tree[p].v = data[l];
    else {
      int m = (l + r) / 2;
      int pl = build(data, left(p), l, m);
      int pr = build(data, right(p), m + 1, r);
      tree[p].v = pl + pr;
    }
    return tree[p].v;
  }

  int left(int p) {
    return p << 1;
  }

  int right(int p) {
    return (p << 1) + 1;
  }

  void _add(int p, int i, int v) {
    if (i < tree[p].l || tree[p].r < i)
      return;
    tree[p].v += v;
    if (tree[p].l != tree[p].r) {
      _add(left(p), i, v);
      _add(right(p), i, v);
    }
  }

  void propagate(int p) {
    if (!tree[p].islazy)
      return;
    tree[p].v += (tree[p].r - tree[p].l + 1) * tree[p].lazy;
    if (tree[p].l != tree[p].r) {
      tree[left(p)].lazy += tree[p].lazy;
      tree[left(p)].islazy = true;
      tree[right(p)].lazy += tree[p].lazy;
      tree[right(p)].islazy = true;
    }
    tree[p].lazy = 0;
    tree[p].islazy = false;
  }

  int _sum(int p, int l, int r) {
    if (r < tree[p].l || tree[p].r < l)
      return 0;
    propagate(p);
    if (l <= tree[p].l && tree[p].r <= r)
      return tree[p].v;
    return _sum(left(p), l, r) + _sum(right(p), l, r);
  }

  void _range_add(int p, int l, int r, int v) {
    propagate(p);
    if (r < tree[p].l || tree[p].r < l)
      return;
    if (l <= tree[p].l && tree[p].r <= r) {
      tree[p].lazy += v;
      tree[p].islazy = true;
      propagate(p);
    }
    else if (tree[p].l != tree[p].r) {
      _range_add(left(p), l, r, v);
      _range_add(right(p), l, r, v);
      tree[p].v = tree[left(p)].v + tree[right(p)].v;
    }
  }

 public:
  vector<Node> tree;
  const int root = 1;

  SegmentTree(int n) {
    tree.assign(4 * n, Node());
  }

  SegmentTree(const vector<int> &data): SegmentTree(4 * data.size()){
    build(data, root, 0, data.size() - 1);
  }

  void add(int i, int v) {
    _add(root, i, v);
  }

  int sum(int l, int r) {
    return _sum(root, l, r);
  }

  void range_add(int l, int r, int v) {
    _range_add(root, l, r, v);
  }
};

int main() {
  vector<int> a{1, 6, 5, 2, 4, 2};
  auto st = SegmentTree(a);
  st.add(3, 5);
  for (auto x : st.tree)
    printf("%d ", x.v);
  printf("\n");
  auto st2 = SegmentTree(a);
  st2.range_add(0, 5, 3);
  st2.range_add(0, 4, 2);
  for (auto x : st2.tree)
    printf("%d ", x.v);
  printf("\n");

  return 0;
}
