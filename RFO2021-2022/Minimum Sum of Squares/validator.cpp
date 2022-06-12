#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){
  registerValidation(argc, argv);
  const int MAXT = 1e5;
  int T = inf.readInt(1, MAXT, "T");
  inf.readEoln();

  const int MAXN = 1e9;
  vector<int>N(T), L(T);
  for (int i = 0; i < T; ++i) {
    N[i] = inf.readInt(1, MAXN, "N[i]");
    inf.readSpace();
    L[i] = inf.readInt(1, N[i], "L[i]");
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
