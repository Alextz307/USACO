// http://www.usaco.org/index.php?page=viewproblem2&cpid=360
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("wormhole.in");
ofstream fout("wormhole.out");
 
int N;
vector <int> X(16), Y(16), partner(16), next_on_right(16);
 
bool is_cycle() {
    for(int start = 1; start <= N; ++start) {
        int pos = start;
        for(int cnt = 0; cnt < N; ++cnt)
            pos = next_on_right[partner[pos]];
        if(pos != 0)
            return true;
    }
    return false;
}
 
int solve() {
    int i;
    for(i = 1; i <= N; ++i)
        if(partner[i] == 0)
            break;
    if(i > N)
        return is_cycle();
    int sol = 0;
    for(int j = i + 1; j <= N; ++j)
        if(partner[j] == 0) {
            partner[i] = j;
            partner[j] = i;
            sol += solve();
            partner[i] = partner[j] = 0;
        }
    return sol;
}
 
int main() {
    fin >> N;
    for(int i = 1; i <= N; ++i)
        fin >> X[i] >> Y[i];
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
            if(X[j] > X[i] && Y[i] == Y[j])
                if(next_on_right[i] == 0 || X[j] < X[next_on_right[i]])
                    next_on_right[i] = j;
    fout << solve();
}
 
