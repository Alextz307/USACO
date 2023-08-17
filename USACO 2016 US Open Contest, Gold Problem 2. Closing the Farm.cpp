#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("closing.in");
ofstream fout("closing.out");
 
class DSU {
    public:
        int N;
        vector<int> p, r;
 
        DSU(int n) : N(n) {
            p.resize(N + 1), r.assign(N + 1, 1);
            iota(p.begin(), p.end(), 0);
        }
 
        int get(int x) {
            return (x == p[x] ? x : (p[x] = get(p[x])));
        }
 
        bool connected(int u, int v) {
            int x = get(u),
                y = get(v);
            return x == y;
        }
 
        bool unite(int u, int v) {
            int x = get(u),
                y = get(v);
            if(x == y)
                return false;
            if(r[x] == r[y])
                ++r[x];
            if(r[x] > r[y]) {
                p[y] = x;
                r[x] += r[y];
            }
            else {
               p[x] = y;
               r[y] += r[x];
            }
            return true;
        }
};
 
const int NMAX = 2e5 + 5;
int N, M, u[NMAX], v[NMAX], a[NMAX], poz[NMAX], comps;
vector<int> G[NMAX];
vector<bool> sol;
 
int main() {
    fin >> N >> M;
    DSU tree(N);
    for(int i = 0; i < M; ++i)
        fin >> u[i] >> v[i];
    for(int i = 0; i < N; ++i) {
        fin >> a[i];
        poz[a[i]] = i;
    }
    for(int i = 0; i < M; ++i)
        if(poz[u[i]] < poz[v[i]])
            G[u[i]].emplace_back(v[i]);
        else
            G[v[i]].emplace_back(u[i]);
    for(int i = N - 1; i >= 0; --i) {
        int u = a[i];
        ++comps;
        for(const int &v : G[u])
            if(!tree.connected(u, v)) {
                --comps;
                tree.unite(u, v);
            }
        sol.emplace_back(comps == 1);
    }
    reverse(sol.begin(), sol.end());
    for(const bool &x : sol)
        fout << (x ? "YES\n" : "NO\n");
}
 
