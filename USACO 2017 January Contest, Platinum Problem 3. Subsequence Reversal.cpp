#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

ifstream fin("subrev.in");
ofstream fout("subrev.out");

/// Obs. 1: Operatia de inversare a unui subsir inseamna swap la elemente pornind din capete, deci asta
/// sugereaza un dp[st][dr].
/// Obs. 2: Ma intereseaza pentru st...dr si subsiruri care incep sau nu in st si se termina sau nu in dr,
/// deci aceste capete limiteaza ce se intampla in st + 1...dr - 1 in functie de caz
/// => dp[st][dr][min][max] =def= subsirul crescator maximal din intervalul st...dr cu toate valorile cuprinse intre min si max
/// Complexitate: O(N^4)

const int kN = 50;
int a[1 + kN], dp[1 + kN][1 + kN][1 + kN][1 + kN];

void maxSelf(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

int solve(int l, int r, int mn, int mx) {
  if (mx < mn) { /// nu se poate
    return -INF;
  }
  if (r < l) {
    return 0;
  }
  if (l == r) {
    if (mn <= a[l] && a[l] <= mx) {
      return 1;
    }
    return 0;
  }
  if (dp[l][r][mn][mx] != -1) {
    return dp[l][r][mn][mx];
  }
  int ans = 0;
  maxSelf(ans, solve(l + 1, r, mn, mx)); /// ignor l
  maxSelf(ans, solve(l, r - 1, mn, mx)); /// ignor r
  maxSelf(ans, solve(l + 1, r - 1, mn, mx)); /// ignor l si r
  if (mn <= a[l] && a[l] <= mx) { /// includ l
    maxSelf(ans, solve(l + 1, r, a[l], mx) + 1);
  }
  if (mn <= a[r] && a[r] <= mx) { /// includ r
    maxSelf(ans, solve(l, r - 1, mn, a[r]) + 1);
  }
  if (mn <= a[l] && a[l] <= a[r] && a[r] <= mx) { /// includ l si r
    maxSelf(ans, solve(l + 1, r - 1, a[l], a[r]) + 2);
  }
  if (mn <= a[l] && a[l] <= mx) { /// dau swap la l si r si includ l(care e acum pe pozitia lui r)
    maxSelf(ans, solve(l + 1, r - 1, mn, a[l]) + 1);
  }
  if (mn <= a[r] && a[r] <= mx) { /// dau swap la l si r si includ r(care e acum pe pozitia lui l)
    maxSelf(ans, solve(l + 1, r - 1, a[r], mx) + 1);
  }
  if (mn <= a[r] && a[r] <= a[l] && a[l] <= mx) { /// dau swap la l si r si le includ pe ambele
    maxSelf(ans, solve(l + 1, r - 1, a[r], a[l]) + 2);
  }
  return dp[l][r][mn][mx] = ans;
}

void testCase() {
  int n;
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    fin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      for (int p = 1; p <= 50; ++p) {
        for (int q = p; q <= 50; ++q) {
          dp[i][j][p][q] = -1;
        }
      }
    }
  }
  fout << solve(1, n, 1, 50) << '\n';
}

int main() {
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
