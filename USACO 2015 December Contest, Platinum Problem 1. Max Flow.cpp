#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("maxflow.in");
ofstream fout("maxflow.out");
 
const int MAXN = 5e4 + 1;
const int MAXM = MAXN << 1;
const int LGMAX = 17;
vector<int> G[MAXN];
int M, p[MAXN], tour[MAXM], first[MAXN], depth[MAXN], lg2[MAXM], rmq[MAXM][LGMAX], dp[MAXN], ans;
 
void max_self(int &x, int y) {
  x = max(x, y);
}
 
void dfs1(int u, int parent) {
  p[u] = parent;
  tour[++M] = u;
  first[u] = M;
  for (int v : G[u])
    if (v != parent) {
      depth[v] = depth[u] + 1;
      dfs1(v, u);
      tour[++M] = u;
    }
}
 
void compute_rmq() {
  for (int i = 1; i <= M; ++i) {
    rmq[i][0] = tour[i];
    if (i > 1)
      lg2[i] = lg2[i >> 1] + 1;
  }
  for (int j = 1; (1 << j) <= M; ++j)
    for (int i = 1; i + (1 << j) - 1 <= M; ++i) {
      int l = 1 << (j - 1);
      int u = rmq[i][j - 1], v = rmq[i + l][j - 1];
      if (depth[u] < depth[v])
        rmq[i][j] = u;
      else rmq[i][j] = v;
    }
}
 
int find_lca(int x, int y) {
  int l = first[x], r = first[y];
  if (l > r)
    swap(l, r);
  int diff = r - l + 1;
  int k = lg2[diff];
  int shift = diff - (1 << k);
  int u = rmq[l][k], v = rmq[l + shift][k];
  if (depth[u] < depth[v])
    return u;
  return v;
}
 
void dfs2(int u) {
  for (int v : G[u])
    if (v != p[u]) {
      dfs2(v);
      dp[u] += dp[v];
    }
  max_self(ans, dp[u]);
}
 
int main() {
  int n, m;
  fin >> n >> m;
  for (int i = 1; i < n; ++i) {
    int u, v;
    fin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  dfs1(1, 0);
  compute_rmq();
  for (int i = 0; i < m; ++i) {
    int u, v;
    fin >> u >> v;
    int lca = find_lca(u, v);
    ++dp[u], ++dp[v], --dp[lca], --dp[p[lca]];
  }
  dfs2(1);
  fout << ans << '\n';
  fin.close();
  fout.close();
  return 0;
}
 
