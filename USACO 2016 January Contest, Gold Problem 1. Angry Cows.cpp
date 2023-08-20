// http://www.usaco.org/index.php?page=viewproblem2&cpid=597
#include <bits/stdc++.h>
#define int long long
#define ABS(x) ((x) >= 0 ? (x) : -(x))
 
using namespace std;
using ld = long double;
 
ifstream fin("angry.in");
ofstream fout("angry.out");
 
const int INF = 1e16L;
 
void min_self(ld &a, ld b) {
    a = min(a, b);
}
 
int32_t main() {
    int N;
    fin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; ++i)
        fin >> a[i];
    sort(a.begin(), a.end());
    vector<int> dp[2];
    for(int it = 0; it < 2; ++it) {
        dp[it].resize(N, INF);
        dp[it][0] = -1;
        int lastj = 0;
        for(int i = 1; i < N; ++i) {
            while(lastj + 1 < i && ABS(a[i] - a[lastj + 1]) > dp[it][lastj + 1] + 1)
                ++lastj;
            dp[it][i] = min(ABS(a[i] - a[lastj]), dp[it][lastj + 1] + 1);
        }
        reverse(a.begin(), a.end());
    }
    reverse(dp[1].begin(), dp[1].end());
    int i = 0, j = N - 1;
    ld ans = INF;
    while(i < j) {
        min_self(ans, max((ld)(a[j] - a[i]) / 2.0, (ld)1.0 + max(dp[0][i], dp[1][j])));
        if(dp[0][i + 1] < dp[1][j - 1])
            ++i;
        else
            --j;
    }
    fout << fixed << setprecision(1) << ans;
}
 
