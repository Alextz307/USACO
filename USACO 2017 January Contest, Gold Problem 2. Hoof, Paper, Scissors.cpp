#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("hps.in");
ofstream fout("hps.out");
 
/// H = 0, P = 1, S = 2
/// 0 > 2
/// 2 > 1
/// 1 > 0
 
const int NMAX = 1e5 + 5;
const int KMAX = 22;
int N, K, dp[NMAX][KMAX][3], ans;
string moves = "";
 
/// dp[i][switches][play] - numarul maxim de jocuri pe care le poate castiga Bessie
///                         daca la pasul i a facut switches schimbari de stare
///                         si joaca "miscarea" play
 
int num(const char &ch) {
    if(ch == 'H')
        return 0;
    if(ch == 'P')
        return 1;
    return 2;
}
 
bool wins(const int &x, const int &y) {
    return (x == 0 && y == 2) || (x == 2 && y == 1) || (x == 1 && y == 0);
}
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    fin >> N >> K;
    fin.get();
    for(int i = 0; i < N; ++i, fin.get())
        moves += fin.get();
    for(int play = 0; play < 3; ++play)
        dp[0][0][play] = wins(play, num(moves[0]));
    for(int i = 1; i < N; ++i)
        for(int switches = 0; switches <= K; ++switches)
            for(int prv_play = 0; prv_play < 3; ++prv_play)
                for(int curr_play = 0; curr_play < 3; ++curr_play) {
                    int new_switches = switches + (curr_play != prv_play);
                    if(new_switches > K)
                        continue;
                    max_self(dp[i][new_switches][curr_play], dp[i - 1][switches][prv_play] + wins(curr_play, num(moves[i])));
                }
    for(int k = 0; k <= K; ++k)
        for(int play = 0; play < 3; ++play)
            max_self(ans, dp[N - 1][k][play]);
    fout << ans << '\n';
}
 
