#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("shuffle.in");
ofstream fout("shuffle.out");
 
const int NMAX = 1e5;
int a[NMAX], cnt[NMAX];
 
void solve() {
  int N;
  fin >> N;
  for (int i = 0; i < N; ++i) {
    fin >> a[i];
    --a[i];
    ++cnt[a[i]];
  }
  queue<int> Q;
  for (int i = 0; i < N; ++i)
    if (!cnt[i])
      Q.emplace(i);
  int ans = N;
  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();
    --ans;
    if (--cnt[a[curr]] == 0)
      Q.emplace(a[curr]);
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
 
