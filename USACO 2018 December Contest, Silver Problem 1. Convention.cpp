// http://www.usaco.org/index.php?page=viewproblem2&cpid=858
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("convention.in");
ofstream fout("convention.out");
 
int32_t main() {
    int N, M, C;
    fin >> N >> M >> C;
    vector<int> a(N + 1);
    for(int i = 1; i <= N; ++i)
        fin >> a[i];
    sort(a.begin() + 1, a.end());
    int st = 1, dr = 1e12, ans = 1e12;
    while(st <= dr) {
        int T = (st + dr) >> 1;
        int p = 1, cnt = 1;
        for(int i = 2; i <= N; ++i)
            if(i - p + 1 > C || a[i] - a[p] > T) {
                p = i;
                ++cnt;
            }
        if(cnt <= M) {
            ans = T;
            dr = T - 1;
        }
        else
            st = T + 1;
    }
    fout << ans;
}
 
