#include <bits/stdc++.h>

using namespace std;

ifstream fin("poetry.in");
ofstream fout("poetry.out");

const int mod = 1e9 + 7;

void addSelf(int &x, const int &y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void multSelf(int &x, const int &y) {
  x = (int64_t)x * y % mod;
}

int mult(int x, const int &y) {
  multSelf(x, y);
  return x;
}

int Pow(int x, int n) {
  int ans = 1;
  while (n) {
    if (n & 1) {
      multSelf(ans, x);
    }
    multSelf(x, x);
    n >>= 1;
  }
  return ans;
}

void testCase() {
  int n, m, k;
  fin >> n >> m >> k;
  vector<pair<int, int>> a(n);
  for (auto &it : a) {
    fin >> it.first >> it.second;
  }
  vector<int> freq(26);
  for (int i = 0; i < m; ++i) {
    char c;
    fin >> c;
    freq[c - 'A'] += 1;
  }
  vector<int> dp(k), ways(n + 1);
  dp[0] = 1;
  for (int sum = 0; sum < k; ++sum) {
    for (auto it : a) {
      if (sum + it.first < k) {
        addSelf(dp[sum + it.first], dp[sum]);
      } else if (sum + it.first == k) {
        addSelf(ways[it.second], dp[sum]);
      }
    }
  }
  int ans = 1;
  for (int c = 0; c < 26; ++c) {
    if (freq[c]) {
      int sum = 0;
      for (int i = 1; i <= n; ++i) {
        addSelf(sum, Pow(ways[i], freq[c]));
      }
      multSelf(ans, sum);
    }
  }
  fout << ans << '\n';
}

int main() {
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  fin.close();
  fout.close();
  return 0;
}
