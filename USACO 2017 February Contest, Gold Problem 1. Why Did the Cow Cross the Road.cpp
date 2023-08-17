#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("visitfj.in");
ofstream fout("visitfj.out");
 
/// pentru a ajunge sa fie cele la distanta 1 pe pozitie divizibila cu 3 face un fel de "du-te-vino"
/// nu exista strategie analoaga cu cea pentru distanta 1 si pentru distanta 2
/// distanta 3 e clar ca poate sa sara
const int MAXN = 100;
const int di[] = {0, 1, 2, 3, 2, 1, 0, -1, -2, -3, -2, -1, -1, 1, 0, 0};
const int dj[] = {3, 2, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2, 0, 0, -1, 1};
int n, T, a[MAXN][MAXN], dp[MAXN][MAXN];
 
void min_self(int &x, int y) {
  x = min(x, y);
}
 
bool inside(int lin, int col) {
  return lin >= 0 && lin < n && col >= 0 && col < n;
}
 
int main() {
  fin >> n >> T;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      fin >> a[i][j];
      dp[i][j] = INF;
    }
  dp[0][0] = 0;
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.emplace(0, 0);
  int ans = INF;
  while (!pq.empty()) {
    int d = pq.top().first, i = pq.top().second / n, j = pq.top().second % n;
    pq.pop();
    if (dp[i][j] != d)
      continue;
    int dist = (n - 1 - i) + (n - 1 - j);
    if (dist < 3)
      min_self(ans, d + dist * T);
    for (int k = 0; k < 16; ++k) {
      int iv = i + di[k], jv = j + dj[k];
      int cost = d + a[iv][jv] + 3 * T;
      if (inside(iv, jv) && dp[iv][jv] > cost) {
        dp[iv][jv] = cost;
        pq.emplace(dp[iv][jv], iv * n + jv);
      }
    }
  }
  fout << ans << '\n';
  return 0;
}
 
