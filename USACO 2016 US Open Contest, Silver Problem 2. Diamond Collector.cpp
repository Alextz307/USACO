// http://www.usaco.org/index.php?page=viewproblem2&cpid=643
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("diamond.in");
ofstream fout("diamond.out");
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    int N, K;
    fin >> N >> K;
    vector<int> a(N);
    for(int i = 0; i < N; ++i)
        fin >> a[i];
    sort(a.begin(), a.end());
    int r = 0;
    vector<int> can(N);
    for(int l = 0; l < N; ++l) {
        while(r < N && a[r] - a[l] <= K)
            ++r;
        can[l] = r - l;
    }
    vector<int> suf_mx(N);
    suf_mx[N - 1] = can[N - 1];
    for(int i = N - 2; i >= 0; --i)
        suf_mx[i] = max(suf_mx[i + 1], can[i]);
    int ans = 0;
    for(int i = 0; i < N; ++i)
        if(i + can[i] < N)
            max_self(ans, can[i] + suf_mx[i + can[i]]);
    fout << ans;
}
 
