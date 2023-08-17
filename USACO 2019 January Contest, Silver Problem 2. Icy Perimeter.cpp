#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("perimeter.in");
ofstream fout("perimeter.out");
 
const int NMAX = 1e3 + 3;
const int dl[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
char a[NMAX][NMAX];
bool viz[NMAX][NMAX];
 
void solve() {
  int N;
  fin >> N;
  for (int i = 1; i <= N; ++i)
    fin >> (a[i] + 1);
  int Amax = 0, Pmin = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      if (a[i][j] == '#' && !viz[i][j]) {
        queue<pair<int,int>> Q;
        Q.emplace(i, j);
        viz[i][j] = true;
        int A = 0, P = 0;
        while (!Q.empty()) {
          int l = Q.front().first, c = Q.front().second;
          Q.pop();
          ++A;
          for (int k = 0; k < 4; ++k) {
            int lv = l + dl[k], cv = c + dc[k];
            if (a[lv][cv] != '#')
              ++P;
            else {
              if (!viz[lv][cv] && lv > 0 && cv > 0 && lv <= N && cv <= N) {
                viz[lv][cv] = true;
                Q.emplace(lv, cv);
              }
            }
          }
        }
        if (A > Amax || (A == Amax && P < Pmin)) {
          Amax = A;
          Pmin = P;
        }
      }
  fout << Amax << ' ' << Pmin << '\n';
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
 
