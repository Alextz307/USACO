#include <bits/stdc++.h>
 
using namespace std;
using int64 = long long;
 
ifstream fin("snowcow.in");
ofstream fout("snowcow.out");
 
struct SegTree {
  int Size;
  vector<int64> tree;
  vector<int> lazy;
 
  SegTree(int n) {
    Size = 1;
    while (Size < n)
      Size <<= 1;
    tree.resize(Size << 1);
    lazy.resize(Size << 1);
  }
 
  void push(int x, int lx, int rx) {
    if (lazy[x] == 0)
      return;
    int mid = (lx + rx) >> 1;
    int64 l[] = {mid - lx + 1, rx - mid};
    for (int i = 0; i < 2; ++i) {
      int son = x << 1 | i;
      tree[son] += l[i] * lazy[x];
      lazy[son] += lazy[x];
    }
    lazy[x] = 0;
  }
 
  void update(int x, int lx, int rx, int st, int dr, bool type) {
    if (st <= lx && rx <= dr) {
      if (type) {
        tree[x] += rx - lx + 1;
        ++lazy[x];
      } else {
        tree[x] -= rx - lx + 1;
        --lazy[x];
      }
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (st <= mid)
      update(lSon, lx, mid, st, dr, type);
    if (mid < dr)
      update(rSon, mid + 1, rx, st, dr, type);
    tree[x] = tree[lSon] + tree[rSon];
  }
 
  int64 query(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x];
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    int64 ans = 0;
    if (st <= mid)
      ans += query(x << 1, lx, mid, st, dr);
    if (mid < dr)
      ans += query(x << 1 | 1, mid + 1, rx, st, dr);
    return ans;
  }
};
 
const int MAXN = 1e5;
vector<int> G[MAXN];
int timer, l[MAXN], r[MAXN];
 
void dfs(int u, int p) {
  l[u] = ++timer;
  for (int v : G[u])
    if (v != p)
      dfs(v, u);
  r[u] = timer;
}
 
int main() {
  int n, Q;
  fin >> n >> Q;
  for (int i = 1; i < n; ++i) {
    int u, v;
    fin >> u >> v;
    --u, --v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  dfs(0, -1);
  set<pair<int,int>> nodes[MAXN];
  SegTree tree(n);
  for (int q = 0; q < Q; ++q) {
    int t, u;
    fin >> t >> u;
    --u;
    if (t == 1) {
      int c;
      fin >> c;
      --c;
      auto it = nodes[c].upper_bound(make_pair(l[u], 0));
      if (it != nodes[c].begin() && prev(it)->second >= r[u])
        continue;
      while (it != end(nodes[c]) && it->second <= r[u]) {
        tree.update(1, 1, n, it->first, it->second, false);
        nodes[c].erase(it++);
      }
      tree.update(1, 1, n, l[u], r[u], true);
      nodes[c].emplace(l[u], r[u]);
    } else fout << tree.query(1, 1, n, l[u], r[u]) << '\n';
  }
  fin.close();
  fout.close();
  return 0;
}
 
