// http://www.usaco.org/index.php?page=viewproblem2&cpid=918
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("herding.in");
ofstream fout("herding.out");
 
int N;
vector<int> a;
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int solve_min() {
    if(a[N - 2] - a[0] == N - 2 && a[N - 1] - a[N - 2] > 2)
        return 2;
    if(a[N - 1] - a[1] == N - 2 && a[1] - a[0] > 2)
        return 2;
    int j = 0, best = 0;
    for(int i = 0; i < N; ++i) {
        while(j < N - 1 && a[j + 1] - a[i] < N)
            ++j;
        max_self(best, j - i + 1);
    }
    return N - best;
}
 
int solve_max() {
    return max(a[N - 2] - a[0], a[N - 1] - a[1]) - (N - 2);
}
 
int main() {
    fin >> N;
    a.resize(N);
    for(int i = 0; i < N; ++i)
        fin >> a[i];
    sort(a.begin(), a.end());
    fout << solve_min() << '\n' << solve_max();
}
 
