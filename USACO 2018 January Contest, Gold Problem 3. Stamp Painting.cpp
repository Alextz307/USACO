#include <bits/stdc++.h>

using namespace std;

ifstream fin("spainting.in");
ofstream fout("spainting.out");

const int mod = 1e9 + 7;
const int kN = 1e6;
int sum[1 + kN];

/// Observatie importanta: pentru ca la un pas se coloreaza neaparat k celule consecutive
/// cu o anumita culoare, la final va exista o secventa de lungime k in care toate culorile sunt la fel
/// De asemenea, e usor de observat ca orice sir ce respecta aceasta proprietate si are valori
/// intre 1 si m poate fi construit(se coloreaza cele din afara intervalului si apoi intervalul)
/// si este o solutie
/// Astfel, problema cere numarul de siruri de n numere cu valori intre 1 si m care au cel
/// putin o secventa de lungime cel putin k formata din numere egale
/// Complementul e mai usor de calculat(la final se scade rezultatul din m^n):
/// => Se vrea numarul de siruri de n numere cu valori intre 1 si m care nu au k numere
/// egale pe pozitii consecutive
/// dp(n) =def= numarul de siruri ...
/// dp(n) = sum{dp[n - i]} * (m - 1); 1 <= i <= k - 1
/// m - 1 moduri pentru ultima culoare(trebuie sa fie diferita de cea de dinainte)

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

void multSelf(int &x, int y) {
  x = (int64_t)x * y % mod;
}

int mult(int x, int y) {
  multSelf(x, y);
  return x;
}

void testCase() {
  int n, m, k;
  fin >> n >> m >> k;
  int pw = 1;
  for (int i = 1; i <= n; ++i) {
    multSelf(pw, m);
    sum[i] = sum[i - 1];
    if (i < k) {
      addSelf(sum[i], pw);
    } else {
      addSelf(sum[i], mult(m - 1, add(sum[i - 1], mod - sum[i - k])));
    }
  }
  fout << add(pw, mod - add(sum[n], mod - sum[n - 1])) << '\n';
}

int main() {
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  fin.close();
  fout.close();
  return 0;
}
