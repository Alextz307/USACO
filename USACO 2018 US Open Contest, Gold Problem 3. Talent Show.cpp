#include <bits/stdc++.h>
#define int long long

using namespace std;

ifstream fin("talent.in");
ofstream fout("talent.out");

const int kN = 250;
const int INF = 1e18L;
int n, W, w[kN], t[kN];

void maxSelf(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

bool check(int y) {
  vector<int> dp(W + 1, -INF);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    int wt = 1000 * t[i] - y * w[i];
    for (int g = W; g >= 0; --g) {
      if (dp[g] != -INF) {
        maxSelf(dp[min(g + w[i], W)], dp[g] + wt);
      }
    }
  }
  return dp[W] >= 0;
}

void testCase() {
  fin >> n >> W;
  for (int i = 0; i < n; ++i) {
    fin >> w[i] >> t[i];
  }
  int l = 0, r = 1e9, ans = 0;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  fout << ans << '\n';
}

int32_t main() {
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  fin.close();
  fout.close();
  return 0;
}
