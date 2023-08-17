#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("milkvisits.in");
ofstream fout("milkvisits.out");
 
const int NMAX = 1e5 + 1;
int N, Q, v[NMAX], a[NMAX], x[NMAX], y[NMAX], c[NMAX], req;
bool ap[NMAX];
vector<int> G[NMAX];
int p[NMAX], sz[NMAX], depth[NMAX], chain_top[NMAX];
int cnt_labels, label[NMAX];
char sol;
 
struct SegTree {
  int Size;
  vector<unordered_set<int>> tree;
 
  void init(int N) {
    Size = 1;
    while (Size < N)
      Size <<= 1;
    tree.resize(Size << 1 | 1);
  }
 
  void build(int x, int lx, int rx) {
    if (lx == rx) {
      if (ap[a[lx]])
        tree[x].emplace(a[lx]);
      return;
    }
    int mid = (lx + rx) >> 1;
    build(x << 1, lx, mid);
    build(x << 1 | 1, mid + 1, rx);
    for (int i = 0; i < 2; ++i)
      for (int it : tree[x << 1 | i])
        tree[x].emplace(it);
  }
 
  void query(int x, int lx, int rx, int st, int dr) {
    if (sol == '1')
      return;
    if (st <= lx && rx <= dr) {
      if (tree[x].count(req))
        sol = '1';
      return;
    }
    int mid = (lx + rx) >> 1;
    if (st <= mid)
      query(x << 1, lx, mid, st, dr);
    if (sol == '0' && mid < dr)
      query(x << 1 | 1, mid + 1, rx, st, dr);
  }
} tree;
 
void read_input() {
  fin >> N >> Q;
  for (int i = 1; i <= N; ++i)
    fin >> v[i];
  for (int i = 1; i < N; ++i) {
    int u, v;
    fin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  for (int q = 0; q < Q; ++q) {
    fin >> x[q] >> y[q] >> c[q];
    ap[c[q]] = true;
  }
}
 
void dfs_init(int u, int parent) {
  p[u] = parent;
  depth[u] = depth[parent] + 1;
  sz[u] = 1;
  chain_top[u] = u;
  for (int v : G[u])
    if (v != parent) {
      dfs_init(v, u);
      sz[u] += sz[v];
    }
}
 
void dfs_heavy(int u) {
  label[u] = ++cnt_labels;
  int max_size = -1, heavy_son = -1;
  for (int v : G[u])
    if (v != p[u] && sz[v] > max_size) {
      max_size = sz[v];
      heavy_son = v;
    }
  if (heavy_son == -1)
    return;
  chain_top[heavy_son] = chain_top[u];
  dfs_heavy(heavy_son);
  for (int v : G[u])
    if (v != p[u] && v != heavy_son)
      dfs_heavy(v);
}
 
void lca_query(int x, int y) {
  if (sol == '1')
    return;
  if (chain_top[x] == chain_top[y]) {
    if (label[x] > label[y])
      swap(x, y);
    tree.query(1, 1, N, label[x], label[y]);
    return;
  }
  if (depth[p[chain_top[x]]] > depth[p[chain_top[y]]]) {
    tree.query(1, 1, N, label[chain_top[x]], label[x]);
    if (sol == '0')
      lca_query(p[chain_top[x]], y);
    return;
  }
  tree.query(1, 1, N, label[chain_top[y]], label[y]);
  if (sol == '0')
    lca_query(x, p[chain_top[y]]);
}
 
void solve() {
  dfs_init(1, 0);
  dfs_heavy(1);
  tree.init(N);
  for (int i = 1; i <= N; ++i)
    a[label[i]] = v[i];
  tree.build(1, 1, N);
  for (int q = 0; q < Q; ++q) {
    req = c[q];
    sol = '0';
    lca_query(x[q], y[q]);
    fout << sol;
  }
}
 
void close_files() {
  fin.close();
  fout.close();
}
 
int main() {
  read_input();
  solve();
  close_files();
  return 0;
}
 
