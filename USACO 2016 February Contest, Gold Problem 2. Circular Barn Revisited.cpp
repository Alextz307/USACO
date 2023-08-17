#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("cbarn2.in");
ofstream fout("cbarn2.out");
 
const int INF = 1e16L;
 
void min_self(int &a, int b) {
  a = min(a, b);
}
 
void solve() {
  int N, K;
  fin >> N >> K;
  vector<int> req(N + 1);
  for (int i = 1; i <= N; ++i)
    fin >> req[i];
  int ans = INF;
  for (int rep = 0; rep < N; ++rep) {
    vector<vector<int>> dp(K + 1, vector<int>(N + 2, INF));
    dp[0][N + 1] = 0;
    for (int k = 1; k <= K; ++k) {
      for (int i = 1; i <= N; ++i) {
        int add = 0;
        for (int j = i + 1; j <= N + 1; ++j) {
          add += (j - 1 - i) * req[j - 1];
          min_self(dp[k][i], dp[k - 1][j] + add);
        }
      }
    }
    min_self(ans, dp[K][1]);
    int aux = req[1];
    for (int i = 2; i <= N; ++i)
      req[i - 1] = req[i];
    req[N] = aux;
  }
  fout << ans << '\n';
}
 
void close_files() {
  fin.close();
  fout.close();
}
 
int32_t main() {
  solve();
  close_files();
  return 0;
}
 
