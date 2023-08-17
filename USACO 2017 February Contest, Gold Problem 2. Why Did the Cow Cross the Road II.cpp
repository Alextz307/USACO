#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("nocross.in");
ofstream fout("nocross.out");
 
void max_self(short &x, short y) {
  x = max(x, y);
}
 
int main() {
  short n;
  fin >> n;
  vector<short> a(n + 1), b(n + 1);
  for (short i = 1; i <= n; ++i)
    fin >> a[i];
  for (short i = 1; i <= n; ++i)
    fin >> b[i];
  vector<vector<short>> dp(n + 1, vector<short>(n + 1));
  for (short i = 1; i <= n; ++i)
    for (short j = 1; j <= n; ++j) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if (abs(a[i] - b[j]) <= 4)
        max_self(dp[i][j], dp[i - 1][j - 1] + 1);
    }
  fout << dp[n][n] << '\n';
  fin.close();
  fout.close();
  return 0;
}
