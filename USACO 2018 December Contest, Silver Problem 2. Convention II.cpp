// http://www.usaco.org/index.php?page=viewproblem2&cpid=859
#include <bits/stdc++.h>
#define mp make_pair
#define x first
#define y second
 
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
 
ifstream fin("convention2.in");
ofstream fout("convention2.out");
 
void max_self(ll &a, ll b) {
    a = max(a, b);
}
 
int main() {
    int N;
    fin >> N;
    vector<pair<int,pll>> cows;
    for(int i = 0; i < N; ++i) {
        ll a, t;
        fin >> a >> t;
        cows.push_back(mp(a, mp(i, t)));
    }
    sort(cows.begin(), cows.end());
    ll ans = 0, curr_done = cows[0].x + cows[0].y.y;
    int next = 1;
    set<pll> waiting;
    while(next < N || !waiting.empty()) {
        while(next < N && cows[next].x <= curr_done) {
            waiting.insert(mp(cows[next].y.x, next));
            ++next;
        }
        if(waiting.empty() && next < N) {
            curr_done = cows[next].x + cows[next].y.y;
            ++next;
        }
        else
            if(!waiting.empty()) {
                set<pll>::iterator next_cow = waiting.begin();
                max_self(ans, curr_done - cows[next_cow->second].x);
                curr_done += cows[next_cow->second].y.y;
                waiting.erase(next_cow);
            }
    }
    fout << ans;
}
 
