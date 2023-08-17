#include <fstream>
#include <vector>
#include <queue>
 
using namespace std;
 
ifstream fin("timeline.in");
ofstream fout("timeline.out");
 
const int MAXN = 1e5;
int low[MAXN], in_deg[MAXN], dp[MAXN];
vector<pair<int,int>> G[MAXN];
 
void max_self(int &x, int y) {
  x = max(x, y);
}
 
int main() {
  int n, m, k;
  fin >> n >> m >> k;
  for (int u = 0; u < n; ++u)
    fin >> low[u];
  for (int i = 0; i < k; ++i) {
    int u, v, x;
    fin >> u >> v >> x;
    --u, --v;
    ++in_deg[v];
    G[u].emplace_back(v, x);
  }
  queue<int> q;
  for (int u = 0; u < n; ++u)
    if (in_deg[u] == 0)
      q.emplace(u);
  vector<int> top_sort;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    top_sort.emplace_back(u);
    for (auto v : G[u])
      if (--in_deg[v.first] == 0)
        q.emplace(v.first);
  }
  for (int u : top_sort) {
    max_self(dp[u], low[u]);
    for (auto v : G[u])
      max_self(dp[v.first], dp[u] + v.second);
  }
  for (int u = 0; u < n; ++u)
    fout << dp[u] << '\n';
  return 0;
}
 
