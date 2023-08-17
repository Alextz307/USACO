#include <fstream>
#include <vector>
#include <queue>
 
using namespace std;
 
ifstream fin("milkorder.in");
ofstream fout("milkorder.out");
 
const int MAXM = 5e4;
int n, m;
vector<int> edges[MAXM], sol;
 
bool check(int k) {
  vector<vector<int>> G(n);
  vector<int> in_deg(n);
  for (int i = 0; i < k; ++i)
    for (int j = 0; j < (int)edges[i].size() - 1; ++j) {
      int u = edges[i][j], v = edges[i][j + 1];
      G[u].emplace_back(v);
      ++in_deg[v];
    }
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int u = 0; u < n; ++u)
    if (in_deg[u] == 0)
      pq.emplace(u);
  vector<int> top_order;
  for (int pas = 0; pas < n; ++pas) {
    if (pq.empty())
      return false;
    int u = pq.top();
    pq.pop();
    top_order.emplace_back(u);
    for (int v : G[u])
      if (--in_deg[v] == 0)
        pq.emplace(v);
  }
  sol = top_order;
  return true;
}
 
int main() {
  fin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int k;
    fin >> k;
    edges[i].resize(k);
    for (int &u : edges[i]) {
      fin >> u;
      --u;
    }
  }
  int st = 1, dr = m;
  while (st <= dr) {
    int mid = (st + dr) >> 1;
    if (check(mid))
      st = mid + 1;
    else dr = mid - 1;
  }
  fout << sol[0] + 1;
  for (int i = 1; i < (int)sol.size(); ++i)
    fout << ' ' << sol[i] + 1;
  return 0;
}
 
