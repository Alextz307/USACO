#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("taming.in");
ofstream fout("taming.out");
 
const int NMAX = 101;
int N, a[NMAX], dp[NMAX][NMAX][NMAX];
 
void min_self(int &a, int b) {
  a = min(a, b);
}
 
void solve() {
  fin >> N;
  for (int i = 1; i <= N; ++i)
    fin >> a[i];
  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= N; ++j)
      for (int k = 0; k < N; ++k)
        dp[i][j][k] = INF;
  dp[1][1][0] = (a[1] != 0);
  for (int i = 2; i <= N; ++i)
    for (int b = 1; b <= N; ++b) {
      for (int v = 0; v < i; ++v)
        min_self(dp[i][b][0], dp[i - 1][b - 1][v]);
      if (a[i] != 0)
        ++dp[i][b][0];
      for (int v = 1; v < i; ++v)
        dp[i][b][v] = dp[i - 1][b][v - 1] + (a[i] != v);
    }
  for (int b = 1; b <= N; ++b) {
    int ans = INF;
    for (int v = 0; v < N; ++v)
      min_self(ans, dp[N][b][v]);
    fout << ans << '\n';
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
 
