#include <bits/stdc++.h>

using namespace std;

ifstream fin("team.in");
ofstream fout("team.out");

const int mod = 1e9 + 9;
const int kN = 1e3;
const int kK = 10;
int a[1 + kN], b[1 + kN], sum[1 + kK][1 + kN][1 + kN], sum2[1 + kK][1 + kN][1 + kN];
/// dp[k][i][j] =def= am un set de k vaci ce se termina la pozitia i si vaca corespunzatoare
/// pozitiei i este j.
/// sum[k][i][j] =def= am un set de k vaci ce se termina la pozitia i si vaca corespunzatoare
/// pozitiei i este pe o pozitie mai mica sau egala decat j.
/// dp[k][i][j] = SUM{sum[k - 1][p][j - 1]}; 1 <= p <= i - 1
/// <=not=> dp[k][i][j] = sum2[k - 1][i - 1][j - 1]
/// sum[k][i][j] = sum[k][i][j - 1] + dp[k][i][j]
/// sum2[k][i][j] = sum2[k][i - 1][j] + sum[k][i][j]
/// De cand a[i] <= a[j], dp[k][i][j] = 0, iar sum[k][i][j] ramane constant
/// Initializare: Initializez cu 1 linia pentru k = 1 unde este cazul(a[j] < a[i])
/// Rezultat: SUM{sum[k][i][m]}; 1 <= i <= N
/// Complexitate: O(N * M * K)

void addSelf(int &x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int add(int x, int y) {
  addSelf(x, y);
  return x;
}

void testCase() {
  int N, M, K;
  fin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) {
    fin >> a[i];
  }
  sort(a + 1, a + N + 1);
  for (int i = 1; i <= M; ++i) {
    fin >> b[i];
  }
  sort(b + 1, b + M + 1);
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int dp = 0;
      if (b[j] < a[i]) {
        dp = 1;
      }
      sum[1][i][j] = add(sum[1][i][j - 1], dp);
      sum2[1][i][j] = add(sum2[1][i - 1][j], sum[1][i][j]);
    }
  }
  for (int k = 2; k <= K; ++k) {
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= M; ++j) {
        int dp = 0;
        if (b[j] < a[i]) {
          dp = sum2[k - 1][i - 1][j - 1];
        }
        sum[k][i][j] = add(sum[k][i][j - 1], dp);
        sum2[k][i][j] = add(sum2[k][i - 1][j], sum[k][i][j]);
      }
    }
  }
  int ans = 0;
  for (int i = K; i <= N; ++i) {
    addSelf(ans, sum[K][i][M]);
  }
  fout << ans;
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
