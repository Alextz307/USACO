#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
using int64 = long long;
 
ifstream fin("shortcut.in");
ofstream fout("shortcut.out");
 
const int MAXN = 1e4;
const int MAXM = 5e4;
int64 c[MAXN];
vector<pair<int,int>> G[MAXN];
int dp[MAXN], p[MAXN];
vector<int> tree[MAXN];
 
void min_self(int &x, int y) {
  x = min(x, y);
}
 
void max_self(int64 &x, int64 y) {
  x = max(x, y);
}
 
void Dijkstra(int n) {
  for (int u = 1; u < n; ++u)
    dp[u] = p[u] = INF;
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.emplace(0, 0);
  while (!pq.empty()) {
    int d, u;
    tie(d, u) = pq.top();
    pq.pop();
    if (dp[u] != d)
      continue;
    for (auto it : G[u]) {
      int v, w;
      tie(v, w) = it;
      if (dp[v] >= d + w)
        min_self(p[v], u);
      if (dp[v] > d + w) {
        dp[v] = d + w;
        p[v] = u;
        pq.emplace(dp[v], v);
      }
    }
  }
}
 
void dfs(int u) {
  for (int v : tree[u]) {
    dfs(v);
    c[u] += c[v];
  }
}
 
int main() {
  int n, m, T;
  fin >> n >> m >> T;
  for (int u = 0; u < n; ++u)
    fin >> c[u];
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    fin >> u >> v >> w;
    --u, --v;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  Dijkstra(n);
  for (int u = 1; u < n; ++u)
    tree[p[u]].emplace_back(u);
  dfs(0);
  int64 ans = 0;
  for (int u = 1; u < n; ++u)
    max_self(ans, c[u] * (dp[u] - T));
  fout << ans << '\n';
  fin.close();
  fout.close();
  return 0;
}
 
