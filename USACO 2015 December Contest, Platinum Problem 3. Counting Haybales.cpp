#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("haybales.in");
ofstream fout("haybales.out");
 
void min_self(int &x, int y) {
  x = min(x, y);
}
 
struct SegTree {
  int Size;
  vector<int> mn, sum, lazy;
 
  SegTree(int N) {
    Size = 1;
    while (Size < N)
      Size <<= 1;
    mn.resize(Size << 1);
    sum.resize(Size << 1);
    lazy.resize(Size << 1);
  }
 
  void build(int x, int lx, int rx) {
    if (lx == rx) {
      fin >> mn[x];
      sum[x] = mn[x];
      return;
    }
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    build(lSon, lx, mid);
    build(rSon, mid + 1, rx);
    mn[x] = min(mn[lSon], mn[rSon]);
    sum[x] = sum[lSon] + sum[rSon];
  }
 
  void push(int x, int lx, int rx) {
    if (lazy[x] == 0)
      return;
    int mid = (lx + rx) >> 1;
    int l[] = {mid - lx + 1, rx - mid};
    for (int i = 0; i < 2; ++i) {
      int son = x << 1 | i;
      mn[son] += lazy[x];
      sum[son] += l[i] * lazy[x];
      lazy[son] += lazy[x];
    }
    lazy[x] = 0;
  }
 
  void update(int x, int lx, int rx, int st, int dr, int val) {
    if (st <= lx && rx <= dr) {
      mn[x] += val;
      sum[x] += (rx - lx + 1) * val;
      lazy[x] += val;
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (st <= mid)
      update(lSon, lx, mid, st, dr, val);
    if (mid < dr)
      update(rSon, mid + 1, rx, st, dr, val);
    mn[x] = min(mn[lSon], mn[rSon]);
    sum[x] = sum[lSon] + sum[rSon];
  }
 
  int query_min(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return mn[x];
    push(x, lx, rx);
    int mid = (lx + rx) >> 1, ans = INF;
    if (st <= mid)
      min_self(ans, query_min(x << 1, lx, mid, st, dr));
    if (mid < dr)
      min_self(ans, query_min(x << 1 | 1, mid + 1, rx, st, dr));
    return ans;
  }
 
  int query_sum(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return sum[x];
    push(x, lx, rx);
    int mid = (lx + rx) >> 1, ans = 0;
    if (st <= mid)
      ans += query_sum(x << 1, lx, mid, st, dr);
    if (mid < dr)
      ans += query_sum(x << 1 | 1, mid + 1, rx, st, dr);
    return ans;
  }
};
 
int32_t main() {
  int N, Q;
  fin >> N >> Q;
  SegTree tree(N);
  tree.build(1, 1, N);
  for (int q = 0; q < Q; ++q) {
    char t;
    int l, r;
    fin >> t >> l >> r;
    if (t == 'P') {
      int C;
      fin >> C;
      tree.update(1, 1, N, l, r, C);
      continue;
    }
    if (t == 'M')
      fout << tree.query_min(1, 1, N, l, r) << '\n';
    else fout << tree.query_sum(1, 1, N, l, r) << '\n';
  }
  return 0;
}
 
