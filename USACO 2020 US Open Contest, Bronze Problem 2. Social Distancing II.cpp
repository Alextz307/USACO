// http://www.usaco.org/index.php?page=viewproblem2&cpid=1036
#include <bits/stdc++.h>
#define pi pair<int,int>
#define x first
#define ok second
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("socdist2.in");
ofstream fout("socdist2.out");
 
void min_self(int &a, int b) {
    a = min(a, b);
}
 
int main() {
    int N;
    fin >> N;
    vector<pi> a(N);
    for(int i = 0; i < N; ++i)
        fin >> a[i].x >> a[i].ok;
    sort(a.begin(), a.end());
    int R = INF;
    for(int i = 0; i < N; ++i)
        if(i > 0 && a[i].ok != a[i - 1].ok)
            min_self(R, a[i].x - a[i - 1].x);
    --R;
    int p = 0;
    while(a[p].ok == 0)
        ++p;
    int ans = 1, last = a[p].x;
    for(int i = p + 1; i < N; ++i)
        if(a[i].ok == 1) {
            if(a[i].x - last > R)
                ++ans;
            last = a[i].x;
        }
    fout << ans;
}
 
