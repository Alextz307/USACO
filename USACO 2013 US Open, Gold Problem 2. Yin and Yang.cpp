#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
using oset = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
using int64 = long long;
 
ifstream fin("yinyang.in");
ofstream fout("yinyang.out");
 
const int MAXN = 1e5 + 5;
int sz[MAXN];
bitset<MAXN> viz;
vector<pair<int,int>> G[MAXN]; 
 
void find_size(int u, int parent) {
  sz[u] = 1;
  for (auto v : G[u])
    if (v.first != parent && !viz[v.first]) {
      find_size(v.first, u);
      sz[u] += sz[v.first];
    }
}
 
int find_centroid(int u, int parent, int n) {
  for (auto v : G[u])
    if (v.first != parent && !viz[v.first] && sz[v.first] > (n >> 1))
      return find_centroid(v.first, u, n);
  return u;
}
 
int offset, cnt[MAXN << 1], paths_rest[MAXN << 1], paths_no_rest[MAXN << 1];
vector<pair<int,bool>> paths;
 
void find_paths(int u, int parent, int sum) {
  paths.emplace_back(sum, cnt[sum + offset] > 0);
  ++cnt[sum + offset];
  for (auto v : G[u])
    if (v.first != parent && !viz[v.first])
      find_paths(v.first, u, sum + v.second);
  --cnt[sum + offset];
}
 
int64 solve_tree(int u, int n) {
  for (int i = offset - n + 1; i <= offset + n - 1; ++i)
    paths_rest[i] = paths_no_rest[i] = 0;
  int64 ans = 0;
  for (auto v : G[u])
    if (!viz[v.first]) {
      paths.clear();
      find_paths(v.first, u, v.second);
      for (auto p : paths) {
        if (p.second || p.first == 0)
          ans += paths_no_rest[offset - p.first];
        ans += paths_rest[offset - p.first];
        if (p.second && p.first == 0)
          ++ans;
      }
      for (auto p : paths) 
        if (p.second)
          ++paths_rest[p.first + offset];
        else ++paths_no_rest[p.first + offset];
    }
  return ans;
} 
 
int64 build(int u, int parent) {
  find_size(u, 0);
  int c = find_centroid(u, 0, sz[u]);
  viz[c] = true;
  int64 ans = solve_tree(c, sz[u]);
  for (auto v : G[c])
    if (!viz[v.first])
      ans += build(v.first, c);
  return ans;
}
 
void test_case() {
  int N;
  fin >> N;
  offset = N;
  for (int i = 1; i < N; ++i) {
    int u, v, w;
    fin >> u >> v >> w;
    w = (w << 1) - 1;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  fout << build(1, 0) << '\n';
}
 
void solve() {  
  int T = 1;
  for (int tc = 0; tc < T; ++tc)
    test_case();
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
 
