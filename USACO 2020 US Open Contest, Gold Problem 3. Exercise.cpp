#include <bits/stdc++.h>

using namespace std;

ifstream fin("exercise.in");
ofstream fout("exercise.out");

int mod;

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

void testCase() {
  int n;
  fin >> n >> mod;
  if (n == 1) {
    cout << "1\n";
    return;
  }
  vector<bool> isPrime(n + 1, true);
  vector<int> primes;
  for (int i = 2; i <= n; ++i) {
    if (isPrime[i]) {
      primes.emplace_back(i);
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }
  int N = primes.size();
  vector<vector<int>> dp(N + 1, vector<int>(n + 1));
  for (int i = 0; i <= n; ++i) {
    dp[0][i] = 1; /// permutarea identica
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j <= n; ++j) {
      dp[i][j] = dp[i - 1][j];
      int p = primes[i - 1];
      while (p <= j) {
        addSelf(dp[i][j], mult(dp[i - 1][j - p], p));
        p *= primes[i - 1];
      }
    }
  }
  fout << dp[N][n] << '\n';
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
