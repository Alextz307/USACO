#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("teamwork.in");
ofstream fout("teamwork.out");
 
const int NMAX = 1e4 + 4;
int N, K, a[NMAX], dp[NMAX];
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    fin >> N >> K;
    for(int i = 1; i <= N; ++i) {
        fin >> a[i];
        int best = 0;
        for(int add = 0; add < min(i, K); ++add) {
            max_self(best, a[i - add]);
            max_self(dp[i], dp[i - add - 1] + (add + 1) * best);
        }
    }
    fout << dp[N] << '\n';
}
 
