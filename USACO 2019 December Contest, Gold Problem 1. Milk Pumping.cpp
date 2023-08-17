#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
using ld = long double;
 
ifstream fin("pump.in");
ofstream fout("pump.out");
 
const int MAXN = 1e3;
vector<pair<int,int>> G[MAXN];
int w[MAXN], f[MAXN], dp[MAXN], prv[MAXN], flow[MAXN];
 
struct raport {
  int x, y;
 
  bool operator > (const raport &A) const {
    return x * A.y > y * A.x;
  }
};
 
void min_self(int &x, int y) {
  x = min(x, y);
}
 
void Dijkstra(int n, int low) {
  for (int u = 0; u < n; ++u)
    dp[u] = prv[u] = INF;
  dp[0] = 0;
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.emplace(0, 0);
  while (!pq.empty()) {
    int d, u;
    tie(d, u) = pq.top();
    pq.pop();
    if (dp[u] != d)
      continue;
    for (auto it : G[u]) {
      int v, e;
      tie(v, e) = it;
      if (f[e] < low)
        continue;
      if (dp[v] > d + w[e]) {
        dp[v] = d + w[e];
        prv[v] = u;
        flow[v] = f[e];
        pq.emplace(dp[v], v);
      }
    }
  }
}
 
int main() {
  int n, m;
  fin >> n >> m;
  set<int> F;
  for (int i = 0; i < m; ++i) {
    int u, v;
    fin >> u >> v >> w[i] >> f[i];
    --u, --v;
    G[u].emplace_back(v, i);
    G[v].emplace_back(u, i);
    F.emplace(f[i]);
  }
  raport ans{0, 1};
  for (int flow_rate : F) {
    Dijkstra(n, flow_rate);
    if (dp[n - 1] == INF)
      break;
    raport path{INF, dp[n - 1]};
    int node = n - 1;
    while (prv[node] != INF) {
      min_self(path.x, flow[node]);
      node = prv[node];
    }
    if (path > ans)
      ans = path;
  }
  fout << int(1e6 * (ld)ans.x / ans.y) << '\n';
  return 0;
}
 
