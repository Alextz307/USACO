// http://www.usaco.org/index.php?page=viewproblem2&cpid=594
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("angry.in");
ofstream fout("angry.out");
 
int32_t main() {
    int N, K;
    fin >> N >> K;
    vector<int> x(N + 1);
    for(int i = 1; i <= N; ++i)
        fin >> x[i];
    sort(x.begin() + 1, x.end());
    int st = 1, dr = 1e12, ans = 1e12;
    while(st <= dr) {
        int R = (st + dr) >> 1;
        int cnt = 1, p = 1;
        for(int i = 2; i <= N; ++i)
            if(x[i] - x[p] > 2 * R) {
                ++cnt;
                p = i;
            }
        if(cnt <= K) {
            ans = R;
            dr = R - 1;
        }
        else
            st = R + 1;
    }
    fout << ans;
}
 
