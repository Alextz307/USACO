#include <bits/stdc++.h>
#define int long long

using namespace std;

ifstream fin("pieaters.in");
ofstream fout("pieaters.out");

/* void testCase() {
  int n, m;
  fin >> n >> m;
  vector<int> w(m), pies(m);
  for (int i = 0; i < m; ++i) {
    int l, r;
    fin >> w[i] >> l >> r;
    for (int j = l; j <= r; ++j) {
      pies[i] |= (1LL << (j - 1));
    }
  }
  vector<int> dp(1 << m), subset(1 << m);
  for (int mask = 1; mask < (1 << m); ++mask) {
    for (int i = 0; (1 << i) <= mask; ++i) {
      if (mask & (1 << i)) {
        subset[mask] = subset[mask ^ (1 << i)] | pies[i];
        if (subset[mask ^ (1 << i)] != (subset[mask ^ (1 << i)] | pies[i])) { /// mai are i ceva de mancare
          maxSelf(dp[mask], dp[mask ^ (1 << i)] + w[i]);
        }
      }
    }
  }
  fout << *max_element(dp.begin(), dp.end()) << '\n';
} */

const int kN = 300;
int wt[1 + kN + 1][1 + kN + 1][1 + kN + 1], dp[1 + kN][1 + kN];
/// wt[last][l][r] =def= valoarea maxima a unei vaci al carei interval este inclus in l...r si contine last
/// dp[l][r] =def= suma maxima daca se mananca doar placinte din intervalul l...r
/// se itereaza prin ultima placinta mancata de o vaca(in i...k - 1 si k + 1...r vaca sigur nu mananca
/// nimic pentru ca are capetele atat in i...k - 1, cat si k + 1...r)

void maxSelf(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

void testCase() {
  int n, m;
  fin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int w, l, r;
    fin >> w >> l >> r;
    for (int j = l; j <= r; ++j) {
      wt[j][l][r] = w;
    }
  }
  for (int len = 1; len <= n; ++len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int j = i + len - 1;
      for (int k = i; k <= j; ++k) {
        maxSelf(wt[k][i - 1][j], wt[k][i][j]);
        maxSelf(wt[k][i][j + 1], wt[k][i][j]);
      }
    }
  }
  for (int len = 1; len <= n; ++len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int j = i + len - 1;
      for (int k = i; k <= j; ++k) {
        /// maxSelf(dp[i][j], dp[i][k] + dp[k + 1][j]);
        maxSelf(dp[i][j], dp[i][k - 1] + wt[k][i][j] + dp[k + 1][j]);
      }
    }
  }
  fout << dp[1][n] << '\n';
}

int32_t main() {
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
