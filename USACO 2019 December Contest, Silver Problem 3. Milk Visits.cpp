#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("milkvisits.in");
ofstream fout("milkvisits.out");
 
const int NMAX = 1e5 + 5;
int N, Q, level[NMAX], dp[NMAX][2], ancestor[NMAX][18];
string s;
vector<int> G[NMAX];
 
void dfs(int u, int parent) {
  level[u] = level[parent] + 1;
  for (int i = 0; i < 2; ++i)
    dp[u][i] = dp[parent][i];
  if (s[u - 1] == 'G')
    ++dp[u][0];
  else ++dp[u][1];
  ancestor[u][0] = parent;
  for (int i = 1; i < 18; ++i)
    ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
  for (int v : G[u])
    if (v != parent)
      dfs(v, u);
}
 
int find_lca(int u, int v) {
  if (level[u] < level[v])
    swap(u, v);
  for (int lift = 17; lift >= 0; --lift)
    if (level[u] - (1 << lift) >= level[v])
      u = ancestor[u][lift];
  if (u == v)
    return u;
  for (int lift = 17; lift >= 0; --lift)
    if (ancestor[u][lift] != ancestor[v][lift]) {
      u = ancestor[u][lift];
      v = ancestor[v][lift];
    }
  return ancestor[u][0];
}
 
void solve() {
  fin >> N >> Q >> s;
  for (int i = 1; i < N; ++i) {
    int u, v;
    fin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  dfs(1, 0);
  for (int q = 0; q < Q; ++q) {
    int u, v;
    char req;
    fin >> u >> v >> req;
    int lca = find_lca(u, v), type;
    if (req == 'G')
      type = 0;
    else type = 1;
    if (dp[u][type] + dp[v][type] - (dp[lca][type] << 1) + (s[lca - 1] == req) > 0)
      fout << '1';
    else fout << '0';
  }
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
 
