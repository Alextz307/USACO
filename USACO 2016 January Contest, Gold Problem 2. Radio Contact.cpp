#include <bits/stdc++.h>
#define sqr(x) (x) * (x)
 
using namespace std;
 
ifstream fin("radio.in");
ofstream fout("radio.out");
 
const int64_t INF = 1e18L;
 
int moveX(char c) {
  if (c == 'E')
    return 1;
  if (c == 'W')
    return -1;
  return 0;
}
 
int moveY(char c) {
  if (c == 'N')
    return 1;
  if (c == 'S')
    return -1;
  return 0;
}
 
int cost(const pair<int,int> &a, const pair<int,int> &b) {
  return sqr(b.first - a.first) + sqr(b.second - a.second);
}
 
void min_self(int64_t &x, int64_t y) {
  x = min(x, y);
}
 
int main() {
  int n, m;
  vector<pair<int,int>> a(1), b(1);
  string s, t;
  fin >> n >> m >> a[0].first >> a[0].second >> b[0].first >> b[0].second >> s >> t;
  for (char c : s) {
    int dx = moveX(c), dy = moveY(c);
    a.emplace_back(a.back().first + dx, a.back().second + dy);
  }
  for (char c : t) {
    int dx = moveX(c), dy = moveY(c);
    b.emplace_back(b.back().first + dx, b.back().second + dy);
  }
  vector<vector<int64_t>> dp(n + 1, vector<int64_t>(m + 1, INF));
  dp[0][0] = 0;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j) {
      int add = cost(a[i], b[j]);
      if (i && j)
        min_self(dp[i][j], dp[i - 1][j - 1] + add);
      if (i)
        min_self(dp[i][j], dp[i - 1][j] + add);
      if (j)
        min_self(dp[i][j], dp[i][j - 1] + add);
    }
  fout << dp[n][m] << '\n';
  fin.close();
  fout.close();
  return 0;
}
