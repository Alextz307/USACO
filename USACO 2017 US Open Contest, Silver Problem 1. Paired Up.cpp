// http://www.usaco.org/index.php?page=viewproblem2&cpid=738
#include <bits/stdc++.h>
#define pi pair<int,int>
#define x first
#define y second
 
using namespace std;
 
ifstream fin("pairup.in");
ofstream fout("pairup.out");
 
bool fcmp(const pi &a, const pi &b) {
    return a.y < b.y;
}
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    int N;
    fin >> N;
    vector<pi> a(N);
    for(int i = 0; i < N; ++i)
        fin >> a[i].x >> a[i].y;
    sort(a.begin(), a.end(), fcmp);
    int p = N - 1, ans = 0;
    for(int i = 0; i <= p; ++i) {
        max_self(ans, a[i].y + a[p].y);
        if(a[i].x > a[p].x) {
            a[i].x -= a[p].x;
            --p;
            --i;
        }
        else {
            a[p].x -= a[i].x;
            if(a[p].x == 0)
                --p;
        }
    }
    fout << ans;
}
 
