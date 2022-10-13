#include <bits/stdc++.h>

using namespace std;

ifstream fin("cowpatibility.in");
ofstream fout("cowpatibility.out");

struct subset_t {
  short n;
  int v[5];

  bool operator == (const subset_t &rhs) const {
    if (n != rhs.n) {
      return false;
    }
    for (int i = 0; i < 5; ++i) {
      if (v[i] != rhs.v[i]) {
        return false;
      }
    }
    return true;
  }
};

const int base = 1572869;
const int mod = 1610612741;

struct hash_t {
	int operator () (const subset_t &x) const {
		int res = 0;
		for (int i = 0; i < 5; i++) {
      res = ((int64_t)res * base + x.v[i]) % mod;
		}
		return res;
	}
};

int main() {
  int n;
  fin >> n;
  vector<int> setBits[32];
  for (int mask = 1; mask < 32; ++mask) {
    for (int bit = 0; (1 << bit) <= mask; ++bit) {
      if (mask & (1 << bit)) {
        setBits[mask].emplace_back(bit);
      }
    }
  }
  int a[5];
  unordered_map<subset_t, int, hash_t> subsets;
  subsets.reserve(31 * n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 5; ++j) {
      fin >> a[j];
    }
    sort(a, a + 5);
    for (int mask = 1; mask < 32; ++mask) {
      subset_t subset{0, {-1, -1, -1, -1, -1}};
      for (const int &bit : setBits[mask]) {
        if (mask & (1 << bit)) {
          subset.v[subset.n++] = a[bit];
        }
      }
      subsets[subset] += 1;
    }
  }
  int64_t res = (int64_t)n * (n - 1) / 2;
  for (const auto &it : subsets) {
    if (it.first.n & 1) {
      res -= (int64_t)it.second * (it.second - 1) / 2;
    } else {
      res += (int64_t)it.second * (it.second - 1) / 2;
    }
  }
  fout << res << '\n';
  fin.close();
  fout.close();
  return 0;
}
