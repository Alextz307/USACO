// http://www.usaco.org/index.php?page=viewproblem2&cpid=1038
#include <bits/stdc++.h>
#define int long long
#define pi pair<int,int>
#define x first
#define y second
 
using namespace std;
 
ifstream fin("socdist.in");
ofstream fout("socdist.out");
 
const int INF = 1e16L;
 
int32_t main() {
    int N, M;
    fin >> N >> M;
    vector<pi> a(M);
    for(int i = 0; i < M; ++i)
        fin >> a[i].x >> a[i].y;
    sort(a.begin(), a.end());
    int st = 1, dr = INF, ans = 1;
    while(st <= dr) {
        int D = (st + dr) >> 1;
        int prev = -INF, cnt = 0;
        for(int i = 0; i < M; ++i) {
            while(max(prev + D, a[i].x) <= a[i].y) {
                ++cnt;
                if(cnt >= N)
                    break;
                prev = max(prev + D, a[i].x);
            }
            if(cnt >= N)
                break;
        }
        if(cnt >= N) {
            ans = D;
            st = D + 1;
        }
        else
            dr = D - 1;
    }
    fout << ans;
}
 
