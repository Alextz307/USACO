
     
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("cowland.in");
ofstream fout("cowland.out");
 
const int NMAX = 1e5 + 5;
int a[NMAX];
 
struct SegTree {
  int Size;
  vector<int> tree;
 
  void init(int N) {
    Size = 1;
    while (Size < N)
      Size <<= 1;
    tree.resize(Size << 1 | 1);
  }
 
  void build(int x, int lx, int rx) {
    if (lx == rx) {
      tree[x] = a[lx];
      return;
    }
    int mid = (lx + rx) >> 1;
    build(x << 1, lx, mid);
    build(x << 1 | 1, mid + 1, rx);
    tree[x] = tree[x << 1] ^ tree[x << 1 | 1];
  }
 
  void update(int x, int lx, int rx, int poz, int val) {
    if (lx == rx) {
      tree[x] = val;
      return;
    }
    int mid = (lx + rx) >> 1;
    if (poz <= mid)
      update(x << 1, lx, mid, poz, val);
    else
      update(x << 1 | 1, mid + 1, rx, poz, val);
    tree[x] = tree[x << 1] ^ tree[x << 1 | 1];
  }
 
  int query(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x];
    int mid = (lx + rx) >> 1, ans1 = 0, ans2 = 0;
    if (st <= mid)
      ans1 = query(x << 1, lx, mid, st, dr);
    if (mid < dr)
      ans2 = query(x << 1 | 1, mid + 1, rx, st, dr);
    return ans1 ^ ans2;
  }
} tree;
 
int N, Q, v[NMAX]; /// numarul de noduri, de query-uri, valorile initiale
vector<int> G[NMAX]; /// arborele
int p[NMAX]; /// tatal nodului
int sz[NMAX]; /// dimensiunea subarborelui cu radacina in nod
int depth[NMAX]; /// adancimea / nivelul in arbore
int chain_top[NMAX]; /// capul chain-ului(cel mai apropiat de radacina nod din chain)
int cnt_labels, label[NMAX]; /// le voi da nodurilor valori astfel incat sa am chain-urile numerotate consecutiv sa pot face aint pe ele
 
void read_input() {
  fin >> N >> Q;
  for (int i = 1; i <= N; ++i)
    fin >> v[i];
  for (int i = 1; i < N; ++i) {
    int x, y;
    fin >> x >> y;
    G[x].emplace_back(y);
    G[y].emplace_back(x);
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
  if(heavy_son == -1)
    return;
  chain_top[heavy_son] = chain_top[u];
  dfs_heavy(heavy_son);
  for (int v : G[u])
    if (v != p[u] && v != heavy_son)
      dfs_heavy(v);
}
 
int lca_query(int x, int y) {
  if (chain_top[x] == chain_top[y]) { /// x si y fac parte din acelasi chain
    if (label[x] > label[y])
      swap(x, y);
    return tree.query(1, 1, N, label[x], label[y]);
  }
  if (depth[p[chain_top[x]]] > depth[p[chain_top[y]]])
    return tree.query(1, 1, N, label[chain_top[x]], label[x]) ^ lca_query(p[chain_top[x]], y);
  return tree.query(1, 1, N, label[chain_top[y]], label[y]) ^ lca_query(x, p[chain_top[y]]);
}
 
void solve() {
  dfs_init(1, 0);
  dfs_heavy(1);
  tree.init(N);
  for (int i = 1; i <= N; ++i)
    a[label[i]] = v[i];
  tree.build(1, 1, N);
  for (int q = 0; q < Q; ++q) {
    int op, x, y;
    fin >> op >> x >> y;
    if (op == 1)
      tree.update(1, 1, N, label[x], y);
    else
      fout << lca_query(x, y) << '\n';
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
 
