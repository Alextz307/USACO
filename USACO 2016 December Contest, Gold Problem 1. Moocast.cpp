#include <bits/stdc++.h>
#define sqr(x) ((x) * (x))
 
using namespace std;
 
ifstream fin("moocast.in");
ofstream fout("moocast.out");
 
class vertex {
    public:
        int x, y;
 
        void read() {
            fin >> x >> y;
        }
};
 
class edge {
    public:
        int u, v, w;
 
        bool operator < (const edge &A) const {
            return w < A.w;
        };
};
 
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
 
const int NMAX = 1 << 10;
const int EMAX = 1 << 20;
int N, M, cnt;
vertex a[NMAX];
edge edges[EMAX];
 
int dist(const vertex &A, const vertex &B) {
    return sqr(B.x - A.x) + sqr(B.y - A.y);
}
 
int main() {
    fin >> N;
    for(int i = 1; i <= N; ++i)
        a[i].read();
    for(int i = 1; i < N; ++i)
        for(int j = i + 1; j <= N; ++j)
            edges[++M] = edge{i, j, dist(a[i], a[j])};
    sort(edges + 1, edges + M + 1);
    DSU tree(N);
    for(int i = 1; i <= M; ++i)
        if(!tree.connected(edges[i].u, edges[i].v)) {
            ++cnt;
            if(cnt == N - 1) {
                fout << edges[i].w << '\n';
                return 0;
            }
            tree.unite(edges[i].u, edges[i].v);
        }
}
 
