#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("clocktree.in");
ofstream fout("clocktree.out");
 
const int NMAX = 2505;
int a[NMAX], n[2], s[2];
vector<int> G[NMAX];
 
void dfs(int u, int parent, int depth) {
  ++n[depth & 1];
  s[depth & 1] += a[u];
  for (int v : G[u])
    if (v != parent)
      dfs(v, u, depth + 1);
}
 
void solve() {
  int N;
  fin >> N;
  for (int i = 1; i <= N; ++i)
    fin >> a[i];
  for (int i = 1; i < N; ++i) {
    int u, v;
    fin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  dfs(1, 0, 0);
  if (s[0] % 12 == s[1] % 12)
    fout << N << '\n';
  else {
    if ((s[0] + 1) % 12 == s[1] % 12)
      fout << n[1] << '\n';
    else {
      if ((s[1] + 1) % 12 == s[0] % 12)
        fout << n[0] << '\n';
      else fout << "0\n";
    }
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
 
