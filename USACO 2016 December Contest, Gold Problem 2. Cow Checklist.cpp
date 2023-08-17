#include <bits/stdc++.h>
#define sqr(x) (x) * (x)
 
using namespace std;
 
ifstream fin("checklist.in");
ofstream fout("checklist.out");
 
const int64_t INF = 1e18L;
 
int cost(const pair<int,int> &a, const pair<int,int> &b) {
  return sqr(b.first - a.first) + sqr(b.second - a.second);
}
 
void min_self(int64_t &x, int64_t y) {
  x = min(x, y);
}
 
int main() {
  int n, m;
  fin >> n >> m;
  vector<pair<int,int>> a(n), b(m);
  for (auto &it : a)
    fin >> it.first >> it.second;
  for (auto &it : b)
    fin >> it.first >> it.second;
  vector<vector<vector<int64_t>>> dp(2, vector<vector<int64_t>>(n + 1, vector<int64_t>(m + 1, INF)));
  dp[0][1][0] = 0;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j) {
      int add;
      if (i && j) {
        add = cost(a[i - 1], b[j - 1]);
        min_self(dp[0][i][j], dp[1][i - 1][j] + add);
        min_self(dp[1][i][j], dp[0][i][j - 1] + add);
      }
      if (i > 1) {
        add = cost(a[i - 2], a[i - 1]);
        min_self(dp[0][i][j], dp[0][i - 1][j] + add);
      }
      if (j > 1) {
        add = cost(b[j - 2], b[j - 1]);
        min_self(dp[1][i][j], dp[1][i][j - 1] + add);
      }
    }
  fout << dp[0][n][m] << '\n';
  fin.close();
  fout.close();
  return 0;
}
 
