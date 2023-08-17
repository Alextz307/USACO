#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("revegetate.in");
ofstream fout("revegetate.out");
 
const int NMAX = 1e5 + 5;
vector<int> G1[NMAX], G2[NMAX];
int tag[NMAX];
bool flag;
 
void dfs(int u) {
  if (flag)
    return;
  for (int v : G1[u]) {
    if (tag[v] == 3 - tag[u])
      flag = true;
    if (tag[v] == 0) {
      tag[v] = tag[u];
      dfs(v);
    }
  }
  for (int v : G2[u]) {
    if (tag[v] == tag[u])
      flag = true;
    if (tag[v] == 0) {
      tag[v] = 3 - tag[u];
      dfs(v);
    }
  }
}
 
void solve() {
  int N, M;
  fin >> N >> M;
  for (int i = 0; i < M; ++i) {
    char c;
    int u, v;
    fin >> c >> u >> v;
    if (c == 'S') {
      G1[u].emplace_back(v);
      G1[v].emplace_back(u);
    } else {
      G2[u].emplace_back(v);
      G2[v].emplace_back(u);
    }
  }
  int ans = 0;
  for (int u = 1; u <= N && !flag; ++u)
    if (!tag[u]) {
      ++ans;
      tag[u] = 1;
      dfs(u);
    }
  if (flag)
    fout << "0\n";
  else {
    fout << '1';
    for (int i = 0; i < ans; ++i)
      fout << '0';
    fout << '\n';
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
 
