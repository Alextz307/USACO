#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("deleg.in");
ofstream fout("deleg.out");
 
const int MAXN = 1e5 + 1;
int n, paths[MAXN];
vector<int> G[MAXN], sub[MAXN];
 
int dfs(int u, int p) {
  int szu = 1;
  for (int v : G[u])
    if (v != p) {
      int szv = dfs(v, u);
      sub[u].emplace_back(szv);
      szu += szv;
    }
  if (p)
    sub[u].emplace_back(n - szu);
  return szu;
}
 
bool check(int k) {
  if ((n - 1) % k)
    return false;
  for (int i = 1; i < k; ++i)
    paths[i] = 0;
  for (int u = 1; u <= n; ++u) {
    int pairs = 0;
    for (int x : sub[u]) {
      x %= k;
      if (x == 0)
        continue;
      if (paths[k - x])
        --paths[k - x], --pairs;
      else ++paths[x], ++pairs;
    }
    if (pairs)
      return false;
  }
  return true;
}
 
int main() {
  fin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    fin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  dfs(1, 0);
  for (int k = 1; k < n; ++k)
    fout << (check(k) ? '1' : '0');
  fout << '\n';
  fin.close();
  fout.close();
  return 0;
}
 
