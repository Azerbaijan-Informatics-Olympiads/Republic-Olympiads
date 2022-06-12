#include "testlib.h"
#include <bits/stdc++.h>
#define pii pair<int, int>
#define piii pair<pii, int>
#define vi vector<int>
#define vvi vector<vi>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define x first
#define y second
#define oo 1000000001
#define eb emplace_back
#define pb push_back
#define mpr make_pair
#define size(v) (int)v.size()
#define ln '\n'
#define ull unsigned long long
#define ll long long
#define all(v) v.begin(), v.end()

using namespace std;

bool cmp_manhattan(pii p1, pii p2) {
  return p1.x + p1.y < p2.x + p2.y;
}
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int Q1 = atoi(argv[3]); // number of type1 queries
	int Q2 = atoi(argv[4]); // number of type2 queries
	int preQ1 = Q1 - atoi(argv[5]); // number of type1 queries at the beginning
  int Q = Q1 + Q2;

  vector<pii> forUpdate;

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      forUpdate.eb(mpr(i, j));
    }
  }
  sort(all(forUpdate), cmp_manhattan);

  vector<int>t(Q), x(Q), y(Q);
  if (Q1 == Q2 && preQ1 == 0) {
    for (int i = 0; i < Q1; ++i) {
      t[i * 2] = 1;
      t[i * 2 + 1] = 2;
    }
  } else {
    vector<int>pos(Q);
    for (int i = 0; i < Q; ++i) {
      pos[i] = i;
    }
    shuffle(pos.begin() + preQ1, pos.end()); // ensure t[0...preQ1-1] = 1
    for (int i = 0; i < Q; ++i) {
      if (i < Q1) t[pos[i]] = 1;
      else t[pos[i]] = 2;
    }
  }

  int sizeUpd = size(forUpdate);
  int ptr1 = 0;
  for (int i = 0; i < Q; ++i) {
    if (t[i] == 1) {
      x[i] = forUpdate[ptr1].x;
      y[i] = forUpdate[ptr1++].y;
      if (ptr1 == sizeUpd) ptr1 = 0;
    } else {
      x[i] = rnd.next(1, N);
      y[i] = rnd.next(1, M);
    }
  }
  cout << N << ' ' << M << ' ' << Q << ln;
  for (int i = 0; i < Q; ++i) {
    cout << t[i] << ' ' << x[i] << ' ' << y[i] << ln;
  }
  return 0;
}
