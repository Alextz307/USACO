#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("problem248.in");
ofstream fout("problem248.out");
 
const int MAXN = 250;
int dp[MAXN][MAXN];
 
void max_self(int &x, int y) {
  if (x < y) {
    x = y;
  }
}
 
void test_case() {
  int n;
  fin >> n;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    fin >> dp[i][i];
    max_self(ans, dp[i][i]);
  }
  for (int len = 2; len <= n; ++len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int j = i + len - 1;
      dp[i][j] = -1;
      for (int k = i; k <= j - 1; ++k) {
        if (dp[i][k] == dp[k + 1][j] && dp[i][k] >= 0) {
          max_self(dp[i][j], dp[i][k] + 1);
        }
      }
      max_self(ans, dp[i][j]);
    }
  }
  fout << ans << '\n';
}
 
int main() {
  int t = 1;
  for (int tc = 1; tc <= t; ++tc) {
    test_case();
  }
  fin.close();
  fout.close();
  return 0;
}
 
