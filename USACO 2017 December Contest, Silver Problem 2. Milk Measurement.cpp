// http://www.usaco.org/index.php?page=viewproblem2&cpid=763
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("measurement.in");
ofstream fout("measurement.out");
 
class event {
    public:
        int day, id, delta;
 
        bool operator < (const event &A) const {
            return day < A.day;
        }
};
 
int main() {
    int N, G;
    fin >> N >> G;
    vector <event> a;
    for(int i = 0; i < N; ++i) {
        int day, id;
        string s;
        fin >> day >> id >> s;
        int val = 0, semn = 1;
        if(s[0] == '-')
            semn = -1;
        for(int i = 1; i < static_cast<int>(s.size()); ++i)
            val = val * 10  + (s[i] - '0');
        val *= semn;
        a.push_back(event{day, id, val});
    }
    sort(a.begin(), a.end());
    map <int,int,greater<int>> cnt;
    map <int,int> M;
    int sol = 0;
    for(int i = 0; i < N; ++i) {
        int id = a[i].id,
            delta = a[i].delta,
            &curr = M[id];
        bool was_top = curr == cnt.begin()->first;
        int was_cnt = cnt[curr]--;
        if(was_cnt == 1)
            cnt.erase(curr);
        curr += delta;
        int is_cnt = ++cnt[curr];
        bool is_top = curr == cnt.begin()->first;
        if(was_top) {
            if(!is_top || was_cnt != 1 || is_cnt != 1)
                ++sol;
        }
        else
            if(is_top)
                ++sol;
    }
    fout << sol;
}
 
