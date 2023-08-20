// http://www.usaco.org/index.php?page=viewproblem2&cpid=690
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("cowdance.in");
ofstream fout("cowdance.out");
 
int32_t main() {
    int N, T;
    fin >> N >> T;
    vector<int> a(N + 1);
    for(int i = 1; i <= N; ++i)
        fin >> a[i];
    int st = 1, dr = N, ans = -1;
    while(st <= dr) {
        int K = (st + dr) >> 1;
        priority_queue < int > Q;
        bool ok = true;
        for(int i = 1; i <= N && ok; ++i) {
            int time = 0;
            if(Q.size() == K) {
                time = -Q.top();
                Q.pop();
            }
            if(time + a[i] > T)
                ok = false;
            Q.push(-(time + a[i]));
        }
        if(ok) {
            ans = K;
            dr = K - 1;
        }
        else
            st = K + 1;
    }
    fout << ans;
}
 
