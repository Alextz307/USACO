// http://www.usaco.org/index.php?page=viewproblem2&cpid=991
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("loan.in");
ofstream fout("loan.out");
 
const int INF = 1e16L;
 
int32_t main() {
    int N, K, M;
    fin >> N >> K >> M;
    int st = 1, dr = INF, ans = INF;
    while(st <= dr) {
        int X = (st + dr) >> 1;
        int k = K, G = 0;
        bool ok = false;
        while(k > 0 && G < N) {
            int Y = (N - G) / X;
            if(Y < M) {
                int left = (N - G + M - 1) / M;
                if(left <= k)
                    ok = true;
                break;
            }
            int max_match = N - X * Y,
                num_days = (max_match - G) / Y + 1;
            G += Y * num_days;
            if(G >= N) {
                ok = true;
                break;
            }
            k -= num_days;
        }
        if(ok) {
            ans = X;
            st = X + 1;
        }
        else
            dr = X - 1;
    }
    fout << ans;
}
 
