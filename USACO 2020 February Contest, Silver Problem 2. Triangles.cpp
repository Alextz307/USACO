#include <bits/stdc++.h>
#define int long long
#define pi pair<int,int>
#define x first
#define y second
 
using namespace std;
 
ifstream fin("triangles.in");
ofstream fout("triangles.out");
 
const int MOD = 1e9 + 7,
          XMAX = 2e4 + 1,
          NMAX = 1e5 + 1;
vector <pi> a, v[XMAX];
vector <int> sum[NMAX];
 
void add_self(int &a, int b) {
    a += b;
    if(a >= MOD)
        a -= MOD;
}
 
void solve() {
    for(int i = 0; i < XMAX; ++i)
        if(!v[i].empty()) {
            int N = v[i].size();
            sort(v[i].begin(), v[i].end());
            int curr = 0;
            for(int j = 1; j < N; ++j)
                add_self(curr, v[i][j].x - v[i][0].x);
            for(int j = 0; j < N; ++j) {
                if(j)
                    add_self(curr, ((j << 1) - N) * (v[i][j].x - v[i][j - 1].x) % MOD);
                sum[v[i][j].y].emplace_back(curr);
            }
        }
}
 
int32_t main() {
    int N;
    fin >> N;
    a.resize(N);
    for(int i = 0; i < N; ++i)
        fin >> a[i].x >> a[i].y;
    for(int i = 0; i < N; ++i)
        v[a[i].x + 10000].emplace_back(a[i].y, i);
    solve();
    for(int i = 0; i < XMAX; ++i)
        v[i].clear();
    for(int i = 0; i < N; ++i)
        v[a[i].y + 10000].emplace_back(a[i].x, i);
    solve();
    int ans = 0;
    for(int i = 0; i < N; ++i)
        add_self(ans, sum[i][0] * sum[i][1] % MOD);
    fout << ans;
}
 
