#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("feast.in");
ofstream fout("feast.out");
 
const int NMAX = 5e6 + 6;
bool dp1[NMAX], dp2[NMAX];
 
void solve() {
  int N, A, B;
  fin >> N >> A >> B;
  if (A > B)
    swap(A, B);
  dp1[0] = true;
  for (int i = A; i <= N; ++i) {
    dp1[i] |= dp1[i - A];
    if (i >= B)
      dp1[i] |= dp1[i - B];
    dp2[i / 2] |= dp1[i];
  }
  dp2[0] = true;
  for (int i = A; i <= N; ++i) {
    dp2[i] |= dp2[i - A];
    if (i >= B)
      dp2[i] |= dp2[i - B];
  }
  for (int i = N; i >= 0; --i)
    if (dp2[i]) {
      fout << i << '\n';
      return;
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
 
