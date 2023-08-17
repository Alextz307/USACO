#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("superbull.in");
ofstream fout("superbull.out");
 
const int NMAX = 2e3 + 3;
int a[NMAX], dp[NMAX];
bitset<NMAX> viz;
 
void max_self(int &a, int b) {
  a = max(a, b);
}
 
void solve() {
  int N;
  fin >> N;
  for (int i = 1; i <= N; ++i)
    fin >> a[i];
  long long ans = 0;
  for (int i = 1; i <= N; ++i) {
    int j = 0;
    for (int k = 1; k <= N; ++k)
      if (!viz[k] && dp[k] >= dp[j])
        j = k;
    ans += dp[j];
    viz[j] = true;
    for (int k = 1; k <= N; ++k)
      max_self(dp[k], a[j] ^ a[k]);
  }
  fout << ans << '\n';
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
 
