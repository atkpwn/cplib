#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

/*
 * Modified from Dinitz's algorithm implementation by
 * https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
 * The breadth first search start from the sink following the
 * recommendation of Boris Cherkassky mentioned in the paper of Yefim
 * Dinitz (author of the Dinic's algorithm)
 * https://www.cs.bgu.ac.il/~dinitz/Papers/Dinitz_alg.pdf
 *
 * NOTE: Multiple edges between vertices might cause bug!
*/

typedef long long ll;
typedef pair<int, int> ii;
struct Edge{
  int dest;
  int cap;
  ll flow;
  Edge(int d, int c, ll f): dest(d), cap(c), flow(f) {}
};

const ll INF = 1L<<60;

class Dinitz {
 private:
  vector<vector<int>> adj;
  vector<Edge> edges;
  vector<int> ranks;
  vector<int> last;
  int N;

  bool bfs(int s, int t) {
    ranks.assign(N, -1);
    ranks[t] = 0;
    queue<int> q;
    q.push(t);
    while (q.size() > 0) {
      auto u = q.front();
      q.pop();
      for (auto& id: adj[u])
        if (edges[id ^ 1].cap - edges[id ^ 1].flow > 0 && ranks[edges[id].dest] == -1) {
          ranks[edges[id].dest] = ranks[u] + 1;
          q.push(edges[id].dest);
        }
    }
    return (ranks[s] != -1);
  }

  int dfs(int u, int t, ll aug=INF) {
    if (u == t || aug == 0)
      return aug;
    for (auto& i = last[u]; i < (int) adj[u].size(); i++) {
      auto& e = edges[adj[u][i]];
      auto& v = e.dest;
      if (ranks[v] == ranks[u] - 1 && e.cap - e.flow > 0) {
        auto pushed = dfs(v, t, min(aug, e.cap - e.flow));
        if (pushed) {
          e.flow += pushed;
          auto& r = edges[adj[u][i] ^ 1];
          r.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

 public:
  Dinitz(int N): N(N) {
    adj.assign(N, vector<int>());
  }

  void add_edge(int u, int v, ll w=1) {
    edges.push_back(Edge(v, w, 0));
    adj[u].push_back(edges.size() - 1);
    edges.push_back(Edge(u, 0, 0));
    adj[v].push_back(edges.size() - 1);
  }

  ll max_flow(int s, int t) {
    ll mf = 0;
    while (bfs(s, t)) {
      last.assign(N, 0);
      while (auto flow = dfs(s, t)) {
        mf += flow;
      }
    }
    return mf;
  }
};
