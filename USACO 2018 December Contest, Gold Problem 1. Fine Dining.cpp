#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("dining.in");
ofstream fout("dining.out");
 
const int MAXN = 5e4 + 1;
vector<pair<int,int>> G[MAXN];
int node[MAXN], cost[MAXN], dp[MAXN], d[MAXN];
 
void Dijkstra(int n) {
  for (int u = 0; u < n; ++u)
    dp[u] = INF;  
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.emplace(0, n);
  while (!pq.empty()) {
    int d, u;
    tie(d, u) = pq.top();
    pq.pop();
    if (dp[u] != d)
      continue;
    for (auto it : G[u]) {
      int v, w;
      tie(v, w) = it;
      if (dp[v] > d + w) {
        dp[v] = d + w;
        pq.emplace(dp[v], v);
      }
    }
  }
}
 
int main() {
  int n, m, k;
  fin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    fin >> u >> v >> w;
    --u, --v;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  for (int i = 0; i < k; ++i) {
    fin >> node[i] >> cost[i];
    --node[i];
  }
  Dijkstra(n - 1);
  for (int u = 0; u < n - 1; ++u)
    d[u] = dp[u];
  for (int i = 0; i < k; ++i)
    G[n].emplace_back(node[i], d[node[i]] - cost[i]);
  Dijkstra(n);
  for (int u = 0; u < n - 1; ++u)
    if (dp[u] <= d[u])
      fout << "1\n";
    else fout << "0\n";
  fin.close();
  fout.close();
  return 0;
}
 
