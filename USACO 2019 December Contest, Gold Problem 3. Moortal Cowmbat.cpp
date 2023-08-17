#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("cowmbat.in");
ofstream fout("cowmbat.out");
 
const int NMAX = 1e5 + 5;
const int MAXM = 26;
int N, M, K, cost[MAXM][MAXM], change[NMAX][MAXM], dp[NMAX][MAXM], best[NMAX];
string s;
/// dp[i][c] - costul minim astfel incat pe pozitia i am caracterul c(deci ultimele K caractere cunt c)
 
void min_self(int &a, int b) {
  a = min(a, b);
}
 
void solve() {
  fin >> N >> M >> K >> s;
  for (int i = 0; i < M; ++i)
    for (int j = 0; j < M; ++j)
      fin >> cost[i][j];
  for (int k = 0; k < M; ++k)
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < M; ++j)
        min_self(cost[i][j], cost[i][k] + cost[k][j]);
  for (int c = 0; c < M; ++c)
    dp[0][c] = INF;
  for (int i = 1; i <= N; ++i) {
    best[i] = INF;
    for (int c = 0; c < M; ++c) {
      int cst = cost[s[i - 1] - 'a'][c];
      change[i][c] = change[i - 1][c] + cst;
      dp[i][c] = dp[i - 1][c] + cst; /// extind o secventa anterioara de lungime >= K
      if (i >= K)
        min_self(dp[i][c], best[i - K] + change[i][c] - change[i - K][c]); /// creez o secventa de lungime K
      min_self(best[i], dp[i][c]);
    }
  }
  fout << best[N] << '\n';
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
 
