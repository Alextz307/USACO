// http://www.usaco.org/index.php?page=viewproblem2&cpid=569
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("badmilk.in");
ofstream fout("badmilk.out");
 
class action {
    public:
        int p, m, t;
};
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    int N, M, D, S;
    fin >> N >> M >> D >> S;
    vector <action> a(D);
    for(int i = 0; i < D; ++i)
        fin >> a[i].p >> a[i].m >> a[i].t;
    vector<int> sick(N + 1);
    for(int i = 0; i < S; ++i) {
        int p, t;
        fin >> p >> t;
        sick[p] = t;
    }
    int sol = 0;
    for(int milk = 1; milk <= N; ++milk) {
        int cnt = 0;
        vector < bool > mark(N + 1);
        for(int i = 0; i < D && cnt < S; ++i) {
            action x = a[i];
            if(x.m == milk && x.t < sick[x.p]) {
                if(!mark[x.p])
                    ++cnt;
                mark[x.p] = true;
            }
        }
        if(cnt == S) {
            set<int> s;
            for(int i = 0; i < D; ++i) {
                action x = a[i];
                if(x.m == milk)
                    s.insert(x.p);
            }
            max_self(sol, static_cast<int>(s.size()));
        }
    }
    fout << sol;
}
 // http://www.usaco.org/index.php?page=viewproblem2&cpid=569
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("badmilk.in");
ofstream fout("badmilk.out");
 
class action {
    public:
        int p, m, t;
};
 
void max_self(int &a, int b) {
    a = max(a, b);
}
 
int main() {
    int N, M, D, S;
    fin >> N >> M >> D >> S;
    vector <action> a(D);
    for(int i = 0; i < D; ++i)
        fin >> a[i].p >> a[i].m >> a[i].t;
    vector<int> sick(N + 1);
    for(int i = 0; i < S; ++i) {
        int p, t;
        fin >> p >> t;
        sick[p] = t;
    }
    int sol = 0;
    for(int milk = 1; milk <= N; ++milk) {
        int cnt = 0;
        vector < bool > mark(N + 1);
        for(int i = 0; i < D && cnt < S; ++i) {
            action x = a[i];
            if(x.m == milk && x.t < sick[x.p]) {
                if(!mark[x.p])
                    ++cnt;
                mark[x.p] = true;
            }
        }
        if(cnt == S) {
            set<int> s;
            for(int i = 0; i < D; ++i) {
                action x = a[i];
                if(x.m == milk)
                    s.insert(x.p);
            }
            max_self(sol, static_cast<int>(s.size()));
        }
    }
    fout << sol;
}
 
