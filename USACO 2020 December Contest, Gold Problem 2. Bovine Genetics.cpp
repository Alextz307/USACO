#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;
const int kN = 1e5;
const string base = "AGCT";
int dp[kN][4][4][4]; /// pozitia curenta, prima litera a penultimului substring, prima litera
/// a substring-ului curent, respectiv ultima litera a substring-ului curent
/// Daca as imparti sirul in substring-urile la care s-a ajuns dupa split si reverse:
/// o impartire ar fi corecta daca:
/// * pentru oricare 2 subtring-uri adiacente prima litera a primului este la fel cu ultima
///   a celui de-al doilea
/// * in orice substring nu exista 2 litere adiacente identice(s-ar fi dat split acolo)

void addSelf(int &x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int add(int x, int y) {
  addSelf(x, y);
  return x;
}

void testCase() {
  string s;
  cin >> s;
  int n = s.size();
  for (int f1 = 0; f1 < 4; ++f1) {
    for (int f2 = 0; f2 < 4; ++f2) {
      if (s[0] == '?' || s[0] == base[f2]) {
        dp[0][f1][f2][f2] = 1;
      }
    }
  }
  for (int i = 1; i < n; ++i) {
    for (int l2 = 0; l2 < 4; ++l2) {
      if (s[i] == '?' || s[i] == base[l2]) {
        for (int f1 = 0; f1 < 4; ++f1) {
          for (int f2 = 0; f2 < 4; ++f2) {
            for (int l1 = 0; l1 < 4; ++l1) {
              if (l1 != l2) {
                addSelf(dp[i][f1][f2][l2], dp[i - 1][f1][f2][l1]);
              }
              if (f1 == l1) {
                addSelf(dp[i][f2][l2][l2], dp[i - 1][f1][f2][l1]);
              }
            }
          }
        }
      }
    }
  }
  int ans = 0;
  for (int f1 = 0; f1 < 4; ++f1) {
    for (int f2 = 0; f2 < 4; ++f2) {
      addSelf(ans, dp[n - 1][f1][f2][f1]);
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
