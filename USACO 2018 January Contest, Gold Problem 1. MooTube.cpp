#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("mootube.in");
ofstream fout("mootube.out");
 
struct edge {
  int u, v, w;
 
  void read() {
    fin >> u >> v >> w;
  }
 
  bool operator < (const edge &A) const {
    return w > A.w;
  }
};
 
struct qry {
  int k, v, ind;
 
  bool operator < (const qry &A) const {
    return k > A.k;
  }
};
 
struct DSU {
  vector<int> p, r;
 
  DSU(int N) {
    p.resize(N + 1);
    r.assign(N + 1, 1);
    iota(p.begin(), p.end(), 0);
  }
 
  int get(int x) {
    if (x == p[x])
      return x;
    return p[x] = get(p[x]);
  }
 
  int get_size(int u) {
    return r[get(u)];
  }
 
  bool unite(int u, int v) {
    int x = get(u), y = get(v);
    if (x == y)
      return false;
    if (r[x] > r[y]) {
      p[y] = x;
      r[x] += r[y];
    } else {
      p[x] = y;
      r[y] += r[x];
    }
    return true;
  }
};
 
void solve() {
  int N, Q;
  fin >> N >> Q;
  vector<edge> edges(N - 1);
  for (edge &e : edges)
    e.read();
  sort(edges.begin(), edges.end());
  vector<qry> queries(Q);
  for (int i = 0; i < Q; ++i) {
    fin >> queries[i].k >> queries[i].v;
    queries[i].ind = i;
  }
  sort(queries.begin(), queries.end());
  vector<int> sol(Q);
  int p = 0;
  DSU tree(N);
  for (const qry &q : queries) {
    while (p < N - 1 && edges[p].w >= q.k) {
      tree.unite(edges[p].u, edges[p].v);
      ++p;
    }
    sol[q.ind] = tree.get_size(q.v) - 1;
  }
  for (const int &x : sol)
    fout << x << '\n';
}
 
void close_files() {
  fin.close();
  fout.close();
}
 
int main() {
  solve();
  close_files();
  return 0;
}
 
