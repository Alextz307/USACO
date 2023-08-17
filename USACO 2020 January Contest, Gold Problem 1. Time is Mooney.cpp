#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("time.in");
ofstream fout("time.out");
 
class edge {
    public:
        int u, v;
 
        void read() {
            fin >> u >> v;
        }
};
 
const int NMAX = 1 << 10;
const int MAXM = 1 << 11;
const int TMAX = 1 << 10;
int N, M, C, a[NMAX], dp[2][NMAX], ind = 1, ans;
edge edges[MAXM];
 
/// dp[t][u] - valoarea maxima ce o pot obtine daca la timpul t sunt in u.
/// Valorile lui t sunt relevante pana la maxim 1000, pentru ca pentru t > 1000
/// 1000 * t - t * t, care este valoarea ce o pot acumula in cel mai bun caz, devine negativa.
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    fin >> N >> M >> C;
    for(int i = 1; i <= N; ++i)
        fin >> a[i];
    for(int i = 1; i <= M; ++i)
        edges[i].read();
    for(int i = 0; i < 2; ++i)
        for(int u = 1; u <= N; ++u)
            dp[i][u] = -INF;
    dp[0][1] = 0;
    for(int t = 1; t < TMAX; ++t, ind ^= 1) {
        for(int u = 1; u <= N; ++u)
            dp[ind][u] = -INF;
        for(int i = 1; i <= M; ++i) {
            int u = edges[i].u,
                v = edges[i].v;
            max_self(dp[ind][v], dp[ind ^ 1][u] + a[v]);
        }
        max_self(ans, dp[ind][1] - C * t * t);
    }
    fout << ans << '\n';
}
 
