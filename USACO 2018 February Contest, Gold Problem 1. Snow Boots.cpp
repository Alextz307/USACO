// http://www.usaco.org/index.php?page=viewproblem2&cpid=813
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("snowboots.in");
ofstream fout("snowboots.out");
 
vector<int> f, snow, dist, did, bid;
 
bool cmp1(int a, int b) {
    return f[a] < f[b];
}
 
bool cmp2(int a, int b) {
    return snow[a] < snow[b];
}
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    int N, B;
    fin >> N >> B;
    f.resize(N), did.resize(N);
    for(int i = 0; i < N; ++i) {
        fin >> f[i];
        did[i] = i;
    }
    snow.resize(B), dist.resize(B), bid.resize(B);
    for(int i = 0; i < B; ++i) {
        fin >> snow[i] >> dist[i];
        bid[i] = i;
    }
    sort(did.begin(), did.end(), cmp1);
    sort(bid.begin(), bid.end(), cmp2);
    vector<int> next(N), prev(N);
    for(int i = 0; i < N; ++i) {
        next[i] = i + 1;
        prev[i] = i - 1;
    }
    int j = N - 1, maxStep = 1;
    vector<bool> ans(B);
    for(int i = B - 1; i >= 0; --i) {
        int boot = bid[i];
        while(j >= 0 && f[did[j]] > snow[boot]) {
            int curr = did[j];
            next[prev[curr]] = next[curr];
            prev[next[curr]] = prev[curr];
            max_self(maxStep, next[curr] - prev[curr]);
            --j;
        }
        ans[boot] = (maxStep <= dist[boot]);
    }
    for(int i = 0; i < B; ++i)
        fout << ans[i] << '\n';
}
 
