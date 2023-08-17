#include <bits/stdc++.h>
 
using namespace std;
using int64 = long long;
 
ifstream fin("barnpainting.in");
ofstream fout("barnpainting.out");
 
const int mod = 1e9 + 7;
const int MAXN = 1e5;
vector<int> G[MAXN];
int dp[MAXN][3];
 
void add_self(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
 
void dfs(int u, int p) {
  for (int v : G[u])
    if (v != p) {
      dfs(v, u);
      for (int c1 = 0; c1 < 3; ++c1) {
        int sum = 0;
        for (int c2 = 0; c2 < 3; ++c2)
          if (c2 != c1)
            add_self(sum, dp[v][c2]);
        dp[u][c1] = (int64)dp[u][c1] * sum % mod;
      }
    }
}
 
int main() {
  int n, k;
  fin >> n >> k;
  for (int i = 1; i < n; ++i) {
    int u, v;
    fin >> u >> v;
    --u, --v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  for (int u = 0; u < n; ++u)
    for (int c = 0; c < 3; ++c)
      dp[u][c] = 1;
  for (int i = 0; i < k; ++i) {
    int u, c;
    fin >> u >> c;
    --u, --c;
    for (int col = 0; col < 3; ++col)
      if (col != c)
        dp[u][col] = 0;
  }
  dfs(0, -1);
  int ans = 0;
  for (int c = 0; c < 3; ++c)
    add_self(ans, dp[0][c]);
  fout << ans;
  fin.close();
  fout.close();
  return 0;
}
 
