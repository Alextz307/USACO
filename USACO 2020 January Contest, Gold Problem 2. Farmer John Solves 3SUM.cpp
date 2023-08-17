#include <bits/stdc++.h>
 
using namespace std;
using int64 = long long;
 
ifstream fin("threesum.in");
ofstream fout("threesum.out");
 
const int MAXN = 5e3;
const int MAXV = 2e6 + 1;
const int offset = 1e6;
int a[MAXN], freq[MAXV];
int64 sol[MAXN][MAXN];
 
int main() {
  int n, Q;
  fin >> n >> Q;
  for (int i = 0; i < n; ++i)
    fin >> a[i];
  for (int i = 0; i < n - 2; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int sum = -a[i] - a[j] + offset;
      if (0 <= sum && sum < MAXV)
        sol[i][j] = freq[sum];
      ++freq[a[j] + offset];
    }
    for (int j = i + 1; j < n; ++j)
      --freq[a[j] + offset];
  }
  for (int i = n - 3; i >= 0; --i)
    for (int j = i + 2; j < n; ++j)
      sol[i][j] += sol[i][j - 1] + sol[i + 1][j] - sol[i + 1][j - 1];
  for (int q = 0; q < Q; ++q) {
    int l, r;
    fin >> l >> r;
    fout << sol[l - 1][r - 1] << '\n';
  }
  fin.close();
  fout.close();
  return 0;
}
 
