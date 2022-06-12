#include "testlib.h"
#include <bits/stdc++.h>
#define pii pair<int, int>
#define mpr make_pair

using namespace std;

int main(int argc, char** argv){
  registerValidation(argc, argv);
  const int up = 1e5;
  int N = inf.readInt(2, up, "N");
  inf.readSpace();

  int M = inf.readInt(1, up, "M");
  inf.readSpace();

  const int MAX = 1e9;
  int X = inf.readInt(1, MAX, "X");
  inf.readSpace();
  int Y = inf.readInt(1, MAX, "Y");
  inf.readEoln();

  vector<int>u(M), v(M);
  map<pii, bool>has;
  for (int i = 0; i < M; ++i) {
    u[i] = inf.readInt(1, N, "u[i]");
    inf.readSpace();
    v[i] = inf.readInt(1, N, "v[i]");
    ensure(u[i] != v[i]);
    ensure(has.find(mpr(u[i], v[i])) == has.end());
    has[mpr(u[i], v[i])] = true;
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
