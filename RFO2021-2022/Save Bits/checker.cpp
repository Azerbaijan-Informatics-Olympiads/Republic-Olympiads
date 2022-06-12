#include "testlib.h"
#include <bits/stdc++.h>
#define pii pair<int, int>
#define f first
#define s second

using namespace std;

bool validate(string &s) {
  for (char c : s) {
    if (!(c == '0' || c == '1')) return false;
  }
  return true;
}

bool isTam(int N, string &s) {
  vector<bool>has((1 << N), false);
  int num = 0;
  for (int i = 0; i < N; ++i) {
    num = (num << 1) + s[i] - '0';
  }
  has[num] = true;
  int len = (int)s.size();
  for (int i = N; i < len; ++i) {
    if (s[i - N] == '1') {
      num -= (1 << (N - 1));
    }
    num = (num << 1) + s[i] - '0';
    has[num] = true;
  }
  for (int i = 0; i < (1 << N); ++i) {
    if (!has[i]) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  const int MAXN = 20;
  int N = inf.readInt(1, MAXN);
  string jans = ans.readString("[0-1]{1, 1048596}", "jans");
  string pans = ouf.readString("[0-1]{1, 20971521}", "pans");

  if ((int)pans.size() > N * (1 << N) || (int)pans.size() < N) {
    quitf(_wa, "Output is not valid");
  } else if (!validate(pans)) {
    quitf(_wa, "Output is not valid");
  } else if (!isTam(N, pans)) {
    quitf(_wa, "Output is not valid");
  } else if (pans == jans) {
    quitf(_ok, "Correct answer");
  } else {
    long double ratio = (long double)jans.size() / (long double)pans.size();
    long double score = 70.0 * ratio;
    quitp(score, "Partially correct");
  }
  return 0;
}
