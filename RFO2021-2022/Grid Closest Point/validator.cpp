#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv){
  registerValidation(argc, argv);
  const int MAX = 1e6;
  const int MAXQ = 1e5;
  int N = inf.readInt(1, MAX, "N");
  inf.readSpace();

  int M = inf.readInt(1, MAX, "M");
  inf.readSpace();

  long long NM = 1ll * N * M;
  ensure(NM <= (long long)MAX);

  int Q = inf.readInt(2, MAXQ, "Q");
  inf.readEoln();

  vector<int>t(Q), x(Q), y(Q);
  int max_t = 0;
  for (int i = 0; i < Q; ++i) {
    t[i] = inf.readInt(1, 2, "t[i]");
    max_t = max(t[i], max_t);
    inf.readSpace();
    x[i] = inf.readInt(1, N, "x[i]");
    inf.readSpace();
    y[i] = inf.readInt(1, M, "y[i]");
    inf.readEoln();
  }
  ensure(t[0] == 1);
  ensure(max_t == 2);

  inf.readEof();
  return 0;
}
