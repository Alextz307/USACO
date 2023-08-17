#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("snakes.in");
ofstream fout("snakes.out");
 
const int NMAX = 1 << 9;
int N, K, a[NMAX], dp[NMAX][NMAX], sum, pref_max;
/// dp[i][j] - costul minim pentru a captura primele i grupuri cu j schimbari
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
void min_self(int &a, int b) {
    a = min(a, b);
}
 
int main() {
    fin >> N >> K;
    for(int i = 1; i <= N; ++i) {
        fin >> a[i];
        sum += a[i];
        max_self(pref_max, a[i]);
        dp[i][0] = pref_max * i;
        for(int j = 1; j <= K; ++j) {
            dp[i][j] = INF;
            int mx = a[i];
            for(int prv = i - 1; prv >= 0; --prv) {
                min_self(dp[i][j], dp[prv][j - 1] + mx * (i - prv));
                max_self(mx, a[prv]);
            }
        }
    }
    fout << dp[N][K] - sum << '\n';
}
 
