// http://usaco.org/index.php?page=viewproblem2&cpid=915
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("herding.in");
ofstream fout("herding.out");
 
int main() {
    vector<int> a(3);
    for(int i = 0; i < 3; ++i)
        fin >> a[i];
    sort(a.begin(), a.end());
    if(a[2] == a[0] + 2)
        fout << "0\n";
    else
        if(a[1] == a[0] + 2 || a[2] == a[1] + 2)
            fout << "1\n";
    else
        fout << "2\n";
    fout << max(a[2] - a[1], a[1] - a[0]) - 1;
 
}
 
